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

#ifndef __REGAL_LOG_H__
#define __REGAL_LOG_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <string>
#include <list>
#include <set>

#include <boost/print/json.hpp>           // Note - shouldn't need this in RegalLog.h
#include <boost/print/print_string.hpp>

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Json { struct Output; }

// Compile-time logging control

#ifndef REGAL_LOG_ERROR
# define REGAL_LOG_ERROR 1
#endif

#ifndef REGAL_LOG_WARNING
# define REGAL_LOG_WARNING 1
#endif

#ifndef REGAL_LOG_INFO
# define REGAL_LOG_INFO 1
#endif

#ifndef REGAL_LOG_APP
# ifdef NDEBUG
#  define REGAL_LOG_APP 0
# else
#  define REGAL_LOG_APP 1
# endif
#endif

#ifndef REGAL_LOG_DRIVER
# ifdef NDEBUG
#  define REGAL_LOG_DRIVER 0
# else
#  define REGAL_LOG_DRIVER 1
# endif
#endif

#ifndef REGAL_LOG_INTERNAL
# ifdef NDEBUG
#  define REGAL_LOG_INTERNAL 0
# else
#  define REGAL_LOG_INTERNAL 1
# endif
#endif

#ifndef REGAL_LOG_HTTP
# define REGAL_LOG_HTTP 1
#endif

#ifndef REGAL_LOG
# ifdef NDEBUG
#  define REGAL_LOG 0
# else
#  define REGAL_LOG 1
# endif
#endif

#ifndef REGAL_LOG_MAX_LINES
# define REGAL_LOG_MAX_LINES -1 // unlimited by default
#endif

#ifndef REGAL_LOG_MAX_BYTES
# define REGAL_LOG_MAX_BYTES -1 // unlimited by default
#endif

#ifndef REGAL_LOG_POINTERS
# define REGAL_LOG_POINTERS 1
#endif

#ifndef REGAL_LOG_THREAD
# define REGAL_LOG_THREAD 1
#endif

#ifndef REGAL_LOG_ONCE
# define REGAL_LOG_ONCE 1
#endif

#ifndef REGAL_LOG_JSON
# define REGAL_LOG_JSON 1
#endif

#ifndef REGAL_LOG_CALLBACK
# define REGAL_LOG_CALLBACK 1
#endif

#ifdef REGAL_LOG_ALL
# undef REGAL_LOG_ERROR
# undef REGAL_LOG_WARNING
# undef REGAL_LOG_INFO
# undef REGAL_LOG_APP
# undef REGAL_LOG_DRIVER
# undef REGAL_LOG_INTERNAL
# undef REGAL_LOG_HTTP
# define REGAL_LOG_ERROR    REGAL_LOG_ALL
# define REGAL_LOG_WARNING  REGAL_LOG_ALL
# define REGAL_LOG_INFO     REGAL_LOG_ALL
# define REGAL_LOG_APP      REGAL_LOG_ALL
# define REGAL_LOG_DRIVER   REGAL_LOG_ALL
# define REGAL_LOG_INTERNAL REGAL_LOG_ALL
# define REGAL_LOG_HTTP     REGAL_LOG_ALL
#endif

namespace Logging
{
  extern void Init();
  extern void Cleanup();

  extern void writeJSON(Json::Output &jo);

  // GL_REGAL_log

  enum Mode
  {
    LOG_ERROR    = 0,
    LOG_WARNING,
    LOG_INFO,
    LOG_APP,
    LOG_DRIVER,
    LOG_INTERNAL,
    LOG_DEBUG,
    LOG_STATUS,
    LOG_HTTP
  };

  extern void Output(const Mode mode, const char *file, const int line, const char *prefix, const char *delim, const char *name, const std::string &str = std::string());

  // Runtime control of logging

  extern bool enableError;
  extern bool enableWarning;
  extern bool enableInfo;
  extern bool enableApp;
  extern bool enableDriver;
  extern bool enableInternal;
  extern bool enableHttp;

  // Logging configuration

  extern int  maxLines;
  extern int  maxBytes;

  extern bool frameTime;        // Per-frame elapsed time to info log

  extern bool pointers;         // Enabled by default, otherwise empty
  extern bool thread;           // Disabled by default

#if REGAL_LOG_ONCE
  extern bool once;             // Warning and error message logged once only
  extern std::set<std::string> uniqueErrors;
  extern std::set<std::string> uniqueWarnings;
#endif

  // Callback output

  extern bool callback;

  // Logging output

  extern bool         log;
  extern std::string  logFilename;
  extern FILE        *logOutput;

  // JSON output

  extern bool         json;
  extern std::string  jsonFilename;
  extern FILE        *jsonOutput;

  // Buffering for HTTP query purposes

  extern std::list<std::string> *buffer;
  extern std::size_t             bufferSize;
  extern std::size_t             bufferLimit;

  // Internal housekeeping

  extern bool initialized;

  //

  template<typename T>
  T rawLimit(const T size) { return maxBytes<0 ? size : ( size < maxBytes ? size : maxBytes ); }
}

#if REGAL_LOG_ERROR
#define Error(...)   { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableError) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_ERROR, __FILE__, __LINE__, "error   ", " | ", NULL, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define Error(...) {}
#endif

#if REGAL_LOG_WARNING
#define Warning(...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableWarning) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_WARNING, __FILE__, __LINE__, "warning ", " | ", NULL, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define Warning(...) {}
#endif

#if REGAL_LOG_INFO
#define Info(...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableInfo) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_INFO, __FILE__, __LINE__, "info    ", " | ", NULL, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define Info(...) {}
#endif

#if REGAL_LOG_APP
#define App(name,...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableApp) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_APP, __FILE__, __LINE__, "app     ", " | ", name, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define App(...) {}
#endif

#if REGAL_LOG_DRIVER
#define Driver(name,...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableDriver) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_DRIVER, __FILE__, __LINE__, "driver  ", " | ", name, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define Driver(...) {}
#endif

#if REGAL_LOG_INTERNAL
#define Internal(name,...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableInternal) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_INTERNAL, __FILE__, __LINE__, "internal", " | ", name, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define Internal(...) {}
#endif

#if REGAL_LOG_HTTP
#define HTrace(...) { \
  if (::REGAL_NAMESPACE_INTERNAL::Logging::enableHttp) \
    ::REGAL_NAMESPACE_INTERNAL::Logging::Output( ::REGAL_NAMESPACE_INTERNAL::Logging::LOG_HTTP, __FILE__, __LINE__, "http    ", " | ", NULL, ::boost::print::print_string( __VA_ARGS__) ); }
#else
#define HTrace(...) {}
#endif

REGAL_NAMESPACE_END

#endif
