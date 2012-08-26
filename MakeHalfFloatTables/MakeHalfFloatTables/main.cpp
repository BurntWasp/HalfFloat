//////////////////////////////////////////////////////////////////////////////
//
//  Half Float Table Generator
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

//////////////////////////////////////////////////////////////////////////////

using namespace std;

//////////////////////////////////////////////////////////////////////////////

static uint32_t convertMantissa(uint32_t i);

//////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
#pragma unused(argc)
#pragma unused(argv)
   
   // HALF FLOAT -> FLOAT TABLES
   
   // Write mantissa table
   printf("static const uint32_t MantissaTable[2048]=\n{\n");
   
   printf("   0x00000000, ");
   
   for (uint32_t i = 1; i < 2048; ++i)
   {
      if (i < 1024)
         printf("0x%08x", convertMantissa(i));
      else
         printf("0x%08x", (0x38000000 + ((i - 1024) << 13)));
      
      if (i < 2047)
         printf(", ");
      
      if ((i + 1) % 10 == 0)
         printf("\n   ");
   }
   
   printf("\n};\n\n");
   
   // Write exponent table
   printf("static const uint32_t ExponentTable[64]=\n{\n   ");
   
   for (uint32_t i = 0; i < 64; ++i)
   {
      switch (i)
      {
         case 0:
            printf("0x%08x", 0);
            break;
            
         case 31:
            printf("0x%08x", 0x47800000);
            break;
            
         case 63:
            printf("0x%08x", 0xc7800000);
            break;
            
         case 32:
            printf("0x%08x", 0x80000000);
            break;
            
         default:
            if (i < 30)
               printf("0x%08x", (i << 23));
            else
               printf("0x%08x", (0x80000000 + (i - 32) << 23));
            break;
      }
      
      if (i < 63)
         printf(", ");
      
      if ((i + 1) % 10 == 0)
         printf("\n   ");
   }
   
   printf("\n};\n\n");
   
   // Write offset table
   printf("static const uint32_t OffsetTable[64]=\n{\n   ");
   for (uint32_t i = 0; i < 64; ++i)
   {
      switch (i)
      {
         case 0:
         case 32:
            printf("0x%08x", 0);
            break;
            
         default:
            printf("0x%08x", 1024);
            break;
      }
      
      if (i < 63)
         printf(", ");
      
      if ((i + 1) % 10 == 0)
         printf("\n   ");
   }
   printf("\n};\n\n");
   
   // FLOAT -> HALF FLOAT TABLES

   // This is copy/pasted straight from the pdf linked at the top of this file
   uint16_t baseTable[512], shiftTable[512];
   
   for (int i = 0; i < 256; ++i)
   {
      int e = i - 127;
      
      if(e<-24)
      {
         // Very small numbers map to zero
         baseTable[i|0x000]=0x0000;
         baseTable[i|0x100]=0x8000;
         shiftTable[i|0x000]=24;
         shiftTable[i|0x100]=24;
      }
      else if(e<-14)
      {
         // Small numbers map to denorms
         baseTable[i|0x000]=(0x0400>>(-e-14));
         baseTable[i|0x100]=(0x0400>>(-e-14)) | 0x8000;
         shiftTable[i|0x000]=-e-1;
         shiftTable[i|0x100]=-e-1;
      }
      else if(e<=15)
      {
         // Normal numbers just lose precision
         baseTable[i|0x000]=((e+15)<<10);
         baseTable[i|0x100]=((e+15)<<10) | 0x8000;
         shiftTable[i|0x000]=13;
         shiftTable[i|0x100]=13;
      }
      else if(e<128)
      {
         // Large numbers map to Infinity
         baseTable[i|0x000]=0x7C00;
         baseTable[i|0x100]=0xFC00;
         shiftTable[i|0x000]=24;
         shiftTable[i|0x100]=24;
      }
      else
      {
         // Infinity and NaN's stay Infinity and NaN's
         baseTable[i|0x000]=0x7C00;
         baseTable[i|0x100]=0xFC00;
         shiftTable[i|0x000]=13;
         shiftTable[i|0x100]=13;
      }
   }
   
   // Write base table
   printf("static const uint16_t BaseTable[512]=\n{\n   ");
   for (uint32_t i = 0; i < 512; ++i)
   {
      printf("0x%04x", baseTable[i]);
      
      if (i < 511)
         printf(", ");
      
      if ((i + 1) % 10 == 0)
         printf("\n   ");
   }
   printf("\n};\n\n");
   
   // Write shift table
   printf("static const uint16_t ShiftTable[512]=\n{\n   ");
   for (uint32_t i = 0; i < 512; ++i)
   {
      printf("0x%04x", shiftTable[i]);
      
      if (i < 511)
         printf(", ");
      
      if ((i + 1) % 10 == 0)
         printf("\n   ");
   }
   printf("\n};\n");

   return 0;
}

//////////////////////////////////////////////////////////////////////////////

static uint32_t convertMantissa(uint32_t i)
{
   uint32_t m = i << 13;
   uint32_t e = 0;
   
   while ((m & 0x00800000) != 0)
   {
      e -= 0x00800000;
      m <<= 1;
   }
   
   m &= ~ 0x00800000;
   e += 0x38800000;
   return m | e;
}
