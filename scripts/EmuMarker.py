#!/usr/bin/python -B

formulae = {

}

formulaeGlobal = {

    # GL_EXT_debug_marker

    'Insert' : {
        'entries' : [ 'glInsertEventMarkerEXT' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context, ${arg0plus} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_ext_debug_marker) return;' ]
    },
    'Push' : {
        'entries' : [ 'glPushGroupMarkerEXT' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->PushGroupMarker( *_context, ${arg0plus} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_ext_debug_marker) return;' ]
    },
    'Pop' : {
        'entries' : [ 'glPopGroupMarkerEXT' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->PopGroupMarker( *_context );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_ext_debug_marker) return;' ]
    },

    # GL_KHR_debug
    # http://www.opengl.org/registry/specs/KHR/debug.txt
    #
    # glDebugMessageInsert
    # glPushDebugGroup
    # glPopDebugGroup

    'KHR_debug Push' : {
        'entries' : [ 'glPushDebugGroup' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->PushGroupMarker( *_context, ${arg2plus} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_khr_debug) return;' ]
    },
    'KHR_debug Pop' : {
        'entries' : [ 'glPopDebugGroup' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->PopGroupMarker( *_context );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_khr_debug) return;' ]
    },

    'KHR_debug Insert' : {
        'entries' : [ 'glDebugMessageInsert' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context,${arg4},${arg5} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_khr_debug) return;' ]
    },

    # GL_ARB_debug_output
    # http://www.opengl.org/registry/specs/ARB/debug_output.txt
    #
    # glDebugMessageInsertARB

    'ARB_debug_output Insert' : {
        'entries' : [ 'glDebugMessageInsertARB' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context,${arg4},${arg5} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_arb_debug_output) return;' ]
    },

    # GL_AMD_debug_output
    # http://www.opengl.org/registry/specs/AMD/debug_output.txt
    #
    # glDebugMessageInsertAMD

    'AMD_debug_output Insert' : {
        'entries' : [ 'glDebugMessageInsertAMD' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context,${arg3},${arg4} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_amd_debug_output) return;' ]
    },

    # GL_GREMEDY_string_marker

    'GL_GREMEDY_string_marker' : {
        'entries' : [ 'glStringMarkerGREMEDY' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context, ${arg0plus} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_gremedy_string_marker) return;' ]
    }
}
