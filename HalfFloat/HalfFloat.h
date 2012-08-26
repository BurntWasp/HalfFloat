//////////////////////////////////////////////////////////////////////////////
//
//  Half Float
//  Copyright (c) 2012 Burnt Wasp
//
//  See ftp://ftp.fox-toolkit.org/pub/fasthalffloatconversion.pdf for more
//  information.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BW_HALFFLOAT_H
#define BW_HALFFLOAT_H

#include <cstdint>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////
// Half Float
//////////////////////////////////////////////////////////////////////////////
#pragma mark - Half Float

class HalfFloat
{
   static const uint32_t MantissaTable[2048];
   static const uint32_t ExponentTable[64];
   static const uint32_t OffsetTable[64];
   static const uint16_t BaseTable[512];
   static const uint16_t ShiftTable[512];
   
   uint16_t mRep;
   
public:
   HalfFloat() = default;
   HalfFloat(float value) noexcept
   {
      *this = value;
   }
   
   inline HalfFloat &operator =(const float value) noexcept
   {
      const uint32_t f = *(uint32_t *)(&value);
      const uint32_t offset = (f >> 23) & 0x1ff;
      mRep = BaseTable[offset] + ((f & 0x007fffff) >> ShiftTable[offset]);
      return *this;
   }
   
   inline operator float() const noexcept
   {
      const uint32_t offset = mRep >> 10;
      const uint32_t f = MantissaTable[OffsetTable[offset] + (mRep & 0x3ff)] + ExponentTable[offset];
      return *(float *)(&f);
   }
};

//////////////////////////////////////////////////////////////////////////////
// Type Traits
//////////////////////////////////////////////////////////////////////////////
#pragma mark - Type Traits

template <> struct std::__is_floating_point<HalfFloat> : public std::true_type {};

//////////////////////////////////////////////////////////////////////////////
// Validity Checks
//////////////////////////////////////////////////////////////////////////////
#pragma mark - Validity Checks

// These checks ensure that HalfFloat (or an array of HalfFloats) will have the
// correct binary representation when written to a file or passed to OpenGL.

static_assert(sizeof(HalfFloat) == sizeof(uint16_t), "sizeof(HalfFloat) no longer matches sizeof(uint16_t)");

static_assert(std::is_trivial<HalfFloat>::value, "HalfFloat is no longer trivial");
static_assert(std::is_standard_layout<HalfFloat>::value, "HalfFloat is no longer standard layout");

static_assert(std::is_floating_point<HalfFloat>::value, "HalfFloat is not floating point");

//////////////////////////////////////////////////////////////////////////////
#endif // BW_HALFFLOAT_H
