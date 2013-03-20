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

/*

 Frame capture, etc
 Nigel Stewart

 */

#ifndef __REGAL_FRAME_H__
#define __REGAL_FRAME_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalTimer.h"
#include "RegalContext.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

struct Frame {

  Frame()
  : frame(0),
    frameSamples(0),
    mode(AutoDetect)
  {
    frameTimer.restart();
  }

  void Init(RegalContext &ctx)
  {
    UNUSED_PARAMETER(ctx);
    Internal("Regal::Frame::Init","()");
  }

  //
  // Per-frame state and configuration
  //

  size_t              frame;
  Timer               frameTimer;

  size_t              frameSamples;
  Timer               frameSimpleTimeout;

  //

  inline void glFrameTerminatorGREMEDY(RegalContext &ctx) { if (mode==AutoDetect) mode = FrameTerminatorGREMEDY; if (mode==FrameTerminatorGREMEDY) capture(ctx); }
  inline void wglSwapBuffers          (RegalContext &ctx) { if (mode==AutoDetect) mode = SwapBuffers;            if (mode==SwapBuffers)            capture(ctx); }
  inline void glXSwapBuffers          (RegalContext &ctx) { if (mode==AutoDetect) mode = SwapBuffers;            if (mode==SwapBuffers)            capture(ctx); }
  inline void eglSwapBuffers          (RegalContext &ctx) { if (mode==AutoDetect) mode = SwapBuffers;            if (mode==SwapBuffers)            capture(ctx); }
  inline void CGLFlushDrawable        (RegalContext &ctx) { if (mode==AutoDetect) mode = SwapBuffers;            if (mode==SwapBuffers)            capture(ctx); }

private:
  void capture(RegalContext &ctx);

  enum Mode
  {
    AutoDetect,
    FrameTerminatorGREMEDY,
    SwapBuffers
  };

  Mode mode;
};

REGAL_NAMESPACE_END

#endif
