/*
  Copyright (c) 2011-2012 NVIDIA Corporation
  Copyright (c) 2011-2012 Cass Everitt
  Copyright (c) 2012 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012 Nigel Stewart
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

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalConfig.h"
#include "RegalCacheShader.h"

#include <lookup3.h>

#include <vector>
#include <string>
#include <boost/print/print_string.hpp>

using namespace ::std;
using ::boost::print::print_string;

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Cache {

void
shaderSource(PFNGLSHADERSOURCEPROC proc, GLuint shader, GLsizei count, const GLchar **string, const GLint *length)
{
  if (REGAL_CACHE && REGAL_CACHE_SHADER && Config::cache && Config::cacheShader)
  {
    // Compute 32-bit hash of shader source

    uint32_t hash = 0;
    for (GLsizei i=0; i<count; ++i)
      hash = Lookup3::hashlittle(string[i], length ? length[i] : strlen(string[i]), hash);

    ::std::string filename = makePath(Config::cacheDirectory,print_string(boost::print::hex(hash),".txt"));

    // Cache it to disk, iff it's not there yet

    if (REGAL_CACHE_SHADER_WRITE && Config::cacheShaderWrite && !fileExists(filename.c_str()))
    {
      FILE *f = fopen(filename.c_str(),"wt");
      if (!f)
      {
        Warning("Could not write shader to file ",filename,", permissions problem?");
      }
      else
      {
        Internal("Regal::ShaderCache::glShaderSource","shader=",shader," hash=",boost::print::hex(hash)," filename=",filename," written.");
        Info("Cached shader ",boost::print::hex(hash)," written: ",filename);
        for (GLsizei i=0; i<count; ++i)
          fwrite(string[i], length ? length[i] : strlen(string[i]),1,f);
        fclose(f);
      }
    }
    else
    {
      // Read from disk cache, if reading is enabled
      // export REGAL_CACHE_SHADER_READ=1

      if (REGAL_CACHE_SHADER_READ && Config::cacheShaderRead)
      {
        std::string buffer;

        // Try opening the file

        FILE *f = fopen(filename.c_str(),"rt");

        if (!f)
        {
          Internal("Regal::ShaderCache::glShaderSource","shader=",shader," hash=",boost::print::hex(hash)," filename=",filename," not found.");
          Info("Cached shader ",boost::print::hex(hash)," not found: ",filename);
          goto done;
        }

        buffer = fileRead(f);

        Internal("Regal::ShaderCache::glShaderSource","shader=",shader," hash=",boost::print::hex(hash)," filename=",filename," read.");
        Info("Cached shader ",boost::print::hex(hash)," read: ",filename);

        const GLchar *bufferPtr[2];
        bufferPtr[0] = &buffer[0];
        bufferPtr[1] = NULL;

        proc(shader,1,bufferPtr,NULL);
        return;
      }
      else
      {
        Internal("Regal::ShaderCache::glShaderSource","shader=",shader," hash=",boost::print::hex(hash)," filename=",filename," not read.");
        Info("Cached shader ",boost::print::hex(hash)," not read: ",filename);
      }
    }
  }

  // Call the driver

done:
  proc(shader,count,string,length);
}

};

REGAL_NAMESPACE_END
