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

 Regal API filtering support for ES 2.0 and Core GL contexts.
 Cass Everitt

 */

#ifndef __REGAL_FILT_H__
#define __REGAL_FILT_H__

#include "RegalUtil.h"

#if REGAL_EMULATION

REGAL_GLOBAL_BEGIN

#include "RegalEmu.h"
#include "RegalContext.h"
#include "RegalContextInfo.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Emu {

  struct Filt : public RegalEmu
  {
    Filt()
    : filtered(false)
    {
    }

    void
    Init(RegalContext &ctx)
    {
      UNUSED_PARAMETER(ctx);
    }

    void BindTexture(const RegalContext &ctx, GLenum target, GLuint name );

    template <typename T> void Get(const RegalContext &ctx, GLenum pname, T *params)
    {
      FilterGet(ctx,pname);
      if (filtered)
        params[0] = T(retVal);
    }

    void PolygonMode (const RegalContext &ctx, GLenum face, GLenum mode);
    void RenderMode  (const RegalContext &ctx, GLenum mode);
    void TexParameter(const RegalContext &ctx, GLenum target, GLenum pname, GLint   param);
    void TexParameter(const RegalContext &ctx, GLenum target, GLenum pname, GLfloat param);

    void FilterGet   (const RegalContext &ctx, GLenum pname);

    bool Filtered() { bool f = filtered; filtered = false; return f; }

  private:
    bool filtered;
    int  retVal;
  };

}

REGAL_NAMESPACE_END

#endif // REGAL_EMULATION

#endif // __REGAL_FILT_H__
