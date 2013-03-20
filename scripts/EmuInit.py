#!/usr/bin/python -B

#
# Selectively initialize Regal for known initialization calls
# in addition to Regal API entry points.
#
# eglGetDisplay is needed for apitrace eglretrace tool.
#

formulae = {
  'EmuInit' : {
    'entries' : [ 'CGLChoosePixelFormat', 'eglGetDisplay' ],
    'prefix'  : [ 'Init::init();' ]
  }
}

#
# Hook into the MakeCurrent and DestroyContext functions in
# order to manage Regal contexts.
#

formulaeGlobal = {

    # WGL

    'wglMakeCurrent' : {
        'entries' : [ 'wglMakeCurrent' ],
        'init' : [ 'Init::makeCurrent(RegalSystemContext(hglrc));' ]
    },

    'wglDeleteContext' : {
        'entries' : [ 'wglDeleteContext' ],
        'init' : [ 'Init::destroyContext(RegalSystemContext(hglrc));' ]
    },

    # GLX

    'glXMakeCurrent' : {
        'entries' : [ 'glXMakeCurrent' ],
        'init' : [ 'Init::makeCurrent(RegalSystemContext(ctx));' ]
    },

    'glXDestroyContext' : {
        'entries' : [ 'glXDestroyContext' ],
        'init' : [ 'Init::destroyContext(RegalSystemContext(ctx));' ]
    },

    # EGL

    'eglMakeCurrent' : {
        'entries' : [ 'eglMakeCurrent' ],
        'init' : [ 'Init::makeCurrent(ctx);' ]
    },

    'eglDestroyContext' : {
        'entries' : [ 'eglDestroyContext' ],
        'init' : [ 'Init::destroyContext(RegalSystemContext(ctx));' ]
    },

    # CGL

    'CGLSetCurrentContext' : {
        'entries' : [ 'CGLSetCurrentContext' ],
        'init' : [ 'Init::makeCurrent(ctx);' ]
    },

    'CGLDestroyContext' : {
        'entries' : [ 'CGLDestroyContext' ],
        'init' : [ 'Init::destroyContext(RegalSystemContext(ctx));' ]
    },
}
