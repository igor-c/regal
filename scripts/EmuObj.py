#!/usr/bin/python -B

objFormulae = {
    'Buffers' : {
        'entries' : [ 'gl(GenBuffers|DeleteBuffers|BindBuffer)(ARB|)' ],
        'impl' : [ '_context->obj->${m1}( _context, ${arg0plus} );', ],
    },
    'VAOs' : {
        'entries' : [ 'gl(GenVertexArrays|DeleteVertexArrays|BindVertexArray)(ARB|)' ],
        'impl' : [ '_context->obj->${m1}( _context, ${arg0plus} );', ],
    },
    'Textures' : {
        'entries' : [ 'gl(GenTextures|DeleteTextures|BindTexture)' ],
        'impl' : [ '_context->obj->${m1}( _context, ${arg0plus} );', ],
    },
    'IsObj' : {
        'entries' : [ 'glIs(Buffer|VertexArray|Texture)(ARB|)' ],
        'impl' : [ 'return _context->obj->Is${m1}( _context, ${arg0plus} );', ],
    },
}
