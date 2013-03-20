/*

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

*/

#include <ppapi/c/pp_var.h>
#include <ppapi/c/pp_errors.h>
#include <ppapi/c/pp_module.h>

#include <ppapi/c/ppb.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_messaging.h>
#include <ppapi/c/ppb_var.h>
#include <ppapi/c/ppb_view.h>

#include <ppapi/c/ppp.h>
#include <ppapi/c/ppp_instance.h>
#include <ppapi/c/ppp_messaging.h>
#include <ppapi/c/ppp_input_event.h>
#include <ppapi/c/ppb_graphics_3d.h>
#include <ppapi/c/ppb_opengles2.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_input_event.h>

#include "render.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>

// Can't mix all of Regal.h with OpenGL ES 2.0 header(s)

#define __REGAL_H__
#include <GL/Regal.h>

extern "C"
{
  extern void glLogMessageCallbackREGAL(void (*callback)(GLenum, GLsizei, const char *, GLvoid *));
  extern void glEnable(GLenum cap);
};

#define GL_LOG_ERROR_REGAL    0x9319     /* 37657 */
#define GL_LOG_WARNING_REGAL  0x931a     /* 37658 */
#define GL_LOG_INFO_REGAL     0x931b     /* 37659 */
#define GL_LOG_APP_REGAL      0x931c     /* 37660 */
#define GL_LOG_DRIVER_REGAL   0x931d     /* 37661 */
#define GL_LOG_INTERNAL_REGAL 0x931e     /* 37662 */
#define GL_LOG_DEBUG_REGAL    0x931f     /* 37663 */
#define GL_LOG_STATUS_REGAL   0x9320     /* 37664 */
#define GL_LOG_HTTP_REGAL     0x9321     /* 37665 */

#define GL_ERROR_REGAL     0x9322     /* 37666 */
#define GL_DEBUG_REGAL     0x9323     /* 37667 */
#define GL_LOG_REGAL       0x9324     /* 37668 */
#define GL_EMULATION_REGAL 0x9325     /* 37669 */
#define GL_DRIVER_REGAL    0x9326     /* 37670 */

static PPB_Messaging          *ppb_messaging_interface = NULL;
static PPB_Var                *ppb_var_interface = NULL;
static PPB_View               *ppb_view_interface = NULL;
static PPB_Graphics3D         *ppb_graphics3d_interface = NULL;
static PPB_Instance           *ppb_instance_interface = NULL;
static PPB_OpenGLES2          *ppb_opengl_interface = NULL;
static PPB_KeyboardInputEvent *ppb_keyboard_interface = NULL;
static PPB_InputEvent         *ppb_input_interface = NULL;
static PP_Resource             opengl_context = 0;

// Utility functions

PP_Instance printfInstance = 0;

static struct PP_Var CStrToVar(const char* str)
{
  if (ppb_var_interface)
    return ppb_var_interface->VarFromUtf8(str, strlen(str));
  else
    return PP_MakeUndefined();
}

static void messagePrint(const char* str)
{
  if (ppb_messaging_interface && printfInstance)
    ppb_messaging_interface->PostMessage(printfInstance, ::CStrToVar(str));  
}

static void myLogCallback(GLenum stream, GLsizei length, const char *message, GLvoid *context)
{
  messagePrint(message);
}

static void myDraw(void *user_data, int32_t result)
{
  dreamTorusDisplay(true);

  PP_CompletionCallback ccb;
  ccb.func = myDraw;
  ccb.user_data = NULL;
  ccb.flags = 0;
  ppb_graphics3d_interface->SwapBuffers(opengl_context, ccb);
}

// Instance interface

static PP_Bool Instance_DidCreate
(
  PP_Instance instance,
  uint32_t argc,
  const char* argn[],
  const char* argv[]
)
{
  printfInstance = instance;
  messagePrint("Regal Dream Torus (GLIBC)");
  int32_t attribs[] = { PP_GRAPHICS3DATTRIB_WIDTH, 512, PP_GRAPHICS3DATTRIB_HEIGHT, 512, PP_GRAPHICS3DATTRIB_NONE};
  opengl_context = ppb_graphics3d_interface->Create(instance, opengl_context, attribs);
  ppb_instance_interface->BindGraphics(instance, opengl_context);

  RegalMakeCurrent(opengl_context, ppb_opengl_interface);
  glLogMessageCallbackREGAL(myLogCallback);

//  glEnable(GL_LOG_APP_REGAL);
  glEnable(GL_ERROR_REGAL);

  myDraw(NULL, 0);
  return PP_TRUE;
}

static void Instance_DidDestroy(PP_Instance instance)
{
}

static void Instance_DidChangeView(PP_Instance instance, PP_Resource view_resource)
{
}

static void Instance_DidChangeFocus(PP_Instance instance, PP_Bool has_focus)
{
}

static PP_Bool Instance_HandleDocumentLoad(PP_Instance instance, PP_Resource url_loader)
{
  return PP_FALSE;
}

// Module interface

PP_EXPORT int32_t PPP_InitializeModule(PP_Module a_module_id, PPB_GetInterface get_browser)
{
  ppb_messaging_interface  = (PPB_Messaging *)          get_browser(PPB_MESSAGING_INTERFACE);
  ppb_var_interface        = (PPB_Var *)                get_browser(PPB_VAR_INTERFACE);
  ppb_view_interface       = (PPB_View *)               get_browser(PPB_VIEW_INTERFACE);
  ppb_graphics3d_interface = (PPB_Graphics3D *)         get_browser(PPB_GRAPHICS_3D_INTERFACE);
  ppb_instance_interface   = (PPB_Instance *)           get_browser(PPB_INSTANCE_INTERFACE);
  ppb_opengl_interface     = (PPB_OpenGLES2 *)          get_browser(PPB_OPENGLES2_INTERFACE);
  ppb_keyboard_interface   = (PPB_KeyboardInputEvent *) get_browser(PPB_KEYBOARD_INPUT_EVENT_INTERFACE);
  ppb_input_interface      = (PPB_InputEvent *)         get_browser(PPB_INPUT_EVENT_INTERFACE);
  return PP_OK;
}

static PPP_Instance instance_interface = 
{
  &Instance_DidCreate,
  &Instance_DidDestroy,
  &Instance_DidChangeView,
  &Instance_DidChangeFocus,
  &Instance_HandleDocumentLoad,
};

PP_EXPORT const void *PPP_GetInterface(const char *interface_name)
{
  if (!strcmp(interface_name, PPP_INSTANCE_INTERFACE))
    return &instance_interface;
  return NULL;
}

PP_EXPORT void PPP_ShutdownModule()
{
}
