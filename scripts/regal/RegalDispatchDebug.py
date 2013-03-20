#!/usr/bin/python -B

from string import Template, upper, replace

from ApiUtil import outputCode
from ApiUtil import typeIsVoid

from ApiCodeGen import *

from RegalDispatchLog import apiDispatchFuncInitCode
from RegalDispatchEmu import dispatchSourceTemplate
from RegalContextInfo import cond

from Emu       import emuFindEntry, emuCodeGen

from DispatchDebug import debugDispatchFormulae

##############################################################################################

# CodeGen for API debug function definition.

def apiDebugFuncDefineCode(apis, args):
  categoryPrev = None
  code = ''

  for api in apis:

    code += '\n'
    if api.name in cond:
      code += '#if %s\n' % cond[api.name]

    for function in api.functions:
      if not function.needsContext:
        continue
      if getattr(function,'regalOnly',False)==True:
        continue

      name   = function.name
      params = paramsDefaultCode(function.parameters, True)
      callParams = paramsNameCode(function.parameters)
      rType  = typeCode(function.ret.type)
      category  = getattr(function, 'category', None)
      version   = getattr(function, 'version', None)

      if category:
        category = category.replace('_DEPRECATED', '')
      elif version:
        category = version.replace('.', '_')
        category = 'GL_VERSION_' + category

      # Close prev category block.
      if categoryPrev and not (category == categoryPrev):
        code += '\n'

      # Begin new category block.
      if category and not (category == categoryPrev):
        code += '// %s\n\n' % category

      categoryPrev = category

      code += 'static %sREGAL_CALL %s%s(%s) \n{\n' % (rType, 'debug_', name, params)
      code += '  RegalContext *_context = REGAL_GET_CONTEXT();\n'
      code += '  RegalAssert(_context);\n'
      code += '  DispatchTable *_next = _context->dispatcher.debug._next;\n'
      code += '  RegalAssert(_next);\n'
      e = emuFindEntry( function, debugDispatchFormulae, '' )
      if e != None and 'prefix' in e :
        for l in e['prefix'] :
          code += '  %s\n' % l
      code += '  '
      if not typeIsVoid(rType):
        code += '%s ret = ' % rType
      code += '_next->call(&_next->%s)(%s);\n' % ( name, callParams )
      if not typeIsVoid(rType):
        code += '  return ret;\n'
      code += '}\n\n'

    if api.name in cond:
      code += '#endif // %s\n' % cond[api.name]
    code += '\n'

  # Close pending if block.
  if categoryPrev:
    code += '\n'

  return code

debugGlobalCode = '''
#include "RegalDebugInfo.h"
'''

debugLocalCode = '''
'''

def generateDebugSource(apis, args):

  funcDefine = apiDebugFuncDefineCode( apis, args )
  funcInit   = apiDispatchFuncInitCode( apis, args, 'debug' )

  # Output

  substitute = {}

  substitute['LICENSE']         = args.license
  substitute['AUTOGENERATED']   = args.generated
  substitute['COPYRIGHT']       = args.copyright
  substitute['DISPATCH_NAME']   = 'Debug'
  substitute['LOCAL_INCLUDE']   = debugGlobalCode
  substitute['LOCAL_CODE']      = debugLocalCode
  substitute['API_DISPATCH_FUNC_DEFINE'] = funcDefine
  substitute['API_DISPATCH_FUNC_INIT'] = funcInit
  substitute['IFDEF'] = '#if REGAL_DEBUG\n\n'
  substitute['ENDIF'] = '#endif\n'

  outputCode( '%s/RegalDispatchDebug.cpp' % args.srcdir, dispatchSourceTemplate.substitute(substitute))

