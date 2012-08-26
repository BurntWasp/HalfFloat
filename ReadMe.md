C++ Half Float
==============

This is a C++ implementation of 16bit half precision floating point, based on the algorithms from [this paper by Jeroen van der Zijp][paper]. Although C++11 is used, it is trivial to backport to earlier revisions of the standard.

This was originally written for offline conversion of single precision floating point textures to half float, but it is not limited to that use. There are no dependencies beyond the standard library.

Using
-----

Simply drop HalfFloat/HalfFloat.cpp and HalfFloat/HalfFloat.h into your project and start using it. You do not need anything else.

Implicit conversions are provided to and from float. Math operators are not provided, but the compiler will automatically promote so math should work normally. However, due to the very low precision, you should not generally be doing math on half floats.

The memory layout of HalfFloat matches that of a uint16\_t. An array of HalfFloats can be passed to OpenGL or DirectX as a texture. The layout is checked with static\_assert so any changes that break the layout will produce a compiler error.

A somewhat lame example is provided in the TestHalfFloat directory; it just generates a bunch of random half floats and does some conversions.

The code used to generate the lookup tables for float conversion is provided in the MakeHalfFloatTables directory. This is provided for interest purposes only; unless a bug is found in the tables, there's no need to regenerate them.

Xcode projects are provided for both of the above apps. If you want to compile on another platform, you'll have to either make a project or compile it from the command line manually. You do not need either to use the HalfFloat class.

Compiler Support
----------------

This has been tested using the version of clang provided with Xcode 4.4.1, which is based on clang 3.1. The only C++11 features used are default constructors, static\_assert, noexcept keyword and type traits.

If your compiler does not support one or more of these features:

* static asserts and type traits can be commented out
* The noexcept keyword can be removed
* The defaulted constructor can be replaced with an empty constructor

License
-------

Copyright (c) 2012 Burnt Wasp

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

[paper]: ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf
