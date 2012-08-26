//
//  main.cpp
//  TestHalfFloat
//
//  Created by Tom Bampton on 26/08/2012.
//  Copyright (c) 2012 Burnt Wasp. All rights reserved.
//

#include <cstdio>
#include <cstdint>
#include <random>

#include "HalfFloat.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
#pragma unused(argc)
#pragma unused(argv)
   
   std::random_device dev;
   std::mt19937 gen(dev());
   std::uniform_real_distribution<> dist(0, 4);
   
   for (size_t i = 0; i < 20; ++i)
   {
      float val = dist(gen);
      HalfFloat halfVal = val;
      float backConv = halfVal;
      float error = backConv - val;
      printf("Original = %f Half = %f Error = %f\n", val, backConv, error);
   }
   
   return 0;
}
