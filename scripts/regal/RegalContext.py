#!/usr/bin/python -B

from string import Template, upper, replace

from ApiUtil import outputCode
from ApiCodeGen import *

from EmuContextState   import formulae as contextStateFormulae
from EmuGetString      import formulae as getStringFormulae
from EmuForceCore      import formulae as forceCoreFormulae
from EmuLookup         import formulae as lookupFormulae
from EmuMarker         import formulae as markerFormulae
from EmuExtensionQuery import formulae as extensionQueryFormulae
from EmuErrorString    import formulae as errorStringFormulae
from EmuEnable         import formulae as enableFormulae

from EmuLog    import logFormulae

from Emu       import emuFindEntry, emuCodeGen
from EmuDsa    import dsaFormulae
from EmuVao    import vaoFormulae
from EmuPpc    import ppcFormulae
from EmuPpa    import ppaFormulae
from EmuIff    import iffFormulae
from EmuBin    import binFormulae
from EmuObj    import objFormulae
from EmuFilter import formulae as filterFormulae

# Regal.cpp emulation

emuRegal = [
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : contextStateFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : getStringFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : forceCoreFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : lookupFormulae },
    { 'type' : 'Marker',   'member' : 'marker', 'conditional' : None,  'ifdef' : None,  'formulae' : markerFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : extensionQueryFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : errorStringFormulae },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : logFormulae    },
    { 'type' : None,       'member' : None,     'conditional' : None,  'ifdef' : None,  'formulae' : enableFormulae },
]


# RegalDispathEmu.cpp fixed-function emulation

emu = [
    { 'type' : 'RegalObj',    'member' : 'obj',    'conditional' : 'Config::enableEmuObj',    'ifdef' : 'REGAL_EMU_OBJ',    'formulae' : objFormulae    },
    #{ 'type' : 'RegalPpc',   'member' : 'ppc',    'conditional' : None,                      'ifdef' : '',                 'formulae' : ppcFormulae    },
    { 'type' : 'RegalPpa',    'member' : 'ppa',    'conditional' : 'Config::enableEmuPpa',    'ifdef' : 'REGAL_EMU_PPA',    'formulae' : ppaFormulae    },
    { 'type' : 'RegalBin',    'member' : 'bin',    'conditional' : 'Config::enableEmuBin',    'ifdef' : 'REGAL_EMU_BIN',    'formulae' : binFormulae    },
    { 'type' : 'RegalDsa',    'member' : 'dsa',    'conditional' : 'Config::enableEmuDsa',    'ifdef' : 'REGAL_EMU_DSA',    'formulae' : dsaFormulae    },
    { 'type' : 'RegalIff',    'member' : 'iff',    'conditional' : 'Config::enableEmuIff',    'ifdef' : 'REGAL_EMU_IFF',    'formulae' : iffFormulae    },
    { 'type' : 'RegalVao',    'member' : 'vao',    'conditional' : 'Config::enableEmuVao',    'ifdef' : 'REGAL_EMU_VAO',    'formulae' : vaoFormulae    },
    { 'type' : None,          'member' : None,     'conditional' : 'Config::enableEmuFilter', 'ifdef' : 'REGAL_EMU_FILTER', 'formulae' : filterFormulae },
    { 'type' : 'void',        'member' : None,     'conditional' : None,                      'ifdef' : None,               'formulae' : None           }
]

contextHeaderTemplate = Template( '''${AUTOGENERATED}
${LICENSE}

#ifndef __${HEADER_NAME}_H__
#define __${HEADER_NAME}_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalTimer.h"
#include "RegalPrivate.h"
#include "RegalDispatcher.h"
#include "RegalDispatchError.h"

#if defined(__native_client__)
#define __gl2_h_  // HACK - revisit
#include <ppapi/c/pp_resource.h>
#include <ppapi/c/ppb_opengles2.h>
#endif

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

struct DebugInfo;
struct ContextInfo;

${EMU_FORWARD_DECLARE}

struct RegalContext
{
  RegalContext();
  ~RegalContext();

  void Init(RegalContext *share_ctx);

  Dispatcher          dispatcher;
  DispatchErrorState  err;
  DebugInfo          *dbg;
  ContextInfo        *info;
${EMU_MEMBER_DECLARE}

  #if defined(__native_client__)
  PPB_OpenGLES2      *naclES2;
  PP_Resource         naclResource;
  #endif

  RegalSystemContext  sysCtx;
  Thread              thread;

  GLLOGPROCREGAL      logCallback;

  // Per-frame state and configuration
  
  size_t              frame;
  Timer               frameTimer;

  size_t              frameSamples;
  Timer               frameSimpleTimeout;

  // State tracked via EmuContextState.py / Regal.cpp

  size_t              depthBeginEnd;   // Normally zero or one
  size_t              depthPushAttrib; //
};

REGAL_NAMESPACE_END

#endif // __${HEADER_NAME}_H__
''')

contextSourceTemplate = Template( '''${AUTOGENERATED}
${LICENSE}

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalConfig.h"
#include "RegalContext.h"
#include "RegalDebugInfo.h"
#include "RegalContextInfo.h"

${INCLUDES}#if REGAL_EMULATION
${EMU_INCLUDES}#endif

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

using namespace Logging;

RegalContext::RegalContext()
: dispatcher(),
  dbg(NULL),
  info(NULL),
${MEMBER_CONSTRUCT}#if REGAL_EMULATION
${EMU_MEMBER_CONSTRUCT}#endif
#if defined(__native_client__)
  naclES2(NULL),
  naclResource(NULL),
#endif
  sysCtx(NULL),
  thread(0),
  logCallback(NULL),
  frame(0),
  frameSamples(0),
  depthBeginEnd(0),
  depthPushAttrib(0)
{
  Internal("RegalContext::RegalContext","()");
  if (Config::enableDebug) {
    dbg = new DebugInfo();
    dbg->Init(this);
  }
  frameTimer.restart();
}

void
RegalContext::Init(RegalContext *share_ctx)
{
  Internal("RegalContext::Init","()");

  info = new ContextInfo();
  RegalAssert(this);
  RegalAssert(info);
  info->init(*this);

${MEMBER_INIT}

#if REGAL_EMULATION
#if !REGAL_FORCE_EMULATION
  if
  (
    Config::forceEmulation  ||
    (
      Config::enableEmulation &&
      (
        info->core ||
        info->gles ||
        ( info->compat && !info->gl_ext_direct_state_access )
      )
    )
  )
#endif
  {
    RegalAssert(info);
${EMU_MEMBER_INIT}
  }
#endif
}

RegalContext::~RegalContext()
{
  Internal("RegalContext::~RegalContext","()");
  delete info;
${MEMBER_CLEANUP}
#if REGAL_EMULATION
${EMU_MEMBER_CLEANUP}#endif
}

REGAL_NAMESPACE_END
''')

def generateContextHeader(apis, args):

    emuForwardDeclare = ''
    emuMemberDeclare  = ''

    for i in emuRegal:
      if i.get('member')!=None:
        emuForwardDeclare += 'struct %s;\n' % i['type']
        emuMemberDeclare  += '  %-18s *%s;\n' % ( i['type'], i['member'] )

    emuForwardDeclare += '#if REGAL_EMULATION\n'
    emuMemberDeclare  += '#if REGAL_EMULATION\n'

    emuMemberDeclare += '  // Fixed function emulation\n'
    emuMemberDeclare += '  int emuLevel;\n'

    for i in emu:
      if i.get('member')!=None:
        emuForwardDeclare += 'struct %s;\n' % i['type']
        emuMemberDeclare  += '  %-18s *%s;\n' % ( i['type'], i['member'] )

    emuForwardDeclare += '#endif\n'
    emuMemberDeclare  += '#endif\n'

    # Output

    substitute = {}

    substitute['LICENSE']       = args.license
    substitute['AUTOGENERATED'] = args.generated
    substitute['COPYRIGHT']     = args.copyright

    substitute['HEADER_NAME'] = "REGAL_CONTEXT"

    substitute['EMU_FORWARD_DECLARE'] = emuForwardDeclare
    substitute['EMU_MEMBER_DECLARE'] = emuMemberDeclare

    outputCode( '%s/RegalContext.h' % args.outdir, contextHeaderTemplate.substitute(substitute))

def generateContextSource(apis, args):

    includes           = ''
    memberConstruct    = ''
    memberInit         = ''
    memberCleanup      = ''
    emuIncludes        = ''
    emuMemberConstruct = ''
    emuMemberInit      = ''
    emuMemberCleanup   = ''

    for i in emuRegal:
      if i['member']:
        includes        += '#include "Regal%s.h"\n' % i['type']
        memberConstruct += '  %s(NULL),\n' % ( i['member'] )
        memberInit      += '  %s = new %s;\n'%(i['member'],i['type'])
        memberCleanup   += '  delete %s;\n' % i['member']

    emuMemberConstruct += '  emuLevel(0),\n'

    emuMemberInit += '    // emu\n'
    emuMemberInit += '    emuLevel = %d;\n' % ( len( emu ) - 1 )
    emuMemberCleanup += '  // emu\n'

    for i in range( len( emu ) - 1 ) :
      if emu[i]['member']:
        emuMemberConstruct += '  %s(NULL),\n' % emu[i]['member']

    for i in range( len( emu ) - 1 ) :
        if emu[i]['member']:
            emuIncludes += '#include "%s.h"\n' % emu[i]['type']
            emuMemberCleanup += '  delete %s;\n' % emu[i]['member']
        revi = len( emu ) - 2 - i;
        if emu[revi]['member']:
            init = ''
            if emu[revi]['member']=='dsa':
              init += 'Internal("RegalContext::Init ","GL_EXT_direct_state_access");\n'
              init += 'info->regal_ext_direct_state_access = true;\n'
#              init += '#ifndef REGAL_GL_EXTENSIONS\n'
              init += 'info->regalExtensionsSet.insert("GL_EXT_direct_state_access");\n'
              init += 'info->regalExtensions = ::boost::print::detail::join(info->regalExtensionsSet,std::string(" "));\n'
#              init += '#endif\n'

            init += '%s = new %s;\n' % ( emu[revi]['member'], emu[revi]['type'] )
            init += 'emuLevel = %d;\n' % ( int(emu[revi]['level']) - 1)
            init += '%s->Init(*this, share_ctx);\n' % emu[revi]['member']
            emuMemberInit += indent(wrapIf(emu[revi]['ifdef'],wrapCIf(emu[revi]['conditional'],init)),'    ')

    emuMemberInit += '    emuLevel = %d;\n' % ( len( emu ) - 1 )

    # Output

    substitute = {}

    substitute['LICENSE']       = args.license
    substitute['AUTOGENERATED'] = args.generated
    substitute['COPYRIGHT']     = args.copyright

    substitute['INCLUDES']             = includes
    substitute['MEMBER_CONSTRUCT']     = memberConstruct
    substitute['MEMBER_INIT']          = memberInit
    substitute['MEMBER_CLEANUP']       = memberCleanup
    substitute['EMU_INCLUDES']         = emuIncludes
    substitute['EMU_MEMBER_CONSTRUCT'] = emuMemberConstruct
    substitute['EMU_MEMBER_INIT']      = emuMemberInit
    substitute['EMU_MEMBER_CLEANUP']   = emuMemberCleanup

    outputCode( '%s/RegalContext.cpp' % args.outdir, contextSourceTemplate.substitute(substitute))
