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

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

#if REGAL_EMULATION

REGAL_GLOBAL_BEGIN

#include "RegalLog.h"
#include "RegalFilt.h"
#include "RegalToken.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Emu {

  using namespace ::REGAL_NAMESPACE_INTERNAL::Logging;
  using namespace ::REGAL_NAMESPACE_INTERNAL::Token;

  void Filt::BindTexture(const RegalContext &ctx, GLenum target, GLuint name)
  {
    UNUSED_PARAMETER(ctx);
    UNUSED_PARAMETER(target);
    UNUSED_PARAMETER(name);

    #if REGAL_SYS_ES2
    if (ctx.isES2())
    {
      switch( target )
      {
        case GL_TEXTURE_1D:
        case GL_TEXTURE_3D:
          Warning( "Regal does not support ", GLenumToString( target ), " as target for glBindTexture for ES 2.0 profile - skipping." );
          filtered = true;
        default:
          break;
      }
    }
    #endif
  }

  void Filt::RenderMode(const RegalContext &ctx, GLenum mode)
  {
    UNUSED_PARAMETER(ctx);
    UNUSED_PARAMETER(mode);

    #if REGAL_SYS_ES2 || REGAL_SYS_GL
    if (ctx.isCore() || ctx.isES2())
      if (mode!=GL_RENDER)
      {
        Warning("Regal does not support ", GLenumToString(mode), " render mode for core or ES 2.0 profiles, only GL_RENDER is supported in those profiles - skipping.");
        filtered = true;
      }
    #endif
  }

  void Filt::TexParameter(const RegalContext &ctx, GLenum target, GLenum pname, GLint param)
  {
    TexParameter(ctx,target,pname,GLfloat(param));
  }

  void Filt::TexParameter(const RegalContext &ctx, GLenum target, GLenum pname, GLfloat param)
  {
    UNUSED_PARAMETER(ctx);
    UNUSED_PARAMETER(target);
    UNUSED_PARAMETER(pname);
    UNUSED_PARAMETER(param);

    #if REGAL_SYS_ES2 || REGAL_SYS_GL
    if (ctx.isCore() || ctx.isES2())
      switch(pname)
      {
        case GL_TEXTURE_WRAP_S:
        case GL_TEXTURE_WRAP_T:
        case GL_TEXTURE_WRAP_R:
          switch(int(param))
          {
            case GL_CLAMP:
              Warning("Regal does not support GL_CLAMP wrap mode for core or ES 2.0 profiles - skipping.");
              filtered = true;
            default: break;
          }
        default: break;
      }
    #endif
  }

  void Filt::PolygonMode(const RegalContext &ctx, GLenum face, GLenum mode)
  {
    UNUSED_PARAMETER(ctx);
    UNUSED_PARAMETER(face);
    UNUSED_PARAMETER(mode);

    #if REGAL_SYS_GL
    if (ctx.isCore())
    {
      if (face!=GL_FRONT_AND_BACK)
      {
        Warning("Regal does not support ", GLenumToString(face), " in glPolygonMode for core profile, only GL_FRONT_AND_BACK is supported - skipping.");
        filtered = true;
      }
    }
    #endif

    #if REGAL_SYS_ES2
    if (ctx.isES2())
    {
      Warning("Regal does not support glPolygonMode for ES 2.0 - skipping.");
      filtered = true;
    }
    #endif
  }

  void Filt::FilterGet(const RegalContext &ctx, GLenum pname)
  {
    UNUSED_PARAMETER(ctx);
    UNUSED_PARAMETER(pname);

    #if REGAL_SYS_ES2 || REGAL_SYS_GL
    if (ctx.isCore() || ctx.isES2())
    {
      filtered = true;
      switch (pname )
      {
        case GL_MAX_TEXTURE_SIZE:              retVal = 1024; break;
        case GL_MAX_PIXEL_MAP_TABLE:           retVal = 256;  break;
        case GL_MAX_NAME_STACK_DEPTH:          retVal = 128;  break;
        case GL_MAX_LIST_NESTING:              retVal = 64;   break;
        case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        case GL_MAX_ATTRIB_STACK_DEPTH:        retVal = 16;   break;

        case GL_DEPTH_BITS:                    retVal = 24;   break;

        case GL_RED_BITS:
        case GL_GREEN_BITS:
        case GL_BLUE_BITS:
        case GL_ALPHA_BITS:
        case GL_STENCIL_BITS:
        case GL_SUBPIXEL_BITS:
          retVal = 8;
          break;

        case GL_INDEX_MODE:
        case GL_UNPACK_ROW_LENGTH:
        case GL_UNPACK_SKIP_ROWS:
        case GL_UNPACK_SKIP_PIXELS:
        case GL_UNPACK_LSB_FIRST:
        case GL_UNPACK_SWAP_BYTES:
        case GL_PACK_ROW_LENGTH:
        case GL_PACK_SKIP_ROWS:
        case GL_PACK_SKIP_PIXELS:
        case GL_PACK_LSB_FIRST:
        case GL_PACK_SWAP_BYTES:
          retVal = 0;
          break;
        default:
          filtered = false;
          break;
      }
      if (filtered)
      {
        Warning( "Regal does not support ", GLenumToString(pname), " as pname for glGet for core or ES 2.0 profiles - skipping." );
        return;
      }
    }
    #endif

    #if REGAL_SYS_GL
    if (ctx.isCore())
    {
      filtered = true;
      switch (pname )
      {
          /* just a test
           case GL_UNPACK_ALIGNMENT:
           retVal = 0;
           break;
           */
        default:
          filtered = false;
          break;
      }
      if (filtered)
      {
        Warning( "Regal does not support ", GLenumToString(pname), " as pname for glGet for core profile - skipping." );
        return;
      }
    }
    #endif

    #if REGAL_SYS_ES2
    if (ctx.isES2())
    {
      filtered = true;
      switch (pname ) {
        case GL_PACK_ALIGNMENT:
          retVal = 1;
          break;
        default:
          filtered = false;
          break;
      }
      if (filtered)
      {
        Warning( "Regal does not support ", GLenumToString(pname), " as pname for glGet for ES 2.0 profile - skipping." );
        return;
      }
    }
    #endif
  }
}

REGAL_NAMESPACE_END

#endif // REGAL_EMULATION
