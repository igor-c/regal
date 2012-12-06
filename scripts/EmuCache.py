#!/usr/bin/python -B

# Regal.cpp - Application-side shader caching
#
# Note - for driver-side caching, RegalDispatchCache.cpp is used.

formulaeGlobal = {

    'glShaderSource' : {
        'entries' : [ 'glShaderSource' ],
        'suffix' : [
          'if (REGAL_CACHE && REGAL_CACHE_SHADER)\n',
          '{',
          '  ShaderCache::shaderSource(_next->call(&_next->glShaderSource), shader, count, string, length);',
          '  return;',
          '}'
        ]
    }
}
