/*
 * Copyright (c) 2010-2013 NVIDIA Corporation
 * Copyright (c) 2010-2013 Nigel Stewart
 * All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * boost::print is a library for string conversion.
 * boost::print is not currently a part of boost.
 */

#ifndef BOOST_PRINT_JSON_HPP
#define BOOST_PRINT_JSON_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <string>

#include <boost/print/core.hpp>
#include <boost/print/interface.hpp>
#include <boost/print/string_list.hpp>

// See: http://www.json.org/

namespace boost { namespace print { namespace json {

  using ::boost::print::pad;

  template< typename T = ::std::string >
  struct output : public ::boost::print::string_list< T >
  {
    public:
      inline output() : _empty(true), _nesting(0) {}

      // Each nested object must be concluded with a call to end()

      inline                 void object();
      template< typename N > void object(const N &name);
      inline                 void end();

      template< typename N > void member(const N &name);                           // name : null
      template< typename N > void member(const N &name, const char          *val); // name : "the text"
      template< typename N > void member(const N &name, const ::std::string &val); // name : "the text"
      template< typename N > void member(const N &name, const N             &val); // name : "the text"

      template< typename N, typename V > void member(const N &name, const V &val);

    private:
      bool   _empty;
      size_t _nesting;
  };

  template< typename T>
  void output<T>::object()
  {
    T tmp;
    print(tmp, pad(_nesting), "{");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = true;
    _nesting++;
  }

  template< typename T>
  template< typename N >
  void output<T>::object(const N &name)
  {
    T tmp;
    print(tmp, _empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : {");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = true;
    _nesting++;
  }

  template< typename T>
  void output<T>::end()
  {
    if (_nesting--)
    {
      T tmp;
      print(tmp, "\n", pad(_nesting), "}");
      ::boost::print::string_list<T>::push_back_swap(tmp);
    }
  }

  template< typename T>
  template< typename N >
  void output<T>::member(const N &name)
  {
    T tmp;
    print(tmp, _empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : null");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = false;
  }

  template< typename T>
  template< typename N >
  void output<T>::member(const N &name, const char *val)
  {
    T tmp;
    print(tmp, _empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : \"",val,"\"");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = false;
  }

  template< typename T>
  template< typename N >
  void output<T>::member(const N &name, const ::std::string &val)
  {
    T tmp;
    print(tmp, _empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : \"",val,"\"");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = false;
  }

  template< typename T>
  template< typename N >
  void output<T>::member(const N &name, const N &val)
  {
    T tmp;
    print(tmp, _empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : \"",val,"\"");
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = false;
  }

  template< typename T>
  template< typename N, typename U >
  void output<T>::member(const N &name, const U &val)
  {
    T tmp;
    print(tmp,_empty ? "\n" : ",\n", pad(_nesting), "\"", name, "\" : ",val);
    ::boost::print::string_list<T>::push_back_swap(tmp);
    _empty = false;
  }

}}}

#endif
