#!/usr/bin/python -B

formulae = {

}

formulaeGlobal = {

    # GL_GREMEDY_frame_terminator

    'GL_GREMEDY_frame_terminator' : {
        'entries' : [ 'glFrameTerminatorGREMEDY' ],
        'impl' : [ 'if (_context && _context->frame)',
                   '  _context->frame->glFrameTerminatorGREMEDY(*_context);',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_gremedy_frame_terminator) return;' ]
    },

    # wglSwapBuffers

    'wglSwapBuffers' : {
        'entries' : [ 'wglSwapBuffers' ],
        'impl' : [ 'RegalContext *_context = REGAL_GET_CONTEXT();',
                   'if (_context && _context->frame)',
                   '    _context->frame->wglSwapBuffers(*_context);'
                 ]
    },

    # glXSwapBuffers

    'glXSwapBuffers' : {
        'entries' : [ 'glXSwapBuffers' ],
        'impl' : [ 'RegalContext *_context = REGAL_GET_CONTEXT();',
                   'if (_context && _context->frame)',
                   '    _context->frame->glXSwapBuffers(*_context);'
                 ]
    },

    # eglSwapBuffers

    'eglSwapBuffers' : {
        'entries' : [ 'eglSwapBuffers' ],
        'impl' : [ 'RegalContext *_context = REGAL_GET_CONTEXT();',
                   'if (_context && _context->frame)',
                   '    _context->frame->eglSwapBuffers(*_context);'
                 ]
    },

    # CGLFlushDrawable

    'CGLFlushDrawable' : {
        'entries' : [ 'CGLFlushDrawable' ],
        'impl' : [ 'RegalContext *_context = REGAL_GET_CONTEXT();',
                   'if (_context && _context->frame)',
                   '    _context->frame->CGLFlushDrawable(*_context);'
                 ]
    }

}