#!/usr/bin/python -B

# Basic tracking at RegalContext level for global
# things such as glBegin/glEnd, glPush/glPop depth, etc

formulae = {
  'Begin' : {
    'entries' : [ 'glBegin' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthBeginEnd++;'
             ]
  },

  'End' : {
    'entries' : [ 'glEnd' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthBeginEnd--;'
             ]
  },

  'PushMatrix' : {
    'entries' : [ 'glPushMatrix' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthPushMatrix++;'
             ]
  },

  'PopMatrix' : {
    'entries' : [ 'glPopMatrix' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthPushMatrix--;'
             ]
  },

  'PushAttrib' : {
    'entries' : [ 'glPushAttrib' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthPushAttrib++;'
             ]
  },

  'PopAttrib' : {
    'entries' : [ 'glPopAttrib' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthPushAttrib--;'
             ]
  },

  'NewList' : {
    'entries' : [ 'glNewList' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthNewList++;'
             ]
  },

  'EndList' : {
    'entries' : [ 'glEndList' ],
    'impl' : [ 'RegalAssert(_context);',
               '_context->depthNewList--;'
             ]
  },

}
