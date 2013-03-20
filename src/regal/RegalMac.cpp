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

#if REGAL_SYS_OSX

REGAL_GLOBAL_BEGIN

#include "RegalMac.h"

#include <stdio.h>

#include <GL/Regal.h>

#define CALL( foo ) extern "C" { REGAL_DECL void foo () { RegalAssert(!#foo); } }

// Undocumented Apple OpenGL framework API
// TODO - Need to support these properly...

CALL( gll_noop )
CALL( CGLAreContextsShared )
CALL( CGLSetPBufferVolatileState )
CALL( CGLOpenCLMuxLockDown )

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Mac {

  static int AttributeArgs(CGLPixelFormatAttribute a)
  {
    switch( a )
    {
      case kCGLPFAColorSize:
      case kCGLPFAAlphaSize:
      case kCGLPFADepthSize:
      case kCGLPFAStencilSize:
      case kCGLPFAAccumSize:
      case kCGLPFASampleBuffers:
      case kCGLPFASamples:
      case kCGLPFARendererID:
      case kCGLPFADisplayMask:
      case kCGLPFAOpenGLProfile:
      case kCGLPFAVirtualScreenCount:
        return 1;
      case kCGLPFAAllRenderers:
      case kCGLPFADoubleBuffer:
      case kCGLPFAStereo:
      case kCGLPFAAuxBuffers:
      case kCGLPFAMinimumPolicy:
      case kCGLPFAMaximumPolicy:
      case kCGLPFAOffScreen:
      case kCGLPFAFullScreen:
      case kCGLPFAAuxDepthStencil:
      case kCGLPFAColorFloat:
      case kCGLPFAMultisample:
      case kCGLPFASupersample:
      case kCGLPFASampleAlpha:
      case kCGLPFASingleRenderer:
      case kCGLPFANoRecovery:
      case kCGLPFAAccelerated:
      case kCGLPFAClosestPolicy:
        //case kCGLPFARobust:
      case kCGLPFABackingStore:
        //case kCGLPFAMPSafe:
      case kCGLPFAWindow:
        //case kCGLPFAMultiScreen:
      case kCGLPFACompliant:
      case kCGLPFAPBuffer:
      case kCGLPFARemotePBuffer:
      case kCGLPFAAllowOfflineRenderers:
      case kCGLPFAAcceleratedCompute:
      default:
        break;
    }
    return 0;
  }

  CGLPixelFormatAttribute *forceCoreAttribs(const CGLPixelFormatAttribute *attribs)
  {
    CGLPixelFormatAttribute *nattribs = NULL;
    int attrcount = 0;
    bool hasProfile = false;
    while (attribs[attrcount])
    {
      CGLPixelFormatAttribute a = attribs[attrcount];
      if ( a == kCGLPFAOpenGLProfile )
        hasProfile = true;
      attrcount += AttributeArgs( a ) + 1;
    }
    nattribs = new CGLPixelFormatAttribute[ attrcount + (hasProfile ? 0 : 2 ) + 1 ];
    int profileIdx = -1;
    for (int i = 0; i < attrcount; i++ )
    {
      nattribs[i] = attribs[i];
      if ( AttributeArgs( attribs[i] ) )
      {
        i++;
        nattribs[i] = attribs[i];
        if ( hasProfile && attribs[i-1] == kCGLPFAOpenGLProfile )
        {
          profileIdx = i;
          nattribs[i] = (CGLPixelFormatAttribute) 0x3200;
        }
        if ( attribs[i-1] == kCGLPFAAuxBuffers || attribs[i-1] == kCGLPFAAccumSize )
          nattribs[i] = (CGLPixelFormatAttribute)0;
      }
    }
    if (!hasProfile)
    {
      nattribs[ attrcount + 0 ] = kCGLPFAOpenGLProfile;
      nattribs[ attrcount + 1] = (CGLPixelFormatAttribute)0x3200;
    }
    nattribs[ attrcount + ( hasProfile ? 0 : 2 ) ] = (CGLPixelFormatAttribute) 0;
    return nattribs;
  }
}

REGAL_NAMESPACE_END

#endif // REGAL_SYS_OSX
