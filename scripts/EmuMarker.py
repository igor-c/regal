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

    # GL_GREMEDY_string_marker

    'GL_GREMEDY_string_marker' : {
        'entries' : [ 'glStringMarkerGREMEDY' ],
        'impl' : [ 'if (_context && _context->marker)',
                   '  _context->marker->InsertEventMarker( *_context, ${arg0plus} );',
                   'RegalAssert(_context->info);',
                   'if (!_context->info->gl_gremedy_string_marker) return;' ]
    }
}
