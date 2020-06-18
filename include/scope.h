/*
   Copyright (c) 2020, MariaDB Corporation.
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1335
   USA */

#pragma once

template <typename T> class Scope_value
{
public:
  Scope_value(T &variable, const T &scope_value)
      : variable_(variable), saved_value_(variable)
  {
    variable= scope_value;
  }

  Scope_value(Scope_value &&rhs)
      : variable_(rhs.variable_), saved_value_(rhs.saved_value_),
        engaged_(rhs.engaged_)
  {
    rhs.engaged_= false;
  }

  Scope_value(const Scope_value &)= delete;
  Scope_value &operator=(const Scope_value &)= delete;
  Scope_value &operator=(Scope_value &&)= delete;

  ~Scope_value()
  {
    if (engaged_)
      variable_= saved_value_;
  }

private:
  T &variable_;
  T saved_value_;
  bool engaged_= true;
};

// Use like this:
// auto _ = make_scope_value(var, tmp_value);
template <typename T>
Scope_value<T> make_scope_value(T &variable, const T &scope_value)
{
  return Scope_value<T>(variable, scope_value);
}
