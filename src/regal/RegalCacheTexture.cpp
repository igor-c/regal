/*
  Copyright (c) 2011-2013 NVIDIA Corporation
  Copyright (c) 2011-2013 Cass Everitt
  Copyright (c) 2012-2013 Scott Nations
  Copyright (c) 2012-2013 Mathias Schott
  Copyright (c) 2012-2013 Nigel Stewart
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*

 Disk-based .png texture caching
 Nigel Stewart

 */

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalConfig.h"
#include "RegalToken.h"
#include "RegalCacheTexture.h"
#include "RegalScopedPtr.h"

#include <lookup3.h>           // 32-bit memory hashing function

#include <string>
#include <boost/print/print_string.hpp>

#if !REGAL_NO_PNG
#include <zlib.h>
#include <png.h>
#endif

using namespace ::std;
using ::boost::print::print_string;

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Cache {

void
bindTexture(PFNGLBINDTEXTUREPROC bindTextureProc, PFNGLGETTEXLEVELPARAMETERIVPROC getTexLevelProc, PFNGLGETTEXIMAGEPROC getTexImageProc, GLenum target, GLuint texture)
{
  RegalAssert(bindTextureProc);
  RegalAssert(getTexLevelProc);
  RegalAssert(getTexImageProc);

  bindTextureProc(target,texture);

  if (REGAL_CACHE && REGAL_CACHE_TEXTURE && Config::cache && Config::cacheTexture)
  {
    // Query the texture dimensions
    // TODO: Query the internal format and channels too?

    GLint width = 0;
    GLint height = 0;

    getTexLevelProc(target, 0, GL_TEXTURE_WIDTH,  &width);
    getTexLevelProc(target, 0, GL_TEXTURE_HEIGHT, &height);

    const GLint size = width*height;
    const GLint bytes = size*4;

    Internal("Regal::CacheTexture::texture","width=",width," height=",height);

    if (!width || !height)
      return;

    // Fetch the RGBA texture data
    // TODO: Handle packing alignment...

    scoped_array<GLbyte> buffer(new GLbyte [bytes]);

    getTexImageProc(target,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer.get());

    // Compute 32-bit hash

    uint32_t hash = 0;
    hash = Lookup3::hashlittle(buffer.get(), bytes, hash);

    string filename = makePath(Config::cacheDirectory,print_string(boost::print::hex(hash),".png"));

    Info("glBindTexture(",Token::GLenumToString(target),",",texture,") width=",width," height=",height," hash=",boost::print::hex(hash));

    // Cache it to disk, iff it's not there yet
    // export REGAL_CACHE_TEXTURE_WRITE=1

    if (REGAL_CACHE_TEXTURE_WRITE && Config::cacheTextureWrite && !fileExists(filename.c_str()))
    {
#if !REGAL_NO_PNG
      static png_color_8 pngSBIT = {8, 8, 8, 0, 8};

      FILE *fp = fopen(filename.c_str(), "wb");
      if (fp)
      {
        png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        if (pngPtr)
        {
          png_infop pngInfo = png_create_info_struct(pngPtr);
          if (pngInfo)
          {
            png_init_io(pngPtr, fp);

            // Z_NO_COMPRESSION, Z_BEST_SPEED, Z_BEST_COMPRESSION,
            // Z_DEFAULT_COMPRESSION

            png_set_compression_level(pngPtr, Z_BEST_COMPRESSION);
            png_set_IHDR(pngPtr, pngInfo, width, height,
                         8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
            png_set_pHYs(pngPtr, pngInfo, 72 * 40, 72 * 40, PNG_RESOLUTION_METER);
            png_set_sBIT(pngPtr, pngInfo, &pngSBIT);
            png_write_info(pngPtr, pngInfo);
            for (int y = height; y--; )
              png_write_row(pngPtr, reinterpret_cast<png_byte *>(buffer.get() + y * width * 4));
            png_write_end(pngPtr, pngInfo);
          }
          png_destroy_write_struct(&pngPtr, &pngInfo);
        }
        fclose(fp);

        Internal("Regal::CacheTexture::texture"," hash=",boost::print::hex(hash)," filename=",filename," written.");
        Info("Cached texture written: ",filename);
      }
      else
      {
        Warning("Could not write texture to file ",filename,", permissions problem?");
      }
#endif
    }
    else
    {
      // Read from disk cache, if reading is enabled
      // export REGAL_CACHE_TEXTURE_READ=1

      if (REGAL_CACHE_TEXTURE_READ && Config::cacheTextureRead)
      {
#if !REGAL_NO_PNG
        // TODO
#endif
        return;
      }
      else
      {
        Info("Cached texture not read or written: ",filename);
      }
    }
  }
}

};

REGAL_NAMESPACE_END
