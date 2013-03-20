/*
  Copyright (c) 2011 NVIDIA Corporation
  Copyright (c) 2011-2012 Cass Everitt
  Copyright (c) 2012 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012 Nigel Stewart
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include "RegalHelper.h"

using std::size_t;

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace helper { namespace size {

size_t
get(GLenum pname)
{
  size_t size = 0;

  switch (pname)
  {
    // ES 1.1
    // http://www.khronos.org/opengles/sdk/1.1/docs/man/glGet.xml

    case GL_ACCUM_ALPHA_BITS:                              size = 1;  break;
    case GL_ACCUM_BLUE_BITS:                               size = 1;  break;
    case GL_ACCUM_CLEAR_VALUE:                             size = 4;  break;
    case GL_ACCUM_GREEN_BITS:                              size = 1;  break;
    case GL_ACCUM_RED_BITS:                                size = 1;  break;
    case GL_ACTIVE_STENCIL_FACE_EXT:                       size = 1;  break;
    case GL_ACTIVE_TEXTURE:                                size = 1;  break;
    case GL_ALIASED_LINE_WIDTH_RANGE:                      size = 2;  break;
    case GL_ALIASED_POINT_SIZE_RANGE:                      size = 2;  break;
    case GL_ALPHA_BIAS:                                    size = 1;  break;
    case GL_ALPHA_BITS:                                    size = 1;  break;
    case GL_ALPHA_SCALE:                                   size = 1;  break;
    case GL_ALPHA_TEST:                                    size = 1;  break;
    case GL_ALPHA_TEST_FUNC:                               size = 1;  break;
    case GL_ALPHA_TEST_REF:                                size = 1;  break;
    case GL_ARRAY_BUFFER_BINDING:                          size = 1;  break;
    case GL_ARRAY_ELEMENT_LOCK_COUNT_EXT:                  size = 1;  break;
    case GL_ARRAY_ELEMENT_LOCK_FIRST_EXT:                  size = 1;  break;
    case GL_ATTRIB_STACK_DEPTH:                            size = 1;  break;
    case GL_AUTO_NORMAL:                                   size = 1;  break;
    case GL_AUX_BUFFERS:                                   size = 1;  break;
    case GL_BLEND:                                         size = 1;  break;
    case GL_BLEND_COLOR:                                   size = 4;  break;
    case GL_BLEND_DST:                                     size = 1;  break;
    case GL_BLEND_DST_ALPHA_EXT:                           size = 1;  break;
    case GL_BLEND_DST_RGB_EXT:                             size = 1;  break;
    case GL_BLEND_EQUATION:                                size = 1;  break;
    case GL_BLEND_EQUATION_ALPHA_EXT:                      size = 1;  break;
    case GL_BLEND_SRC:                                     size = 1;  break;
    case GL_BLEND_SRC_ALPHA_EXT:                           size = 1;  break;
    case GL_BLEND_SRC_RGB_EXT:                             size = 1;  break;
    case GL_BLUE_BIAS:                                     size = 1;  break;
    case GL_BLUE_BITS:                                     size = 1;  break;
    case GL_BLUE_SCALE:                                    size = 1;  break;
    case GL_CLAMP_FRAGMENT_COLOR_ARB:                      size = 1;  break;
    case GL_CLAMP_READ_COLOR_ARB:                          size = 1;  break;
    case GL_CLAMP_VERTEX_COLOR_ARB:                        size = 1;  break;
    case GL_CLIENT_ACTIVE_TEXTURE:                         size = 1;  break;
    case GL_CLIENT_ATTRIB_STACK_DEPTH:                     size = 1;  break;
    case GL_CLIP_PLANE0:                                   size = 1;  break;
    case GL_CLIP_PLANE1:                                   size = 1;  break;
    case GL_CLIP_PLANE2:                                   size = 1;  break;
    case GL_CLIP_PLANE3:                                   size = 1;  break;
    case GL_CLIP_PLANE4:                                   size = 1;  break;
    case GL_CLIP_PLANE5:                                   size = 1;  break;
//    case GL_CLIP_PLANE6:                                 size = 1;  break;
//    case GL_CLIP_PLANE7:                                 size = 1;  break;
    case GL_COLOR_ARRAY:                                   size = 1;  break;
    case GL_COLOR_ARRAY_BUFFER_BINDING:                    size = 1;  break;
    case GL_COLOR_ARRAY_COUNT_EXT:                         size = 1;  break;
    case GL_COLOR_ARRAY_SIZE:                              size = 1;  break;
    case GL_COLOR_ARRAY_STRIDE:                            size = 1;  break;
    case GL_COLOR_ARRAY_TYPE:                              size = 1;  break;
    case GL_COLOR_CLEAR_VALUE:                             size = 4;  break;
    case GL_COLOR_LOGIC_OP:                                size = 1;  break;
    case GL_COLOR_MATERIAL:                                size = 1;  break;
    case GL_COLOR_MATERIAL_FACE:                           size = 1;  break;
    case GL_COLOR_MATERIAL_PARAMETER:                      size = 1;  break;
    case GL_COLOR_MATRIX:                                  size = 16; break;
    case GL_COLOR_MATRIX_STACK_DEPTH:                      size = 1;  break;
    case GL_COLOR_SAMPLES_NV:                              size = 1;  break;
    case GL_COLOR_SUM_ARB:                                 size = 1;  break;
    case GL_COLOR_SUM_CLAMP_NV:                            size = 1;  break;
    case GL_COLOR_TABLE:                                   size = 1;  break;
    case GL_COLOR_WRITEMASK:                               size = 4;  break;
    case GL_COMPRESSED_TEXTURE_FORMATS:                    size = 1;  break;
    case GL_CONSTANT_COLOR0_NV:                            size = 4;  break;
    case GL_CONSTANT_COLOR1_NV:                            size = 4;  break;
    case GL_CONVOLUTION_1D:                                size = 1;  break;
    case GL_CONVOLUTION_2D:                                size = 1;  break;
    case GL_CULL_FACE:                                     size = 1;  break;
    case GL_CULL_FACE_MODE:                                size = 1;  break;
    case GL_CURRENT_COLOR:                                 size = 4;  break;
    case GL_CURRENT_FOG_COORD:                             size = 1;  break;
    case GL_CURRENT_INDEX:                                 size = 1;  break;
    case GL_CURRENT_MATRIX_NV:                             size = 16; break;
    case GL_CURRENT_MATRIX_STACK_DEPTH_NV:                 size = 1;  break;
    case GL_CURRENT_NORMAL:                                size = 3;  break;
    case GL_CURRENT_OCCLUSION_QUERY_ID_NV:                 size = 1;  break;
    case GL_CURRENT_PROGRAM:                               size = 1;  break;
    case GL_CURRENT_RASTER_COLOR:                          size = 4;  break;
    case GL_CURRENT_RASTER_DISTANCE:                       size = 1;  break;
    case GL_CURRENT_RASTER_INDEX:                          size = 1;  break;
    case GL_CURRENT_RASTER_POSITION:                       size = 4;  break;
    case GL_CURRENT_RASTER_POSITION_VALID:                 size = 1;  break;
    case GL_CURRENT_RASTER_SECONDARY_COLOR:                size = 4;  break;
    case GL_CURRENT_RASTER_TEXTURE_COORDS:                 size = 4;  break;
    case GL_CURRENT_SECONDARY_COLOR:                       size = 4;  break;
    case GL_CURRENT_TEXTURE_COORDS:                        size = 4;  break;
    case GL_DEPTH_BIAS:                                    size = 1;  break;
    case GL_DEPTH_BITS:                                    size = 1;  break;
    case GL_DEPTH_BOUNDS_EXT:                              size = 2;  break;
    case GL_DEPTH_BOUNDS_TEST_EXT:                         size = 1;  break;
    case GL_DEPTH_BUFFER_FLOAT_MODE_NV:                    size = 1;  break;
    case GL_DEPTH_CLEAR_VALUE:                             size = 1;  break;
    case GL_DEPTH_FUNC:                                    size = 1;  break;
    case GL_DEPTH_RANGE:                                   size = 2;  break;
    case GL_DEPTH_SCALE:                                   size = 1;  break;
    case GL_DEPTH_TEST:                                    size = 1;  break;
    case GL_DEPTH_WRITEMASK:                               size = 1;  break;
    case GL_DITHER:                                        size = 1;  break;
    case GL_DOUBLEBUFFER:                                  size = 1;  break;
    case GL_DRAW_BUFFER:                                   size = 1;  break;
    case GL_DRAW_BUFFER0:                                  size = 1;  break;
    case GL_DRAW_BUFFER1:                                  size = 1;  break;
    case GL_DRAW_BUFFER10:                                 size = 1;  break;
    case GL_DRAW_BUFFER11:                                 size = 1;  break;
    case GL_DRAW_BUFFER12:                                 size = 1;  break;
    case GL_DRAW_BUFFER13:                                 size = 1;  break;
    case GL_DRAW_BUFFER14:                                 size = 1;  break;
    case GL_DRAW_BUFFER15:                                 size = 1;  break;
    case GL_DRAW_BUFFER2:                                  size = 1;  break;
    case GL_DRAW_BUFFER3:                                  size = 1;  break;
    case GL_DRAW_BUFFER4:                                  size = 1;  break;
    case GL_DRAW_BUFFER5:                                  size = 1;  break;
    case GL_DRAW_BUFFER6:                                  size = 1;  break;
    case GL_DRAW_BUFFER7:                                  size = 1;  break;
    case GL_DRAW_BUFFER8:                                  size = 1;  break;
    case GL_DRAW_BUFFER9:                                  size = 1;  break;
    case GL_DS_BIAS_NV:                                    size = 1;  break;
    case GL_DS_SCALE_NV:                                   size = 1;  break;
    case GL_DT_BIAS_NV:                                    size = 1;  break;
    case GL_DT_SCALE_NV:                                   size = 1;  break;
    case GL_EDGE_FLAG:                                     size = 1;  break;
    case GL_EDGE_FLAG_ARRAY:                               size = 1;  break;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:                  size = 1;  break;
    case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB:            size = 1;  break;
    case GL_EDGE_FLAG_ARRAY_COUNT_EXT:                     size = 1;  break;
    case GL_EDGE_FLAG_ARRAY_STRIDE:                        size = 1;  break;
    case GL_FEEDBACK_BUFFER_SIZE:                          size = 1;  break;
    case GL_FEEDBACK_BUFFER_TYPE:                          size = 1;  break;
    case GL_FLOAT_CLEAR_COLOR_VALUE_NV:                    size = 4;  break;
    case GL_FLOAT_RGBA_MODE_NV:                            size = 1;  break;
    case GL_FOG:                                           size = 1;  break;
    case GL_FOG_COLOR:                                     size = 4;  break;
    case GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB:       size = 1;  break;
    case GL_FOG_COORD_ARRAY:                               size = 1;  break;
    case GL_FOG_COORD_ARRAY_STRIDE:                        size = 1;  break;
    case GL_FOG_COORD_ARRAY_TYPE:                          size = 1;  break;
    case GL_FOG_COORD_SRC:                                 size = 1;  break;
    case GL_FOG_DENSITY:                                   size = 1;  break;
    case GL_FOG_DISTANCE_MODE_NV:                          size = 1;  break;
    case GL_FOG_END:                                       size = 1;  break;
    case GL_FOG_HINT:                                      size = 1;  break;
    case GL_FOG_INDEX:                                     size = 1;  break;
    case GL_FOG_MODE:                                      size = 1;  break;
    case GL_FOG_START:                                     size = 1;  break;
    case GL_FRAGMENT_PROGRAM_ARB:                          size = 1;  break;
    case GL_FRAGMENT_PROGRAM_BINDING_NV:                   size = 1;  break;
    case GL_FRAGMENT_PROGRAM_NV:                           size = 1;  break;
    case GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV:          size = 1;  break;
    case GL_FRAGMENT_SHADER:                               size = 1;  break;
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:               size = 1;  break;
    case GL_FRAMEBUFFER_BINDING_EXT:                       size = 1;  break;
    case GL_FRAMEBUFFER_SRGB_CAPABLE_EXT:                  size = 1;  break;
    case GL_FRAMEBUFFER_SRGB_EXT:                          size = 1;  break;
    case GL_FRONT_FACE:                                    size = 1;  break;
    case GL_GENERATE_MIPMAP_HINT_SGIS:                     size = 1;  break;
    case GL_GEOMETRY_PROGRAM_NV:                           size = 1;  break;
    case GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV:          size = 1;  break;
    case GL_GEOMETRY_SHADER_ARB:                           size = 1;  break;
    case GL_GREEN_BIAS:                                    size = 1;  break;
    case GL_GREEN_BITS:                                    size = 1;  break;
    case GL_GREEN_SCALE:                                   size = 1;  break;
    case GL_HISTOGRAM:                                     size = 1;  break;
    case GL_HI_BIAS_NV:                                    size = 1;  break;
    case GL_HI_SCALE_NV:                                   size = 1;  break;
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:          size = 1;  break;
    case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:            size = 1;  break;
    case GL_INDEX_ARRAY:                                   size = 1;  break;
    case GL_INDEX_ARRAY_BUFFER_BINDING_ARB:                size = 1;  break;
    case GL_INDEX_ARRAY_COUNT_EXT:                         size = 1;  break;
    case GL_INDEX_ARRAY_STRIDE:                            size = 1;  break;
    case GL_INDEX_ARRAY_TYPE:                              size = 1;  break;
    case GL_INDEX_BITS:                                    size = 1;  break;
    case GL_INDEX_CLEAR_VALUE:                             size = 1;  break;
    case GL_INDEX_MODE:                                    size = 1;  break;
    case GL_INDEX_OFFSET:                                  size = 1;  break;
    case GL_INDEX_SHIFT:                                   size = 1;  break;
    case GL_INDEX_WRITEMASK:                               size = 1;  break;
    case GL_LIGHT0:                                        size = 1;  break;
    case GL_LIGHT1:                                        size = 1;  break;
    case GL_LIGHT2:                                        size = 1;  break;
    case GL_LIGHT3:                                        size = 1;  break;
    case GL_LIGHT4:                                        size = 1;  break;
    case GL_LIGHT5:                                        size = 1;  break;
    case GL_LIGHT6:                                        size = 1;  break;
    case GL_LIGHT7:                                        size = 1;  break;
//    case GL_LIGHT8:                                      size = 1;  break;
//    case GL_LIGHT9:                                      size = 1;  break;
    case GL_LIGHTING:                                      size = 1;  break;
    case GL_LIGHT_MODEL_AMBIENT:                           size = 4;  break;
    case GL_LIGHT_MODEL_COLOR_CONTROL:                     size = 1;  break;
    case GL_LIGHT_MODEL_LOCAL_VIEWER:                      size = 1;  break;
    case GL_LIGHT_MODEL_TWO_SIDE:                          size = 1;  break;
    case GL_LINE_SMOOTH:                                   size = 1;  break;
    case GL_LINE_SMOOTH_HINT:                              size = 1;  break;
    case GL_LINE_STIPPLE:                                  size = 1;  break;
    case GL_LINE_STIPPLE_PATTERN:                          size = 1;  break;
    case GL_LINE_STIPPLE_REPEAT:                           size = 1;  break;
    case GL_LINE_WIDTH:                                    size = 1;  break;
    case GL_LINE_WIDTH_GRANULARITY:                        size = 1;  break;
    case GL_LINE_WIDTH_RANGE:                              size = 2;  break;
    case GL_LIST_BASE:                                     size = 1;  break;
    case GL_LIST_INDEX:                                    size = 1;  break;
    case GL_LIST_MODE:                                     size = 1;  break;
    case GL_LOGIC_OP:                                      size = 1;  break;
    case GL_LOGIC_OP_MODE:                                 size = 1;  break;
    case GL_LO_BIAS_NV:                                    size = 1;  break;
    case GL_LO_SCALE_NV:                                   size = 1;  break;
    case GL_MAGNITUDE_BIAS_NV:                             size = 1;  break;
    case GL_MAGNITUDE_SCALE_NV:                            size = 1;  break;
    case GL_MAJOR_VERSION:                                 size = 1;  break;
    case GL_MAP1_COLOR_4:                                  size = 1;  break;
    case GL_MAP1_GRID_DOMAIN:                              size = 2;  break;
    case GL_MAP1_GRID_SEGMENTS:                            size = 1;  break;
    case GL_MAP1_INDEX:                                    size = 1;  break;
    case GL_MAP1_NORMAL:                                   size = 1;  break;
    case GL_MAP1_TEXTURE_COORD_1:                          size = 1;  break;
    case GL_MAP1_TEXTURE_COORD_2:                          size = 1;  break;
    case GL_MAP1_TEXTURE_COORD_3:                          size = 1;  break;
    case GL_MAP1_TEXTURE_COORD_4:                          size = 1;  break;
    case GL_MAP1_VERTEX_3:                                 size = 1;  break;
    case GL_MAP1_VERTEX_4:                                 size = 1;  break;
    case GL_MAP2_COLOR_4:                                  size = 1;  break;
    case GL_MAP2_GRID_DOMAIN:                              size = 4;  break;
    case GL_MAP2_GRID_SEGMENTS:                            size = 2;  break;
    case GL_MAP2_INDEX:                                    size = 1;  break;
    case GL_MAP2_NORMAL:                                   size = 1;  break;
    case GL_MAP2_TEXTURE_COORD_1:                          size = 1;  break;
    case GL_MAP2_TEXTURE_COORD_2:                          size = 1;  break;
    case GL_MAP2_TEXTURE_COORD_3:                          size = 1;  break;
    case GL_MAP2_TEXTURE_COORD_4:                          size = 1;  break;
    case GL_MAP2_VERTEX_3:                                 size = 1;  break;
    case GL_MAP2_VERTEX_4:                                 size = 1;  break;
    case GL_MAP_COLOR:                                     size = 1;  break;
    case GL_MAP_STENCIL:                                   size = 1;  break;
    case GL_MATRIX_MODE:                                   size = 1;  break;
    case GL_MAX_3D_TEXTURE_SIZE:                           size = 1;  break;
    case GL_MAX_ARRAY_TEXTURE_LAYERS_EXT:                  size = 1;  break;
    case GL_MAX_ATTRIB_STACK_DEPTH:                        size = 1;  break;
    case GL_MAX_BINDABLE_UNIFORM_SIZE_EXT:                 size = 1;  break;
    case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:                 size = 1;  break;
    case GL_MAX_CLIP_PLANES:                               size = 1;  break;
    case GL_MAX_COLOR_ATTACHMENTS_EXT:                     size = 1;  break;
    case GL_MAX_COLOR_MATRIX_STACK_DEPTH:                  size = 1;  break;
    case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS:      size = 1;  break;
    case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS:      size = 1;  break;
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:              size = 1;  break;
    case GL_MAX_COMBINED_UNIFORM_BLOCKS:                   size = 1;  break;
    case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS:        size = 1;  break;
    case GL_MAX_CONVOLUTION_HEIGHT:                        size = 1;  break;
    case GL_MAX_CONVOLUTION_WIDTH:                         size = 1;  break;
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:                     size = 1;  break;
    case GL_MAX_DRAW_BUFFERS:                              size = 1;  break;
    case GL_MAX_DUAL_SOURCE_DRAW_BUFFERS:                  size = 1;  break;
    case GL_MAX_EVAL_ORDER:                                size = 1;  break;
    case GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT:            size = 1;  break;
    case GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV:      size = 1;  break;
    case GL_MAX_FRAGMENT_UNIFORM_BLOCKS:                   size = 1;  break;
    case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS:               size = 1;  break;
    case GL_MAX_GENERAL_COMBINERS_NV:                      size = 1;  break;
    case GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT:            size = 1;  break;
    case GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT:              size = 1;  break;
    case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT:          size = 1;  break;
    case GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT:      size = 1;  break;
    case GL_MAX_GEOMETRY_UNIFORM_BLOCKS:                   size = 1;  break;
    case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT:           size = 1;  break;
    case GL_MAX_GEOMETRY_VARYING_COMPONENTS_EXT:           size = 1;  break;
    case GL_MAX_LIGHTS:                                    size = 1;  break;
    case GL_MAX_LIST_NESTING:                              size = 1;  break;
    case GL_MAX_MODELVIEW_STACK_DEPTH:                     size = 1;  break;
    case GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV:             size = 1;  break;
    case GL_MAX_NAME_STACK_DEPTH:                          size = 1;  break;
    case GL_MAX_PIXEL_MAP_TABLE:                           size = 1;  break;
    case GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV:      size = 1;  break;
    case GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV:          size = 1;  break;
    case GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS:         size = 1;  break;
    case GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET:             size = 1;  break;
    case GL_MAX_PROJECTION_STACK_DEPTH:                    size = 1;  break;
    case GL_MAX_RECTANGLE_TEXTURE_SIZE_NV:                 size = 1;  break;
    case GL_MAX_RENDERBUFFER_SIZE_EXT:                     size = 1;  break;
    case GL_MAX_SAMPLES_EXT:                               size = 1;  break;
    case GL_MAX_SAMPLE_MASK_WORDS_NV:                      size = 1;  break;
    case GL_MAX_SERVER_WAIT_TIMEOUT:                       size = 1;  break;
    case GL_MAX_SHININESS_NV:                              size = 1;  break;
    case GL_MAX_SPOT_EXPONENT_NV:                          size = 1;  break;
    case GL_MAX_SUBROUTINES:                               size = 1;  break;
    case GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS:              size = 1;  break;
    case GL_MAX_TEXTURE_BUFFER_SIZE_ARB:                   size = 1;  break;
    case GL_MAX_TEXTURE_COORDS:                            size = 1;  break;
    case GL_MAX_TEXTURE_IMAGE_UNITS:                       size = 1;  break;
    case GL_MAX_TEXTURE_LOD_BIAS_EXT:                      size = 1;  break;
    case GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT:                size = 1;  break;
    case GL_MAX_TEXTURE_SIZE:                              size = 1;  break;
    case GL_MAX_TEXTURE_STACK_DEPTH:                       size = 1;  break;
    case GL_MAX_TEXTURE_UNITS:                             size = 1;  break;
    case GL_MAX_TRACK_MATRICES_NV:                         size = 1;  break;
    case GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV:               size = 1;  break;
    case GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS: size = 1;  break;
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS:       size = 1;  break;
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS:    size = 1;  break;
    case GL_MAX_UNIFORM_BLOCK_SIZE:                        size = 1;  break;
    case GL_MAX_UNIFORM_BUFFER_BINDINGS:                   size = 1;  break;
    case GL_MAX_VARYING_FLOATS:                            size = 1;  break;
    case GL_MAX_VERTEX_ATTRIBS_ARB:                        size = 1;  break;
    case GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT:              size = 1;  break;
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:                size = 1;  break;
    case GL_MAX_VERTEX_UNIFORM_BLOCKS:                     size = 1;  break;
    case GL_MAX_VERTEX_UNIFORM_COMPONENTS:                 size = 1;  break;
    case GL_MAX_VERTEX_VARYING_COMPONENTS_EXT:             size = 1;  break;
    case GL_MAX_VIEWPORT_DIMS:                             size = 2;  break;
    case GL_MINMAX:                                        size = 1;  break;
    case GL_MINOR_VERSION:                                 size = 1;  break;
    case GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET:             size = 1;  break;
    case GL_MIN_SAMPLE_SHADING_VALUE_ARB:                  size = 1;  break;
    case GL_MODELVIEW_MATRIX:                              size = 16; break;
    case GL_MODELVIEW_STACK_DEPTH:                         size = 1;  break;
    case GL_MULTISAMPLE:                                   size = 1;  break;
    case GL_MULTISAMPLE_FILTER_HINT_NV:                    size = 1;  break;
    case GL_NAME_STACK_DEPTH:                              size = 1;  break;
    case GL_NORMALIZE:                                     size = 1;  break;
    case GL_NORMAL_ARRAY:                                  size = 1;  break;
    case GL_NORMAL_ARRAY_BUFFER_BINDING:                   size = 1;  break;
    case GL_NORMAL_ARRAY_COUNT_EXT:                        size = 1;  break;
    case GL_NORMAL_ARRAY_STRIDE:                           size = 1;  break;
    case GL_NORMAL_ARRAY_TYPE:                             size = 1;  break;
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS:                size = 1;  break;
    case GL_NUM_EXTENSIONS:                                size = 1;  break;
    case GL_NUM_GENERAL_COMBINERS_NV:                      size = 1;  break;
    case GL_NUM_SHADING_LANGUAGE_VERSIONS:                 size = 1;  break;
    case GL_OCCLUSION_TEST_HP:                             size = 1;  break;
    case GL_OCCLUSION_TEST_RESULT_HP:                      size = 1;  break;
    case GL_PACK_ALIGNMENT:                                size = 1;  break;
    case GL_PACK_IMAGE_HEIGHT:                             size = 1;  break;
    case GL_PACK_LSB_FIRST:                                size = 1;  break;
    case GL_PACK_ROW_LENGTH:                               size = 1;  break;
    case GL_PACK_SKIP_IMAGES:                              size = 1;  break;
    case GL_PACK_SKIP_PIXELS:                              size = 1;  break;
    case GL_PACK_SKIP_ROWS:                                size = 1;  break;
    case GL_PACK_SWAP_BYTES:                               size = 1;  break;
    case GL_PERSPECTIVE_CORRECTION_HINT:                   size = 1;  break;
    case GL_PER_STAGE_CONSTANTS_NV:                        size = 1;  break;
    case GL_PIXEL_COUNTER_BITS_NV:                         size = 1;  break;
    case GL_PIXEL_MAP_A_TO_A_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_B_TO_B_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_G_TO_G_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_I_TO_A_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_I_TO_B_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_I_TO_G_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_I_TO_I_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_I_TO_R_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_R_TO_R_SIZE:                         size = 1;  break;
    case GL_PIXEL_MAP_S_TO_S_SIZE:                         size = 1;  break;
    case GL_PIXEL_PACK_BUFFER_BINDING_ARB:                 size = 1;  break;
    case GL_PIXEL_UNPACK_BUFFER_BINDING_ARB:               size = 1;  break;
    case GL_POINT_DISTANCE_ATTENUATION:                    size = 3;  break;
    case GL_POINT_FADE_THRESHOLD_SIZE:                     size = 1;  break;
    case GL_POINT_SIZE:                                    size = 1;  break;
//    case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:         size = 1;  break;
//    case GL_POINT_SIZE_ARRAY_OES:                        size = 1;  break;
//    case GL_POINT_SIZE_ARRAY_STRIDE_OES:                 size = 1;  break;
//    case GL_POINT_SIZE_ARRAY_TYPE_OES:                   size = 1;  break;
    case GL_POINT_SIZE_GRANULARITY:                        size = 1;  break;
    case GL_POINT_SIZE_MAX:                                size = 1;  break;
    case GL_POINT_SIZE_MIN:                                size = 1;  break;
    case GL_POINT_SIZE_RANGE:                              size = 2;  break;
    case GL_POINT_SMOOTH:                                  size = 1;  break;
    case GL_POINT_SMOOTH_HINT:                             size = 1;  break;
//    case GL_POINT_SPRITE_OES:                            size = 1;  break;
    case GL_POINT_SPRITE_COORD_ORIGIN:                     size = 1;  break;
    case GL_POINT_SPRITE_NV :                              size = 1;  break;
    case GL_POINT_SPRITE_R_MODE_NV:                        size = 1;  break;
    case GL_POLYGON_MODE:                                  size = 2;  break;
    case GL_POLYGON_OFFSET_FACTOR:                         size = 1;  break;
    case GL_POLYGON_OFFSET_FILL:                           size = 1;  break;
    case GL_POLYGON_OFFSET_UNITS:                          size = 1;  break;
    case GL_POLYGON_SMOOTH:                                size = 1;  break;
    case GL_POLYGON_SMOOTH_HINT:                           size = 1;  break;
    case GL_POLYGON_STIPPLE:                               size = 1;  break;
    case GL_POST_COLOR_MATRIX_ALPHA_BIAS:                  size = 1;  break;
    case GL_POST_COLOR_MATRIX_ALPHA_SCALE:                 size = 1;  break;
    case GL_POST_COLOR_MATRIX_BLUE_BIAS:                   size = 1;  break;
    case GL_POST_COLOR_MATRIX_BLUE_SCALE:                  size = 1;  break;
    case GL_POST_COLOR_MATRIX_COLOR_TABLE:                 size = 1;  break;
    case GL_POST_COLOR_MATRIX_GREEN_BIAS:                  size = 1;  break;
    case GL_POST_COLOR_MATRIX_GREEN_SCALE:                 size = 1;  break;
    case GL_POST_COLOR_MATRIX_RED_BIAS:                    size = 1;  break;
    case GL_POST_COLOR_MATRIX_RED_SCALE:                   size = 1;  break;
    case GL_POST_CONVOLUTION_ALPHA_BIAS:                   size = 1;  break;
    case GL_POST_CONVOLUTION_ALPHA_SCALE:                  size = 1;  break;
    case GL_POST_CONVOLUTION_BLUE_BIAS:                    size = 1;  break;
    case GL_POST_CONVOLUTION_BLUE_SCALE:                   size = 1;  break;
    case GL_POST_CONVOLUTION_COLOR_TABLE:                  size = 1;  break;
    case GL_POST_CONVOLUTION_GREEN_BIAS:                   size = 1;  break;
    case GL_POST_CONVOLUTION_GREEN_SCALE:                  size = 1;  break;
    case GL_POST_CONVOLUTION_RED_BIAS:                     size = 1;  break;
    case GL_POST_CONVOLUTION_RED_SCALE:                    size = 1;  break;
    case GL_PROGRAM_ERROR_POSITION_NV:                     size = 1;  break;
    case GL_PROGRAM_POINT_SIZE_EXT:                        size = 1;  break;
    case GL_PROJECTION_MATRIX:                             size = 16; break;
    case GL_PROJECTION_STACK_DEPTH:                        size = 1;  break;
    case GL_PROVOKING_VERTEX:                              size = 1;  break;
    case GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION:      size = 1;  break;
    case GL_RASTERIZER_DISCARD:                            size = 1;  break;
    case GL_READ_BUFFER:                                   size = 1;  break;
    case GL_READ_FRAMEBUFFER_BINDING_EXT:                  size = 1;  break;
    case GL_RED_BIAS:                                      size = 1;  break;
    case GL_RED_BITS:                                      size = 1;  break;
    case GL_RED_SCALE:                                     size = 1;  break;
    case GL_RENDERBUFFER_BINDING_EXT:                      size = 1;  break;
    case GL_RENDER_MODE:                                   size = 1;  break;
    case GL_RESCALE_NORMAL:                                size = 1;  break;
    case GL_RGBA_FLOAT_MODE_ARB:                           size = 1;  break;
    case GL_RGBA_INTEGER_MODE_EXT:                         size = 1;  break;
    case GL_RGBA_MODE:                                     size = 1;  break;
    case GL_RGBA_SIGNED_COMPONENTS_EXT:                    size = 4;  break;
    case GL_SAMPLES:                                       size = 1;  break;
    case GL_SAMPLE_ALPHA_TO_COVERAGE:                      size = 1;  break;
    case GL_SAMPLE_ALPHA_TO_ONE:                           size = 1;  break;
    case GL_SAMPLE_BUFFERS:                                size = 1;  break;
    case GL_SAMPLE_COVERAGE:                               size = 1;  break;
    case GL_SAMPLE_COVERAGE_INVERT:                        size = 1;  break;
    case GL_SAMPLE_COVERAGE_VALUE:                         size = 1;  break;
    case GL_SAMPLE_MASK_NV:                                size = 1;  break;
    case GL_SAMPLE_SHADING_ARB:                            size = 1;  break;
    case GL_SAMPLER_BINDING:                               size = 1;  break;
    case GL_SCISSOR_BOX:                                   size = 4;  break;
    case GL_SCISSOR_TEST:                                  size = 1;  break;
    case GL_SECONDARY_COLOR_ARRAY:                         size = 1;  break;
    case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB:      size = 1;  break;
    case GL_SECONDARY_COLOR_ARRAY_SIZE:                    size = 1;  break;
    case GL_SECONDARY_COLOR_ARRAY_STRIDE:                  size = 1;  break;
    case GL_SECONDARY_COLOR_ARRAY_TYPE:                    size = 1;  break;
    case GL_SELECTION_BUFFER_SIZE:                         size = 1;  break;
    case GL_SEPARABLE_2D:                                  size = 1;  break;
    case GL_SHADE_MODEL:                                   size = 1;  break;
//  case GL_SMOOTH_LINE_WIDTH_RANGE:                       size = 2;  break;
//  case GL_SMOOTH_POINT_SIZE_RANGE:                       size = 2;  break;
    case GL_STENCIL_BACK_FAIL:                             size = 1;  break;
    case GL_STENCIL_BACK_FUNC:                             size = 1;  break;
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:                  size = 1;  break;
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:                  size = 1;  break;
    case GL_STENCIL_BACK_REF:                              size = 1;  break;
    case GL_STENCIL_BACK_VALUE_MASK:                       size = 1;  break;
    case GL_STENCIL_BACK_WRITEMASK:                        size = 1;  break;
    case GL_STENCIL_BITS:                                  size = 1;  break;
    case GL_STENCIL_CLEAR_VALUE:                           size = 1;  break;
    case GL_STENCIL_FAIL:                                  size = 1;  break;
    case GL_STENCIL_FUNC:                                  size = 1;  break;
    case GL_STENCIL_PASS_DEPTH_FAIL:                       size = 1;  break;
    case GL_STENCIL_PASS_DEPTH_PASS:                       size = 1;  break;
    case GL_STENCIL_REF:                                   size = 1;  break;
    case GL_STENCIL_TEST:                                  size = 1;  break;
    case GL_STENCIL_TEST_TWO_SIDE_EXT:                     size = 1;  break;
    case GL_STENCIL_VALUE_MASK:                            size = 1;  break;
    case GL_STENCIL_WRITEMASK:                             size = 1;  break;
    case GL_STEREO:                                        size = 1;  break;
    case GL_SUBPIXEL_BITS:                                 size = 1;  break;
    case GL_TEXTURE_1D:                                    size = 1;  break;
    case GL_TEXTURE_2D:                                    size = 1;  break;
    case GL_TEXTURE_3D:                                    size = 1;  break;
    case GL_TEXTURE_BINDING_1D:                            size = 1;  break;
    case GL_TEXTURE_BINDING_1D_ARRAY_EXT:                  size = 1;  break;
    case GL_TEXTURE_BINDING_2D:                            size = 1;  break;
    case GL_TEXTURE_BINDING_2D_ARRAY_EXT:                  size = 1;  break;
    case GL_TEXTURE_BINDING_3D:                            size = 1;  break;
    case GL_TEXTURE_BINDING_BUFFER_ARB:                    size = 1;  break;
    case GL_TEXTURE_BINDING_CUBE_MAP:                      size = 1;  break;
    case GL_TEXTURE_BINDING_CUBE_MAP_ARRAY:                size = 1;  break;
    case GL_TEXTURE_BINDING_RECTANGLE_NV:                  size = 1;  break;
    case GL_TEXTURE_BINDING_RENDERBUFFER_NV:               size = 1;  break;
    case GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB:         size = 1;  break;
    case GL_TEXTURE_BUFFER_EXT:                            size = 1;  break;
    case GL_TEXTURE_BUFFER_FORMAT_ARB:                     size = 1;  break;
    case GL_TEXTURE_COMPRESSION_HINT:                      size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY:                           size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:            size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY_COUNT_EXT:                 size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY_SIZE:                      size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY_STRIDE:                    size = 1;  break;
    case GL_TEXTURE_COORD_ARRAY_TYPE:                      size = 1;  break;
    case GL_TEXTURE_CUBE_MAP:                              size = 1;  break;
    case GL_TEXTURE_GEN_Q:                                 size = 1;  break;
    case GL_TEXTURE_GEN_R:                                 size = 1;  break;
    case GL_TEXTURE_GEN_S:                                 size = 1;  break;
    case GL_TEXTURE_GEN_T:                                 size = 1;  break;
    case GL_TEXTURE_MATRIX:                                size = 16; break;
    case GL_TEXTURE_RECTANGLE_NV:                          size = 1;  break;
    case GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV:    size = 1;  break;
    case GL_TEXTURE_STACK_DEPTH:                           size = 1;  break;
    case GL_TIMESTAMP:                                     size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_ATTRIBS_NV:                 size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_BINDING_NV:                 size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE_NV:           size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:             size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_MODE:                size = 1;  break;
    case GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED_NV:           size = 1;  break;
    case GL_TRANSPOSE_COLOR_MATRIX:                        size = 16; break;
    case GL_TRANSPOSE_CURRENT_MATRIX_ARB:                  size = 1;  break;
    case GL_TRANSPOSE_MODELVIEW_MATRIX:                    size = 16; break;
    case GL_TRANSPOSE_PROJECTION_MATRIX:                   size = 16; break;
    case GL_TRANSPOSE_TEXTURE_MATRIX:                      size = 16; break;
    case GL_UNIFORM_BUFFER_BINDING:                        size = 1;  break;
    case GL_UNIFORM_BUFFER_BINDING_EXT:                    size = 1;  break;
    case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT:               size = 1;  break;
    case GL_UNPACK_ALIGNMENT:                              size = 1;  break;
    case GL_UNPACK_IMAGE_HEIGHT:                           size = 1;  break;
    case GL_UNPACK_LSB_FIRST:                              size = 1;  break;
    case GL_UNPACK_ROW_LENGTH:                             size = 1;  break;
    case GL_UNPACK_SKIP_IMAGES:                            size = 1;  break;
    case GL_UNPACK_SKIP_PIXELS:                            size = 1;  break;
    case GL_UNPACK_SKIP_ROWS:                              size = 1;  break;
    case GL_UNPACK_SWAP_BYTES:                             size = 1;  break;
    case GL_VERTEX_ARRAY:                                  size = 1;  break;
    case GL_VERTEX_ARRAY_BINDING:                          size = 1;  break;
    case GL_VERTEX_ARRAY_BUFFER_BINDING:                   size = 1;  break;
    case GL_VERTEX_ARRAY_COUNT_EXT:                        size = 1;  break;
    case GL_VERTEX_ARRAY_SIZE:                             size = 1;  break;
    case GL_VERTEX_ARRAY_STRIDE:                           size = 1;  break;
    case GL_VERTEX_ARRAY_TYPE:                             size = 1;  break;
    case GL_VERTEX_PROGRAM_ARB:                            size = 1;  break;
    case GL_VERTEX_PROGRAM_BINDING_NV:                     size = 1;  break;
    case GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV:            size = 1;  break;
    case GL_VERTEX_PROGRAM_TWO_SIDE_ARB:                   size = 1;  break;
    case GL_VERTEX_SHADER:                                 size = 1;  break;
    case GL_VIBRANCE_BIAS_NV:                              size = 1;  break;
    case GL_VIBRANCE_SCALE_NV:                             size = 1;  break;
    case GL_VIEWPORT:                                      size = 4;  break;
    case GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB:               size = 1;  break;
    case GL_ZOOM_X:                                        size = 1;  break;
    case GL_ZOOM_Y:                                        size = 1;  break;

    default: break;
  }

  return size;
}

size_t
callLists(GLsizei n, GLenum type)
{
  size_t size = 0;

  switch (type)
  {
    case GL_BYTE:           size =     sizeof(GLbyte);   break;
    case GL_UNSIGNED_BYTE:  size =     sizeof(GLubyte);  break;
    case GL_SHORT:          size =     sizeof(GLshort);  break;
    case GL_UNSIGNED_SHORT: size =     sizeof(GLushort); break;
    case GL_INT:            size =     sizeof(GLint);    break;
    case GL_UNSIGNED_INT:   size =     sizeof(GLuint);   break;
    case GL_FLOAT:          size =     sizeof(GLfloat);  break;
    case GL_2_BYTES:        size = 2 * sizeof(GLubyte);  break;
    case GL_3_BYTES:        size = 3 * sizeof(GLubyte);  break;
    case GL_4_BYTES:        size = 4 * sizeof(GLubyte);  break;

    default: break;
  }

  size *= n > 0 ? (size_t)(n) : 0;

  return size;
}

size_t
fogv(GLenum pname)
{
  switch (pname)
  {
    case GL_FOG_MODE:             return 1;
    case GL_FOG_DENSITY:          return 1;
    case GL_FOG_START:            return 1;
    case GL_FOG_END:              return 1;
    case GL_FOG_INDEX:            return 1;
    case GL_FOG_COLOR:            return 4;
    case GL_FOG_COORD_SRC:        return 1;

    // GL_NV_fog_distance

    case GL_FOG_DISTANCE_MODE_NV: return 1;

    default:                      return 0;
  }
}

size_t
lightv(GLenum pname)
{
  switch (pname)
  {
    case GL_AMBIENT:               return 4;
    case GL_DIFFUSE:               return 4;
    case GL_SPECULAR:              return 4;
    case GL_POSITION:              return 4;
    case GL_SPOT_CUTOFF:           return 1;
    case GL_SPOT_DIRECTION:        return 3;
    case GL_SPOT_EXPONENT:         return 1;
    case GL_CONSTANT_ATTENUATION:  return 1;
    case GL_LINEAR_ATTENUATION:    return 1;
    case GL_QUADRATIC_ATTENUATION: return 1;
    default:                       return 0;
  }
}

size_t
lightModelv(GLenum pname)
{
  switch (pname)
  {
    case GL_LIGHT_MODEL_AMBIENT:       return 4;
    case GL_LIGHT_MODEL_COLOR_CONTROL: return 1;
    case GL_LIGHT_MODEL_LOCAL_VIEWER:  return 1;
    case GL_LIGHT_MODEL_TWO_SIDE:      return 1;
    default:                           return 0;
  }
}

size_t
materialv(GLenum pname)
{
  switch (pname)
  {
    case GL_AMBIENT:             return 4;
    case GL_DIFFUSE:             return 4;
    case GL_SPECULAR:            return 4;
    case GL_EMISSION:            return 4;
    case GL_SHININESS:           return 1;
    case GL_AMBIENT_AND_DIFFUSE: return 4;
    case GL_COLOR_INDEXES:       return 3;
    default:                     return 0;
  }
}

size_t
pixelImage(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint pack, GLenum target)
{
  /* TODO: Review later: Does texture "level" affect size? */
  /* TODO: Review later: Properly account for effects of glPixelStore. */

  size_t numComponent = componentsPerPixel(format);
  size_t sizeElement  = 8; /* bits */

  size_t dataWidth  = 0;
  size_t dataHeight = 0;
  size_t dataDepth  = 0;

//  if (!traceGL_Native.glGetIntegerv)
//    return 0;

  if (width < 0 || height < 0 || depth < 0)
    return 0;

  if (pack != 0 && pack != 1)
    return 0;

  /* When target is a GL_PROXY_TEXUTRE_xx, size is 0. */

  if ((target == GL_PROXY_TEXTURE_1D) ||
      (target == GL_PROXY_TEXTURE_2D) ||
      (target == GL_PROXY_TEXTURE_3D))
    return 0;

  /* TODO: If an unpack buffer is bound for glDrawPixels... */
  if (!pack)
  {
#if 0
    GLint bufferBinding = 0;
    traceGL_Native.glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &bufferBinding);
    if (bufferBinding > 0)
      return 1;
#endif
  }
  else
  {
#if 0
    /* TODO: Data is treated as byte offset when a non-zero named buffer is bound. */
    GLint bufferBinding = 0;
    traceGL_Native.glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &bufferBinding);
    if (bufferBinding > 0)
      return 1;
#endif
  }

  /* Compute size of each element. */

  sizeElement *= bytesPerComponent(type);

  switch (type)
  {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE:
    case GL_BITMAP:
    case GL_UNSIGNED_SHORT:
    case GL_SHORT:
    case GL_UNSIGNED_INT:
    case GL_INT:
    case GL_FLOAT:           sizeElement *= numComponent; break;
    default:                                              break;
  }

  /* Special case: GL_BITMAP. */

  if (type == GL_BITMAP)
  {
     /* TODO: Confirm calculations. */
    if ((format == GL_COLOR_INDEX) || (format == GL_STENCIL_INDEX))
      sizeElement = sizeElement/8;
    else
      return 0;
  }

  /* Take into account client state set by glPixelStore. */

  if (depth)
  {
#if 0
    GLint skipImages = 0;

    /* GL_PACK_SKIP_IMAGES */
    if (pack)
      traceGL_Native.glGetIntegerv(GL_PACK_SKIP_IMAGES, &skipImages);
    else
      traceGL_Native.glGetIntegerv(GL_UNPACK_SKIP_IMAGES, &skipImages);
    dataDepth += skipImages > 0 ? skipImages : 0;
#endif
  }
  else
  {
    dataDepth = 1;
  }

  if (height)
  {
    GLint imageHeight = 0;
    GLint skipRows    = 0;
    GLint rowLength   = 0;
    GLint alignment   = 1; /* Allowed values: 1,2,4,8 */

#if 0
    /* GL_PACK_IMAGE_HEIGHT */
    if (pack)
      traceGL_Native.glGetIntegerv(GL_PACK_IMAGE_HEIGHT, &imageHeight);
    else
      traceGL_Native.glGetIntegerv(GL_UNPACK_IMAGE_HEIGHT, &imageHeight);
#endif
    dataHeight = imageHeight > 0 ? imageHeight : height;

#if 0
    /* GL_PACK_SKIP_ROWS */
    if (pack)
      traceGL_Native.glGetIntegerv(GL_PACK_SKIP_ROWS, &skipRows);
    else
      traceGL_Native.glGetIntegerv(GL_UNPACK_SKIP_ROWS, &skipRows);
#endif
    dataHeight += skipRows > 0 ? skipRows : 0;

#if 0
    /* GL_PACK_ROW_LENGTH */
    if (pack)
      traceGL_Native.glGetIntegerv(GL_PACK_ROW_LENGTH, &rowLength);
    else
      traceGL_Native.glGetIntegerv(GL_UNPACK_ROW_LENGTH, &rowLength);
#endif
    dataWidth = rowLength > 0 ? rowLength : width;

    /* Align byte boundary */
    dataWidth = (dataWidth * sizeElement + 7)/8;

#if 0
    /* GL_PACK_ALIGNMENT */
    if (pack)
      traceGL_Native.glGetIntegerv(GL_PACK_ALIGNMENT, &alignment);
    else
      traceGL_Native.glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
#endif
    dataWidth = alignment > 0 ? alignment * (dataWidth + alignment - 1)/alignment : dataWidth;
  }
  else
  {
    dataHeight = 1;

    /* Align byte boundary */
    dataWidth = (width * sizeElement + 7)/8;
  }

  return dataWidth * dataHeight * dataDepth;
}

/* TODO: Extension enums. */

size_t
texParameterv(GLenum pname)
{
  switch (pname)
  {
    /* Dec 2012 - http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml */

    case GL_DEPTH_STENCIL_TEXTURE_MODE: return 1;
    case GL_TEXTURE_BASE_LEVEL:         return 1;
    case GL_TEXTURE_BORDER_COLOR:       return 4;
    case GL_TEXTURE_COMPARE_FUNC:       return 1;
    case GL_TEXTURE_COMPARE_MODE:       return 1;
    case GL_TEXTURE_LOD_BIAS:           return 1;
    case GL_TEXTURE_MIN_FILTER:         return 1;
    case GL_TEXTURE_MAG_FILTER:         return 1;
    case GL_TEXTURE_MIN_LOD:            return 1;
    case GL_TEXTURE_MAX_LOD:            return 1;
    case GL_TEXTURE_MAX_LEVEL:          return 1;
    case GL_TEXTURE_SWIZZLE_R:          return 1;
    case GL_TEXTURE_SWIZZLE_G:          return 1;
    case GL_TEXTURE_SWIZZLE_B:          return 1;
    case GL_TEXTURE_SWIZZLE_A:          return 1;
    case GL_TEXTURE_SWIZZLE_RGBA:       return 4;
    case GL_TEXTURE_WRAP_S:             return 1;
    case GL_TEXTURE_WRAP_T:             return 1;
    case GL_TEXTURE_WRAP_R:             return 1;

    /* others */

    case GL_TEXTURE_PRIORITY:               return 1;
    case GL_DEPTH_TEXTURE_MODE:             return 1;
    case GL_GENERATE_MIPMAP:                return 1;

    // GL_EXT_texture_filter_anisotropic

    case GL_TEXTURE_MAX_ANISOTROPY_EXT:     return 1;

    // GL_SGIX_shadow

    case GL_TEXTURE_COMPARE_SGIX:           return 1;
    case GL_TEXTURE_COMPARE_OPERATOR_SGIX:  return 1;

    // GL_NV_texture_expand_normal

    case GL_TEXTURE_UNSIGNED_REMAP_MODE_NV: return 1;

    // GL_NV_texture_shader

    case GL_TEXTURE_BORDER_VALUES_NV:       return 4;

    default:                                return 0;
  }
}

size_t
texEnvv(GLenum target, GLenum pname)
{
  switch (target)
  {
    case GL_TEXTURE_ENV:
      switch (pname)
      {
        case GL_TEXTURE_ENV_MODE:  return 1;
        case GL_TEXTURE_ENV_COLOR: return 4;
        case GL_COMBINE_RGB:       return 1;
        case GL_COMBINE_ALPHA:     return 1;
        case GL_RGB_SCALE:         return 1;
        case GL_ALPHA_SCALE:       return 1;
        case GL_SRC0_RGB:
        case GL_SRC1_RGB:
        case GL_SRC2_RGB:          return 1;
        case GL_SRC0_ALPHA:
        case GL_SRC1_ALPHA:
        case GL_SRC2_ALPHA:        return 1;
        case GL_OPERAND0_RGB:
        case GL_OPERAND1_RGB:
        case GL_OPERAND2_RGB:      return 1;
        case GL_OPERAND0_ALPHA:
        case GL_OPERAND1_ALPHA:
        case GL_OPERAND2_ALPHA:    return 1;
        default:                   return 0;
      }

    case GL_TEXTURE_FILTER_CONTROL:
      switch (pname)
      {
        case GL_TEXTURE_LOD_BIAS:  return 1;
        default:                   return 0;
      }
  }
  return 0;
}

size_t
texGenv(GLenum pname)
{
  switch (pname)
  {
    case GL_TEXTURE_GEN_MODE: return 1;
    case GL_OBJECT_PLANE:     return 4;
    case GL_EYE_PLANE:        return 4;
    default:                  return 0;
  }
}

/* TODO: Extension enums. */

size_t
samplerParameterv(GLenum pname)
{
  switch (pname)
  {
    /* Dec 2012 - http://www.opengl.org/sdk/docs/man4/xhtml/glSamplerParameter.xml */

    case GL_TEXTURE_MIN_FILTER:         return 1;
    case GL_TEXTURE_MAG_FILTER:         return 1;
    case GL_TEXTURE_MIN_LOD:            return 1;
    case GL_TEXTURE_MAX_LOD:            return 1;
    case GL_TEXTURE_WRAP_S:             return 1;
    case GL_TEXTURE_WRAP_T:             return 1;
    case GL_TEXTURE_WRAP_R:             return 1;
    case GL_TEXTURE_BORDER_COLOR:       return 4;
    case GL_TEXTURE_COMPARE_MODE:       return 1;
    case GL_TEXTURE_COMPARE_FUNC:       return 1;

    /* Extensions */

    case GL_TEXTURE_LOD_BIAS:           return 1;
    case GL_TEXTURE_MAX_ANISOTROPY_EXT: return 1;
    case GL_TEXTURE_SRGB_DECODE_EXT:    return 1;

    default:                            return 0;
  }
}

size_t
drawElements(GLenum mode, GLsizei count, GLenum type)
{
  /* TODO: Something about client state VBO affects output? */

  switch (mode)
  {
    case GL_POINTS:
    case GL_LINE_STRIP:
    case GL_LINE_LOOP:
    case GL_LINES:
    case GL_TRIANGLE_STRIP:
    case GL_TRIANGLE_FAN:
    case GL_TRIANGLES:
    case GL_QUAD_STRIP:
    case GL_QUADS:
    case GL_POLYGON:         break;

    default: return 0;
  }

  size_t size = count > 0 ? count : 0;

  switch (type)
  {
    case GL_UNSIGNED_BYTE:  size *= sizeof(GLubyte);  break;
    case GL_UNSIGNED_SHORT: size *= sizeof(GLushort); break;
    case GL_UNSIGNED_INT:   size *= sizeof(GLuint);   break;
    default:                                          break;
  }

  return size;
}

size_t
namedString(const GLint namelen, const GLchar *name)
{
  if (namelen > 0)
    return (size_t) namelen;

  return name ? strlen(name) : 0;
}

size_t
namedStringParams(const GLenum pname)
{
  switch (pname)
  {
    case GL_NAMED_STRING_LENGTH_ARB: return 1;
    case GL_NAMED_STRING_TYPE_ARB:   return 1;
    default:                         return 0;
  }
}

}

/* Convert glShaderSource parameters into NUL-terminated string. */

char *
shaderSourceStrings(const GLsizei count, const GLchar **string,  const GLint *length)
{
  size_t total;  /* Total size of copy (bytes)      */
  char *tmp;     /* Copy of string array            */
  GLsizei i;     /* Input iterator                  */
  GLchar *j;     /* Output iterator                 */
  size_t  k;     /* Scratch space for string length */

  if (count<=0)
    return NULL;

  /* Determine single-allocation memory size */

  total = 0;
  for (i=0; i<count; ++i)
    total += length ? length[i] : (string[i] ? strlen(string[i]) : 0);
  total += count;                        /* One NUL-terminator per string */
  total *= sizeof(GLchar);
  total += 1;                            /*  NULL terminator */

  /* Do the allocation */

  tmp = (char *) malloc(total);

  /* Copy the strings */

  j = tmp;
  for (i=0; i<count; ++i)
  {
    k = length ? length[i] : (string[i] ? strlen(string[i]) : 0);
    memcpy(j,string[i],k);
    j += k;
  }
  *(j++) = '\0';

  RegalAssert(tmp+total == j);

  return tmp;
}

}

REGAL_NAMESPACE_END
