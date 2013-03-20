#!/usr/bin/python -B

#
# Filter or remap calls that don't exist for ES 2.0
#
# This is the last layer of the emulation dispatch.
#

# TODO List
#
#   - Partial list of entries not supported for ES 2.0
#     Can we do something more systematic for ES 2.0?
#     Perhaps for the Regal.cpp entry points, rather than
#     enlarging the emulation dispatch layer excessively?
#     Compile-time support for REGAL_SYS_ES2, etc would be
#     helpful too, in a desktop OpenGL situation.
#
#   - Partial GL_ARB_shader_objects remapping to OpenGL 2.0 / ES
#     Could be extended to a complete GL_ARB_shader_objects emulation layer?
#
#   - GL_ARB_vertex_program filtering for ES 2.0 isn't complete
#     In addition to matching by entry-point name, could we match
#     according to extension name too?

formulae = {

  # Skip calls that ES 2.0 and/or core do not support
  # Issues: This list is not complete

  'filterOutES2' : {
    'entries' : [
      'glClientActiveTexture',
      'glGenSamplers',                                   # Sampler object emulation
      'glGetTexImage',
      'glTexImage(1|3)D',
      'glBlitFramebufferEXT', 'glBlitFramebufferANGLE'   # Emulate glBlitFramebuffer?
    ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  Warning("Regal does not support ${name} for ES 2.0 - skipping.");',
       '  #if REGAL_BREAK',
       '  Break::Filter();',
       '  #endif',
       '  return ${dummyretval};',
       '}'
     ]
  },

  'filterOutCore' : {
    'entries' : [ 'glLineWidth', ],
    'impl' : [
       'if (_context->isCore())',
       '{',
       '   Warning("Regal does not support ${name} for core profile - skipping.");',
       '   #if REGAL_BREAK',
       '   Break::Filter();',
       '   #endif',
       '   return ${dummyretval};',
       '}'
     ]
  },

  'filterOutES2AndCore' : {
    'entries' : [
      'glAccum',
      'glBitmap',
      'glCallList',
      'glClearAccum',
      'glCopyPixels',
      'glDeleteLists',
      'glDrawPixels',
      'glEdgeFlag',
      'glEndList',
      'glEvalCoord(1|2)(d|f)(v|)',
      'glEvalMesh(1|2)',
      'glEvalPoint(1|2)',
      'glGenLists',
      'glGetTexLevelParameter(f|i)v',
      'glHint',
      'glLineStipple',
      'glMap(1|2)(d|f)',
      'glMapGrid(1|2)(d|f)',
      'glNewList',
      'glPixelStore(f|i)',
      'glPixelTransfer(f|i)',
      'glPixelZoom',
      'glRasterPos(2|3|4)(d|f|i|s)(v|)',
      'glRect(d|f|i|s)',
      'glShadeModel',
      'glWindowPos(2|3)(d|f|i|s)(v|)',
      ],
    'impl' : [
       'if (_context->isES2() || _context->isCore())',
       '{',
       '   Warning("Regal does not support ${name} for core or ES2 profiles - skipping.");',
       '   #if REGAL_BREAK',
       '   Break::Filter();',
       '   #endif',
       '   return ${dummyretval};',
       '}'
     ]
  },


  'filterArgs' : {
    'entries' : [
      'gl(BindTexture)',
      'gl(Get)(Boolean|Double|Float|Integer|Integer64)v',
      'gl(PolygonMode)',
      'gl(RenderMode)',
      'gl(TexParameter)(i|f)',
      ],
    'impl' : [
       '_context->filt->${m1}(*_context, ${arg0plus});',
       'if (_context->filt->Filtered())',
       '{',
       '  #if REGAL_BREAK',
       '  Break::Filter();',
       '  #endif',
       '  return ${dummyretval};',
       '}'
     ]
  },

  # Remap glBlitFramebuffer calls to GL_NV_framebuffer_blit
  # http://www.khronos.org/registry/gles/extensions/NV/GL_NV_framebuffer_blit.txt

  'blitFBO' : {
    'entries' : [ 'glBlitFramebuffer' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  if (_context->info->gl_nv_framebuffer_blit)  return _next->call(&_next->${m0}NV)(${arg0plus});',
       '  if (_context->info->gl_ext_framebuffer_blit) return _next->call(&_next->${m0}EXT)(${arg0plus});',
       '}'
     ]
  },

  # Filter out glDrawBuffer, glReadBuffer unless GL_NV_framebuffer_blit
  # or GL_EXT_framebuffer_blit is available

  'blitDrawRead' : {
    'entries' : [ 'glDrawBuffer', 'glReadBuffer' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  if (_context->info->gl_nv_framebuffer_blit || _context->info->gl_ext_framebuffer_blit)',
       '    return _next->call(&_next->${m0})(${arg0plus});',
       '}'
     ]
  },

  # Convert DrawRangeElements to ES DrawElements, ignoring second and third arguments

  'glDrawRangeElements' : {
    'entries' : [ 'glDrawRangeElements' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  return _next->call(&_next->glDrawElements)(${arg0}, ${arg3plus});',
       '}'
     ]
  },

  # Convert DrawRangeElementsBaseVertex to DrawElements iff baseVertex == 0
  # GL_ARB_draw_elements_base_vertex
  # http://www.opengl.org/registry/specs/ARB/draw_elements_base_vertex.txt

  'glDrawRangeElementsBaseVertex' : {
    'entries' : [ 'glDrawRangeElementsBaseVertex' ],
    'impl' : [
       'if (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_arb_draw_elements_base_vertex)',
       '{',
       '  if (basevertex==0)',
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    return _next->call(&_next->glDrawElements)(${arg0}, ${arg3}, ${arg4}, ${arg5});',
       '  }',
       '  else',
       '  {',
       '    Warning("Regal does not support ${name} (GL_ARB_draw_elements_base_vertex extension not available) for basevertex!=0 for ES 2.0 - skipping.");',
       '    return;',
       '  }',
       '}'
     ]
  },


  # http://www.opengl.org/registry/specs/ARB/vertex_program.txt
  # ARB assembly programs not supported or emulated for ES 2.0 (yet)

  'GL_ARB_vertex_program' : {
    'entries' : [ 'glGenProgramsARB', 'glBindProgramARB', 'glProgramStringARB', 'glGetProgramivARB' ],
    'impl' : [
      'if (_context->isES2())',
      '{',
      '  Warning("Regal does not support ${name} (GL_ARB_vertex_program) for ES 2.0 context - skipping.");',
      '  return;',
      '}'
     ]
  },

  # Remap GL_ARB_shader_objects to GL 2.0 API
  # http://www.opengl.org/registry/specs/ARB/shader_objects.txt
  #
  # TODO - Is this complete for GL_ARB_shader_objects API?

#    'glCreateShaderObjectARB' : {
#        'entries' : [ 'glCreateShaderObjectARB' ],
#        'impl' : [
#           '#if !REGAL_FORCE_ES2_PROFILE',
#           'if (_context->info->es2)',
#           '#endif',
#           '{',
#           '  DispatchTable *_next = _context->dispatcher.emulation._next;',
#           '  RegalAssert(_next);',
#           '  return _next->call(&_next->glCreateShader)(${arg0plus});',
#           '}'
#         ]
#    },

  'glCreateProgramObjectARB' : {
    'entries' : [ 'glCreateProgramObjectARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  return _next->call(&_next->glCreateProgram)(${arg0plus});',
      '}'
    ]
  },

#    'glShaderSourceARB' : {
#        'entries' : [ 'glShaderSourceARB' ],
#        'impl' : [
#           '#if !REGAL_FORCE_ES2_PROFILE',
#           'if (_context->info->es2)',
#           '#endif',
#           '{',
#           '  DispatchTable *_next = _context->dispatcher.emulation._next;',
#           '  RegalAssert(_next);',
#           '  _next->call(&_next->glShaderSource)(${arg0plus});',
#           '  return;',
#           '}'
#         ]
#    },

  'glCompileShaderARB' : {
    'entries' : [ 'glCompileShaderARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  _next->call(&_next->glCompileShader)(${arg0plus});',
      '  return;',
      '}'
    ]
  },

  'glAttachObjectARB' : {
    'entries' : [ 'glAttachObjectARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  _next->call(&_next->glAttachShader)(${arg0plus});',
      '  return;',
      '}'
    ]
  },

  'glBindAttribLocationARB' : {
    'entries' : [ 'glBindAttribLocationARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  _next->call(&_next->glBindAttribLocation)(${arg0plus});',
      '  return;',
      '}'
    ]
  },

  'glGetUniformLocationARB' : {
    'entries' : [ 'glGetUniformLocationARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  return _next->call(&_next->glGetUniformLocation)(${arg0plus});',
      '}'
    ]
  },

  'glUniform1iARB' : {
    'entries' : [ 'glUniform1iARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
      '{',
      '  DispatchTable *_next = _context->dispatcher.emulation._next;',
      '  RegalAssert(_next);',
      '  _next->call(&_next->glUniform1i)(${arg0plus});',
      '  return;',
      '}'
    ]
 },

  'glGetObjectParameterivARB' : {
    'entries' : [ 'glGetObjectParameterivARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  if (_next->call(&_next->glIsProgram)(obj))',
       '    _next->call(&_next->glGetProgramiv)(${arg0plus});',
       '  else',
       '    _next->call(&_next->glGetShaderiv)(${arg0plus});',
       '  return;',
       '}'
     ]
  },

  'glGetInfoLogARB' : {
    'entries' : [ 'glGetInfoLogARB' ],
    'impl' : [
      'if (_context->isES2() || !_context->info->gl_arb_shader_objects)',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  if (_next->call(&_next->glIsProgram)(obj))',
       '    _next->call(&_next->glGetProgramInfoLog)(${arg0plus});',
       '  else',
       '    _next->call(&_next->glGetShaderInfoLog)(${arg0plus});',
       '  return;',
       '}'
     ]
  },

# http://www.opengl.org/registry/specs/ARB/vertex_buffer_object.txt
# Map to GL_OES_mapbuffer for ES 2.0

  'glMapBufferARB' : {
    'entries' : [ 'glMapBufferARB' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  return _next->call(&_next->glMapBufferOES)(${arg0plus});',
       '}'
     ]
  },

  'glBufferDataARB' : {
    'entries' : [ 'glBufferDataARB' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  DispatchTable *_next = _context->dispatcher.emulation._next;',
       '  RegalAssert(_next);',
       '  _next->call(&_next->glBufferData)(${arg0plus});',
       '  return;',
       '}'
     ]
  },

# http://www.opengl.org/registry/specs/ARB/framebuffer_object.txt
# Force target = GL_FRAMEBUFFER for ES 2.0

  'glBindFramebuffer' : {
    'entries' : [ 'glBindFramebuffer','glBindFramebufferEXT','glBindFramebufferOES' ],
    'impl' : [
       'if (_context->isES2())',
       '{',
       '  const bool hasFBBlit = _context->info->gl_ext_framebuffer_blit || _context->info->gl_nv_framebuffer_blit || _context->info->gl_version_major >= 3;',
       '  if (!hasFBBlit && (target==GL_DRAW_FRAMEBUFFER || target==GL_READ_FRAMEBUFFER)) target = GL_FRAMEBUFFER;',
       '}'
     ]
  },

#
# http://www.opengl.org/registry/specs/ARB/draw_buffers.txt
# http://www.opengl.org/registry/specs/EXT/draw_buffers2.txt
#
# Without MRT, limit calls to DRAW_BUFFER0_ARB for ES 2.0
#

  'glColorMaskIndexedEXT' : {
    'entries' : [ 'glColorMaskIndexedEXT' ],
    'impl' : [
       'if (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_ext_draw_buffers2)',
       '{',
       '  if (!buf)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    _next->call(&_next->glColorMask)(${arg1plus});',
       '  }',
       '  return;',
       '}'
     ]
  },

  'glGetBooleanIndexedvEXT' : {
    'entries' : [ 'glGetBooleanIndexedvEXT' ],
    'impl' : [
       'if (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_ext_draw_buffers2)',
       '{',
       '  if (!index)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    _next->call(&_next->glGetBooleanv)(${arg0},${arg2});',
       '  }',
       '  return;',
       '}'
     ]
  },

  'glGetIntegerIndexedvEXT' : {
    'entries' : [ 'glGetIntegerIndexedvEXT' ],
    'impl' : [
       'if (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_ext_draw_buffers2)',
       '{',
       '  if (!index)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    _next->call(&_next->glGetIntegerv)(${arg0},${arg2});',
       '  }',
       '  return;',
       '}'
     ]
  },

  'glEnableIndexedEXT' : {
    'entries' : [ 'glEnableIndexedEXT' ],
    'impl' : [
       'if (${arg0}==GL_BLEND && (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_ext_draw_buffers2))',
       '{',
       '  if (!index)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    _next->call(&_next->glEnable)(${arg0});',
       '  }',
       '  return;',
       '}'
     ]
  },

  'glDisableIndexedEXT' : {
    'entries' : [ 'glDisableIndexedEXT' ],
    'impl' : [
       'if (${arg0}==GL_BLEND && (REGAL_FORCE_ES2_PROFILE || !_context->info->gl_ext_draw_buffers2))',
       '{',
       '  if (!index)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    _next->call(&_next->glDisable)(${arg0});',
       '  }',
       '  return;',
       '}'
     ]
  },

  'glIsEnabledIndexedEXT' : {
    'entries' : [ 'glIsEnabledIndexedEXT' ],
    'impl' : [
       'if (${arg0}==GL_BLEND && !_context->info->gl_ext_draw_buffers2)',
       '{',
       '  if (!index)'
       '  {',
       '    DispatchTable *_next = _context->dispatcher.emulation._next;',
       '    RegalAssert(_next);',
       '    return _next->call(&_next->glIsEnabled)(${arg0});',
       '  }',
       '  return GL_FALSE;',
       '}'
     ]
  }

}
