/*
  Copyright (c) 2011 NVIDIA Corporation
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

#ifndef __REGAL_HELPER_H__
#define __REGAL_HELPER_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <GL/Regal.h>

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace helper {

  namespace size {

    std::size_t get(GLenum pname);
    std::size_t callLists(GLsizei, GLenum);
    std::size_t fogv(GLenum);
    std::size_t lightv(GLenum);
    std::size_t lightModelv(GLenum);
    std::size_t materialv(GLenum);
    std::size_t texParameterv(GLenum);
    std::size_t pixelImage(GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLint, GLenum);
    std::size_t texEnvv(GLenum, GLenum);
    std::size_t texGenv(GLenum);
    std::size_t samplerParameterv(GLenum);
    std::size_t drawElements(GLenum, GLsizei, GLenum);
    std::size_t namedString(const GLint, const GLchar *);
    std::size_t namedStringParams(const GLenum);

    inline std::size_t bytesPerComponent(const GLenum type)
    {
      switch (type)
      {
        /* Each value is one component per element. */

        case GL_UNSIGNED_BYTE:               return sizeof(GLubyte);
        case GL_BYTE:                        return sizeof(GLbyte);
        case GL_BITMAP:                      return sizeof(GLubyte);
        case GL_UNSIGNED_SHORT:              return sizeof(GLushort);
        case GL_SHORT:                       return sizeof(GLshort);
        case GL_HALF_FLOAT:                  return sizeof(GLhalfARB);
        case GL_UNSIGNED_INT:                return sizeof(GLuint);
        case GL_INT:                         return sizeof(GLint);
        case GL_FLOAT:                       return sizeof(GLfloat);

        /* Each unsigned value contains all the components per element. */

        case GL_UNSIGNED_BYTE_3_3_2:
        case GL_UNSIGNED_BYTE_2_3_3_REV:     return sizeof(GLubyte);

        case GL_UNSIGNED_SHORT_5_6_5:
        case GL_UNSIGNED_SHORT_5_6_5_REV:
        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        case GL_UNSIGNED_SHORT_5_5_5_1:
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:  return sizeof(GLushort);

        case GL_UNSIGNED_INT_8_8_8_8:
        case GL_UNSIGNED_INT_8_8_8_8_REV:
        case GL_UNSIGNED_INT_10_10_10_2:
        case GL_UNSIGNED_INT_2_10_10_10_REV: return sizeof(GLuint);

        default:                             return 0;
      }
    }

    inline std::size_t componentsPerPixel(const GLenum format)
    {
      switch (format)
      {
        case GL_COLOR_INDEX:
        case GL_STENCIL_INDEX:
        case GL_R:
        case GL_DEPTH_COMPONENT:
        case GL_DEPTH_COMPONENT16:
        case GL_RED:
        case GL_GREEN:
        case GL_BLUE:
        case GL_ALPHA:
        case GL_INTENSITY:       return 1;
        case GL_RG:              return 2;
        case GL_RGB:
        case GL_BGR:             return 3;
        case GL_RGBA:
        case GL_BGRA:            return 4;
        case GL_LUMINANCE:       return 1;
        case GL_LUMINANCE_ALPHA:
        case GL_DEPTH_STENCIL:   return 2;
        default:                 return 1;
      }
    }
  }

   char *shaderSourceStrings(const GLsizei, const GLchar **, const GLint *);
}

REGAL_NAMESPACE_END

#endif
