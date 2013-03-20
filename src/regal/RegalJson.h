/*
  Copyright (c) 2011-2013 NVIDIA Corporation
  Copyright (c) 2011-2013 Cass Everitt
  Copyright (c) 2012-2013 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012-2013 Nigel Stewart
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

/*

 Convenient JSON encoding
 Nigel Stewart

 */

#ifndef __REGAL_JSON_H__
#define __REGAL_JSON_H__

// http://www.json.org/

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <string>

#include <boost/print/string_list.hpp>

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

namespace Json
{
  using ::std::string;

  using ::boost::print::string_list;
  using ::boost::print::print_string;
  using ::boost::print::pad;

  struct Output : public string_list< string >
  {
    public:
      inline Output() : _empty(true), _nesting(0) {}

      // Each nested object must be concluded with a call to end()

      inline void object(const char   *name);
      inline void object(const string &name);

      inline void member(const char *name);                      // name : null
      inline void member(const char *name, const char   *val);   // name : "the text"
      inline void member(const char *name, const string &val);   // name : "the text"

      template< typename T > void member(const char *name, const T &val);

      inline void end();

    private:
      bool   _empty;
      size_t _nesting;
  };

  void Output::object(const char *name)
  {
    string tmp = print_string(_empty ? "\n" : ",\n", pad(_nesting), name, " {");
    push_back_swap(tmp);
    _empty = true;
    _nesting++;
  }

  void Output::object(const string &name)
  {
    object(name.c_str());
  }

  void Output::end()
  {
    if (_nesting--)
    {
      string tmp = print_string("\n", pad(_nesting), "}");
      push_back_swap(tmp);
    }
  }

  void Output::member(const char *name)
  {
    string tmp = print_string(_empty ? "\n" : ",\n", pad(_nesting), name," : null");
    push_back_swap(tmp);
    _empty = false;
  }

  void Output::member(const char *name, const char *val)
  {
    string tmp = print_string(_empty ? "\n" : ",\n", pad(_nesting), name," : \"",val,"\"");
    push_back_swap(tmp);
    _empty = false;
  }

  void Output::member(const char *name, const string &val)
  {
    member(name,val.c_str());
  }

  template<typename T>
  void Output::member(const char *name, const T &val)
  {
    string tmp = print_string(_empty ? "\n" : ",\n", pad(_nesting), name," : ",val);
    push_back_swap(tmp);
    _empty = false;
  }

}

REGAL_NAMESPACE_END

#endif
