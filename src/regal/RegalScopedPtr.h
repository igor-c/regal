/*
  Copyright (c) 2011-2013 NVIDIA Corporation
  Copyright (c) 2013-2013 Cass Everitt
  Copyright (c) 2013-2013 Nigel Stewart
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

 boost::scoped_ptr and boost::scoped_array for Regal
 Cass Everitt, Nigel Stewart

*/

#ifndef __REGAL_SCOPED_PTR_H__
#define __REGAL_SCOPED_PTR_H__

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

template<typename T>
class scoped_ptr
{
  public:
    inline scoped_ptr(T *value = NULL) : _value(value) {}
    inline ~scoped_ptr()                               { delete _value; }

    inline scoped_ptr &operator=(T *value)
    {
      if (_value)
        delete _value;
      _value = value;
      return *this;
    }

    inline void reset(T *value)
    {
      operator=(value);
    }

    inline       T &operator*()        { return *_value; }
    inline const T &operator*()  const { return *_value; }

    inline       T *operator->()       { return _value; }
    inline const T *operator->() const { return _value; }

    inline       T *get()              { return _value; }
    inline const T *get()        const { return _value; }

    inline operator       T *()        { return _value; }
    inline operator const T *()  const { return _value; }

  private:
    inline scoped_ptr(const scoped_ptr &other)            {}
    inline scoped_ptr &operator=(const scoped_ptr &other) { return *this; }

    T      *_value;
};

template<typename T>
class scoped_array
{
  public:
    inline scoped_array(T *value = NULL) : _value(value) {}
    inline ~scoped_array()                               { delete [] _value; }

    inline scoped_array &operator=(T *value)
    {
      if (_value)
        delete [] _value;
      _value = value;
      return *this;
    }

    inline void reset(T *value)
    {
      operator=(value);
    }

    inline       T &operator*()        { return *_value; }
    inline const T &operator*()  const { return *_value; }

    inline       T *operator->()       { return _value; }
    inline const T *operator->() const { return _value; }

    inline       T *get()              { return _value; }
    inline const T *get()        const { return _value; }

    inline operator       T *()        { return _value; }
    inline operator const T *()  const { return _value; }

  private:
    inline scoped_array(const scoped_array &other)            {}
    inline scoped_array &operator=(const scoped_array &other) { return *this; }

    T      *_value;
};

REGAL_NAMESPACE_END

#endif
