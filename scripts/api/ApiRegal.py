#!/usr/bin/python -B

#
# API utility functions for Regal code generation
#

#from string       import Template, upper, replace
from copy         import deepcopy

from ApiUtil      import typeIsVoid
from ApiUtil      import toLong
from ApiUtil      import hexValue
from ApiCodeGen   import *

#
# Map gl.py helper functions to C++ Regal namespace
#

helperMap = {
  'helperGLGetSize'               : 'helper::size::get',
  'helperGLCallListsSize'         : 'helper::size::callLists',
  'helperGLFogvSize'              : 'helper::size::fogv',
  'helperGLLightvSize'            : 'helper::size::lightv',
  'helperGLLightModelvSize'       : 'helper::size::lightModelv',
  'helperGLMaterialvSize'         : 'helper::size::materialv',
  'helperGLTexParametervSize'     : 'helper::size::texParameterv',
  'helperGLTexEnvvSize'           : 'helper::size::texEnvv',
  'helperGLTexGenvSize'           : 'helper::size::texGenv',
  'helperGLNamedStringSize'       : 'helper::size::namedString',
  'helperGLSamplerParametervSize' : 'helper::size::samplerParameterv',
#  'helperGLDrawElementsSize'      : 'helper::size::drawElements',
  'helperGLNamedStringParamsSize' : 'helper::size::namedStringParams'
#  'helperGLPixelImageSize'        : 'helper::size::pixelImageSize'
}

def logParameter(function, parameter):

  t = parameter.type   # Type
  n = parameter.name   # Name
  h = None             # Helper

  # Apply the database specified cast, if necessary

  if parameter.cast != None:
    t = parameter.cast
    n = 'reinterpret_cast<%s>(%s)'%(t,n)

  # Extract the name of the helper function, if possible
  
  if parameter.size!=None and (isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and parameter.size.find('helper')==0:
    h = parameter.size.split('(')[0]
    if h in helperMap:
      h = helperMap[h]
    else:
      h = None

  # Quoting for array of strings

  quote = ''
  if t in [ 'char **','const char **','GLchar **' ,'const GLchar **','GLcharARB **','const GLcharARB **','LPCSTR *']:
    quote = ',"\\\""'

  if parameter.regalLog != None:
    return '%s'%parameter.regalLog
  elif t == 'GLenum':
    return 'toString(%s)'%n
  elif t == 'GLXenum':
    return 'GLXenumToString(%s)'%n
  elif t == 'EGLenum':
    return 'EGLenumToString(%s)'%n
  elif t == 'GLboolean' or t == 'const GLboolean':
    return 'toString(%s)'%n
  elif t in [ 'char *','const char *','GLchar *' ,'const GLchar *','GLcharARB *','const GLcharARB *','LPCSTR']:
    return 'boost::print::quote(%s,\'"\')'%n
  elif parameter.size!=None and (isinstance(parameter.size,int) or isinstance(parameter.size, long)) and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1:
    return 'boost::print::array(%s,%s)'%(n,parameter.size)
  elif parameter.size!=None and (isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1 and parameter.size.find('helper')==-1:
    return 'boost::print::array(%s,%s%s)'%(n,parameter.size,quote)
#   elif parameter.size!=None and (isinstance(parameter.size,int) or isinstance(parameter.size, long) or isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and t=='const GLvoid *':
#     return 'boost::print::raw(%s,%s)'%(n,parameter.size)
  elif parameter.size!=None and h!=None and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1:
    return 'boost::print::array(%s,%s(%s%s)'%(n,h,parameter.size.split('(',1)[1],quote)
  elif t.startswith('GLDEBUG'):
    return None
  elif t.startswith('GLLOGPROC'):
    return None
  elif n=='data' and (function.name=='glBufferData' or function.name=='glBufferDataARB'):
    return 'boost::print::raw(data,Logging::rawLimit(data ? size : 0))'
  elif n=='data' and (function.name=='glBufferSubData' or function.name=='glBufferSubDataARB'):
    return 'boost::print::raw(data,Logging::rawLimit(data ? size : 0))'
  elif t in [ 'void *', 'const void *', 'GLvoid *', 'const GLvoid *', 'GLubyte *', 'const GLubyte *'] or \
    t in [ 'int *', 'const int *', 'GLint *', 'const GLint *' ] or \
    t in [ 'XID', 'XVisualInfo *', 'Pixmap', 'Font', 'Display *', 'GLXDrawble', 'GLXPixmap', 'GLXContext', 'GLXVideoDeviceNV', 'GLXWindow', 'GLXPbuffer', 'GLXFBConfigID'] or \
    t in [ 'PVOID', 'LPVOID', 'HDC', 'HGLRC', 'HPBUFFERARB', 'HPBUFFEREXT', 'HGPUNV', 'HPVIDEODEV', 'HVIDEOINPUTDEVICENV', 'HVIDEOOUTPUTDEVICENV', 'PGPU_DEVICE' ] or \
    t in [ 'EGLNativeWindowType', 'EGLNativePixmapType', 'EGLNativeDisplayType', 'EGLConfig', 'EGLContext', 'EGLDisplay', 'EGLSurface', 'EGLClientBuffer', 'EGLSyncKHR', 'EGLImageKHR', 'EGLStreamKHR', 'EGLSyncNV']:    
    return 'boost::print::optional(%s,Logging::pointers)'%n

  return n

def cCodeParameter(function, parameter):

  t = parameter.type
  n = parameter.name

  # Use a cast, if necessary

  if parameter.cast != None:
    t = parameter.cast
    n = 'reinterpret_cast<%s>(%s)'%(t,n)

  # Quoting for array of strings

  quote = ''
  if t == 'char **' or t == 'const char **' or t == 'GLchar **' or t == 'const GLchar **' or t == 'GLcharARB *' or t == 'LPCSTR *':
    quote = ',"\\\""'

  if parameter.regalLog != None:
    return '%s'%parameter.regalLog
  elif t == 'GLenum':
    return 'toString(%s)'%n
  elif t == 'GLXenum':
    return 'GLXenumToString(%s)'%n
  elif t == 'EGLenum':
    return 'EGLenumToString(%s)'%n
  elif t == 'GLboolean' or t == 'const GLboolean':
    return 'toString(%s)'%n
  elif t == 'char *' or t == 'const char *' or t == 'GLchar *' or t == 'const GLchar *' or t == 'GLcharARB *' or t == 'LPCSTR':
    return None
  elif parameter.size!=None and (isinstance(parameter.size,int) or isinstance(parameter.size, long)) and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1:
    return None
  elif parameter.size!=None and (isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1 and parameter.size.find('helper')==-1:
    return None
#   elif parameter.size!=None and (isinstance(parameter.size,int) or isinstance(parameter.size, long) or isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and t=='const GLvoid *':
#    return None
  elif parameter.size!=None and (isinstance(parameter.size, str) or isinstance(parameter.size, unicode)) and t.find('void')==-1 and t.find('PIXELFORMATDESCRIPTOR')==-1 and parameter.size.find('helper')==0:
    h = parameter.size.split('(')[0]
    if h in helperMap:
      return None
    else:
      return n
  elif t.startswith('GLDEBUG'):
    return None
  elif t.startswith('GLLOGPROC'):
    return None
  elif n=='data' and (function.name=='glBufferData' or function.name=='glBufferDataARB'):
    return None
  elif n=='data' and (function.name=='glBufferSubData' or function.name=='glBufferSubDataARB'):
    return None

  return n

#
# debug print function
#
# trace  - logging mode: Internal, App or Driver
# input  - input parameters
# output - output parameters
# ret    - return value
#
 
def logFunction(function, trace = 'ITrace', input = True, output = False, ret = False):
  c =  ''
  args = []
  for i in function.parameters:

    if not output and i.output:
      continue

    if not input and not i.output:
      continue

    j = logParameter(function,i)
    if j:
      args.append(j)

  r = None
  if ret and function.ret != None:
    tmp = deepcopy(function.ret)
    tmp.name = 'ret'
    r = logParameter(function,tmp)

  args = args[:9]
  if len(args):
    c += '%s("%s","(", ' % (trace, function.name)
    c += ', ", ", '.join(args)
    c += ', ")"'
    if r != None:
      c += ', " returned ", %s'%(r)
    c += ');'
  else:
    c += '%s("%s","()"' % (trace, function.name)
    if r != None:
      c += ', " returned ", %s'%(r)
    c += ');'
  return c

