//////////////////////////////////////////////////////////////////////////////
//
//  Half Float Example / Test Code
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


#include <cstdio>
#include <cstdint>
#include <random>

#include "HalfFloat.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////

static void test(size_t count, std::uniform_real_distribution<> &dist, std::mt19937 &gen);

//////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
#pragma unused(argc)
#pragma unused(argv)
   
   std::random_device dev;
   std::mt19937 gen(dev());
   std::uniform_real_distribution<> smallDist(0, 1);
   std::uniform_real_distribution<> largeDist(20, 100);
   
   printf("Small numbers:\n");
   test(10, smallDist, gen);
   
   printf("\nLarge-ish numbers:\n");
   test(10, largeDist, gen);
   
   return 0;
}

//////////////////////////////////////////////////////////////////////////////

static void test(size_t count, std::uniform_real_distribution<> &dist, std::mt19937 &gen)
{
   for (size_t i = 0; i < count; ++i)
   {
      float val = dist(gen);
      HalfFloat halfVal = val;
      float backConv = halfVal;
      float error = backConv - val;
      printf("   original = %f  half = %f  error = %f\n", val, backConv, error);
   }
}
