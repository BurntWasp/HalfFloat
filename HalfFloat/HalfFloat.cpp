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

#include "HalfFloat.h"

//////////////////////////////////////////////////////////////////////////////
// Lookup Tables
//////////////////////////////////////////////////////////////////////////////
#pragma mark - Lookup Tables

const uint32_t HalfFloat::MantissaTable[2048]=
{
   0x00000000, 0x38802000, 0x38804000, 0x38806000, 0x38808000, 0x3880a000, 0x3880c000, 0x3880e000, 0x38810000, 0x38812000,
   0x38814000, 0x38816000, 0x38818000, 0x3881a000, 0x3881c000, 0x3881e000, 0x38820000, 0x38822000, 0x38824000, 0x38826000,
   0x38828000, 0x3882a000, 0x3882c000, 0x3882e000, 0x38830000, 0x38832000, 0x38834000, 0x38836000, 0x38838000, 0x3883a000,
   0x3883c000, 0x3883e000, 0x38840000, 0x38842000, 0x38844000, 0x38846000, 0x38848000, 0x3884a000, 0x3884c000, 0x3884e000,
   0x38850000, 0x38852000, 0x38854000, 0x38856000, 0x38858000, 0x3885a000, 0x3885c000, 0x3885e000, 0x38860000, 0x38862000,
   0x38864000, 0x38866000, 0x38868000, 0x3886a000, 0x3886c000, 0x3886e000, 0x38870000, 0x38872000, 0x38874000, 0x38876000,
   0x38878000, 0x3887a000, 0x3887c000, 0x3887e000, 0x38880000, 0x38882000, 0x38884000, 0x38886000, 0x38888000, 0x3888a000,
   0x3888c000, 0x3888e000, 0x38890000, 0x38892000, 0x38894000, 0x38896000, 0x38898000, 0x3889a000, 0x3889c000, 0x3889e000,
   0x388a0000, 0x388a2000, 0x388a4000, 0x388a6000, 0x388a8000, 0x388aa000, 0x388ac000, 0x388ae000, 0x388b0000, 0x388b2000,
   0x388b4000, 0x388b6000, 0x388b8000, 0x388ba000, 0x388bc000, 0x388be000, 0x388c0000, 0x388c2000, 0x388c4000, 0x388c6000,
   0x388c8000, 0x388ca000, 0x388cc000, 0x388ce000, 0x388d0000, 0x388d2000, 0x388d4000, 0x388d6000, 0x388d8000, 0x388da000,
   0x388dc000, 0x388de000, 0x388e0000, 0x388e2000, 0x388e4000, 0x388e6000, 0x388e8000, 0x388ea000, 0x388ec000, 0x388ee000,
   0x388f0000, 0x388f2000, 0x388f4000, 0x388f6000, 0x388f8000, 0x388fa000, 0x388fc000, 0x388fe000, 0x38900000, 0x38902000,
   0x38904000, 0x38906000, 0x38908000, 0x3890a000, 0x3890c000, 0x3890e000, 0x38910000, 0x38912000, 0x38914000, 0x38916000,
   0x38918000, 0x3891a000, 0x3891c000, 0x3891e000, 0x38920000, 0x38922000, 0x38924000, 0x38926000, 0x38928000, 0x3892a000,
   0x3892c000, 0x3892e000, 0x38930000, 0x38932000, 0x38934000, 0x38936000, 0x38938000, 0x3893a000, 0x3893c000, 0x3893e000,
   0x38940000, 0x38942000, 0x38944000, 0x38946000, 0x38948000, 0x3894a000, 0x3894c000, 0x3894e000, 0x38950000, 0x38952000,
   0x38954000, 0x38956000, 0x38958000, 0x3895a000, 0x3895c000, 0x3895e000, 0x38960000, 0x38962000, 0x38964000, 0x38966000,
   0x38968000, 0x3896a000, 0x3896c000, 0x3896e000, 0x38970000, 0x38972000, 0x38974000, 0x38976000, 0x38978000, 0x3897a000,
   0x3897c000, 0x3897e000, 0x38980000, 0x38982000, 0x38984000, 0x38986000, 0x38988000, 0x3898a000, 0x3898c000, 0x3898e000,
   0x38990000, 0x38992000, 0x38994000, 0x38996000, 0x38998000, 0x3899a000, 0x3899c000, 0x3899e000, 0x389a0000, 0x389a2000,
   0x389a4000, 0x389a6000, 0x389a8000, 0x389aa000, 0x389ac000, 0x389ae000, 0x389b0000, 0x389b2000, 0x389b4000, 0x389b6000,
   0x389b8000, 0x389ba000, 0x389bc000, 0x389be000, 0x389c0000, 0x389c2000, 0x389c4000, 0x389c6000, 0x389c8000, 0x389ca000,
   0x389cc000, 0x389ce000, 0x389d0000, 0x389d2000, 0x389d4000, 0x389d6000, 0x389d8000, 0x389da000, 0x389dc000, 0x389de000,
   0x389e0000, 0x389e2000, 0x389e4000, 0x389e6000, 0x389e8000, 0x389ea000, 0x389ec000, 0x389ee000, 0x389f0000, 0x389f2000,
   0x389f4000, 0x389f6000, 0x389f8000, 0x389fa000, 0x389fc000, 0x389fe000, 0x38a00000, 0x38a02000, 0x38a04000, 0x38a06000,
   0x38a08000, 0x38a0a000, 0x38a0c000, 0x38a0e000, 0x38a10000, 0x38a12000, 0x38a14000, 0x38a16000, 0x38a18000, 0x38a1a000,
   0x38a1c000, 0x38a1e000, 0x38a20000, 0x38a22000, 0x38a24000, 0x38a26000, 0x38a28000, 0x38a2a000, 0x38a2c000, 0x38a2e000,
   0x38a30000, 0x38a32000, 0x38a34000, 0x38a36000, 0x38a38000, 0x38a3a000, 0x38a3c000, 0x38a3e000, 0x38a40000, 0x38a42000,
   0x38a44000, 0x38a46000, 0x38a48000, 0x38a4a000, 0x38a4c000, 0x38a4e000, 0x38a50000, 0x38a52000, 0x38a54000, 0x38a56000,
   0x38a58000, 0x38a5a000, 0x38a5c000, 0x38a5e000, 0x38a60000, 0x38a62000, 0x38a64000, 0x38a66000, 0x38a68000, 0x38a6a000,
   0x38a6c000, 0x38a6e000, 0x38a70000, 0x38a72000, 0x38a74000, 0x38a76000, 0x38a78000, 0x38a7a000, 0x38a7c000, 0x38a7e000,
   0x38a80000, 0x38a82000, 0x38a84000, 0x38a86000, 0x38a88000, 0x38a8a000, 0x38a8c000, 0x38a8e000, 0x38a90000, 0x38a92000,
   0x38a94000, 0x38a96000, 0x38a98000, 0x38a9a000, 0x38a9c000, 0x38a9e000, 0x38aa0000, 0x38aa2000, 0x38aa4000, 0x38aa6000,
   0x38aa8000, 0x38aaa000, 0x38aac000, 0x38aae000, 0x38ab0000, 0x38ab2000, 0x38ab4000, 0x38ab6000, 0x38ab8000, 0x38aba000,
   0x38abc000, 0x38abe000, 0x38ac0000, 0x38ac2000, 0x38ac4000, 0x38ac6000, 0x38ac8000, 0x38aca000, 0x38acc000, 0x38ace000,
   0x38ad0000, 0x38ad2000, 0x38ad4000, 0x38ad6000, 0x38ad8000, 0x38ada000, 0x38adc000, 0x38ade000, 0x38ae0000, 0x38ae2000,
   0x38ae4000, 0x38ae6000, 0x38ae8000, 0x38aea000, 0x38aec000, 0x38aee000, 0x38af0000, 0x38af2000, 0x38af4000, 0x38af6000,
   0x38af8000, 0x38afa000, 0x38afc000, 0x38afe000, 0x38b00000, 0x38b02000, 0x38b04000, 0x38b06000, 0x38b08000, 0x38b0a000,
   0x38b0c000, 0x38b0e000, 0x38b10000, 0x38b12000, 0x38b14000, 0x38b16000, 0x38b18000, 0x38b1a000, 0x38b1c000, 0x38b1e000,
   0x38b20000, 0x38b22000, 0x38b24000, 0x38b26000, 0x38b28000, 0x38b2a000, 0x38b2c000, 0x38b2e000, 0x38b30000, 0x38b32000,
   0x38b34000, 0x38b36000, 0x38b38000, 0x38b3a000, 0x38b3c000, 0x38b3e000, 0x38b40000, 0x38b42000, 0x38b44000, 0x38b46000,
   0x38b48000, 0x38b4a000, 0x38b4c000, 0x38b4e000, 0x38b50000, 0x38b52000, 0x38b54000, 0x38b56000, 0x38b58000, 0x38b5a000,
   0x38b5c000, 0x38b5e000, 0x38b60000, 0x38b62000, 0x38b64000, 0x38b66000, 0x38b68000, 0x38b6a000, 0x38b6c000, 0x38b6e000,
   0x38b70000, 0x38b72000, 0x38b74000, 0x38b76000, 0x38b78000, 0x38b7a000, 0x38b7c000, 0x38b7e000, 0x38b80000, 0x38b82000,
   0x38b84000, 0x38b86000, 0x38b88000, 0x38b8a000, 0x38b8c000, 0x38b8e000, 0x38b90000, 0x38b92000, 0x38b94000, 0x38b96000,
   0x38b98000, 0x38b9a000, 0x38b9c000, 0x38b9e000, 0x38ba0000, 0x38ba2000, 0x38ba4000, 0x38ba6000, 0x38ba8000, 0x38baa000,
   0x38bac000, 0x38bae000, 0x38bb0000, 0x38bb2000, 0x38bb4000, 0x38bb6000, 0x38bb8000, 0x38bba000, 0x38bbc000, 0x38bbe000,
   0x38bc0000, 0x38bc2000, 0x38bc4000, 0x38bc6000, 0x38bc8000, 0x38bca000, 0x38bcc000, 0x38bce000, 0x38bd0000, 0x38bd2000,
   0x38bd4000, 0x38bd6000, 0x38bd8000, 0x38bda000, 0x38bdc000, 0x38bde000, 0x38be0000, 0x38be2000, 0x38be4000, 0x38be6000,
   0x38be8000, 0x38bea000, 0x38bec000, 0x38bee000, 0x38bf0000, 0x38bf2000, 0x38bf4000, 0x38bf6000, 0x38bf8000, 0x38bfa000,
   0x38bfc000, 0x38bfe000, 0x38c00000, 0x38c02000, 0x38c04000, 0x38c06000, 0x38c08000, 0x38c0a000, 0x38c0c000, 0x38c0e000,
   0x38c10000, 0x38c12000, 0x38c14000, 0x38c16000, 0x38c18000, 0x38c1a000, 0x38c1c000, 0x38c1e000, 0x38c20000, 0x38c22000,
   0x38c24000, 0x38c26000, 0x38c28000, 0x38c2a000, 0x38c2c000, 0x38c2e000, 0x38c30000, 0x38c32000, 0x38c34000, 0x38c36000,
   0x38c38000, 0x38c3a000, 0x38c3c000, 0x38c3e000, 0x38c40000, 0x38c42000, 0x38c44000, 0x38c46000, 0x38c48000, 0x38c4a000,
   0x38c4c000, 0x38c4e000, 0x38c50000, 0x38c52000, 0x38c54000, 0x38c56000, 0x38c58000, 0x38c5a000, 0x38c5c000, 0x38c5e000,
   0x38c60000, 0x38c62000, 0x38c64000, 0x38c66000, 0x38c68000, 0x38c6a000, 0x38c6c000, 0x38c6e000, 0x38c70000, 0x38c72000,
   0x38c74000, 0x38c76000, 0x38c78000, 0x38c7a000, 0x38c7c000, 0x38c7e000, 0x38c80000, 0x38c82000, 0x38c84000, 0x38c86000,
   0x38c88000, 0x38c8a000, 0x38c8c000, 0x38c8e000, 0x38c90000, 0x38c92000, 0x38c94000, 0x38c96000, 0x38c98000, 0x38c9a000,
   0x38c9c000, 0x38c9e000, 0x38ca0000, 0x38ca2000, 0x38ca4000, 0x38ca6000, 0x38ca8000, 0x38caa000, 0x38cac000, 0x38cae000,
   0x38cb0000, 0x38cb2000, 0x38cb4000, 0x38cb6000, 0x38cb8000, 0x38cba000, 0x38cbc000, 0x38cbe000, 0x38cc0000, 0x38cc2000,
   0x38cc4000, 0x38cc6000, 0x38cc8000, 0x38cca000, 0x38ccc000, 0x38cce000, 0x38cd0000, 0x38cd2000, 0x38cd4000, 0x38cd6000,
   0x38cd8000, 0x38cda000, 0x38cdc000, 0x38cde000, 0x38ce0000, 0x38ce2000, 0x38ce4000, 0x38ce6000, 0x38ce8000, 0x38cea000,
   0x38cec000, 0x38cee000, 0x38cf0000, 0x38cf2000, 0x38cf4000, 0x38cf6000, 0x38cf8000, 0x38cfa000, 0x38cfc000, 0x38cfe000,
   0x38d00000, 0x38d02000, 0x38d04000, 0x38d06000, 0x38d08000, 0x38d0a000, 0x38d0c000, 0x38d0e000, 0x38d10000, 0x38d12000,
   0x38d14000, 0x38d16000, 0x38d18000, 0x38d1a000, 0x38d1c000, 0x38d1e000, 0x38d20000, 0x38d22000, 0x38d24000, 0x38d26000,
   0x38d28000, 0x38d2a000, 0x38d2c000, 0x38d2e000, 0x38d30000, 0x38d32000, 0x38d34000, 0x38d36000, 0x38d38000, 0x38d3a000,
   0x38d3c000, 0x38d3e000, 0x38d40000, 0x38d42000, 0x38d44000, 0x38d46000, 0x38d48000, 0x38d4a000, 0x38d4c000, 0x38d4e000,
   0x38d50000, 0x38d52000, 0x38d54000, 0x38d56000, 0x38d58000, 0x38d5a000, 0x38d5c000, 0x38d5e000, 0x38d60000, 0x38d62000,
   0x38d64000, 0x38d66000, 0x38d68000, 0x38d6a000, 0x38d6c000, 0x38d6e000, 0x38d70000, 0x38d72000, 0x38d74000, 0x38d76000,
   0x38d78000, 0x38d7a000, 0x38d7c000, 0x38d7e000, 0x38d80000, 0x38d82000, 0x38d84000, 0x38d86000, 0x38d88000, 0x38d8a000,
   0x38d8c000, 0x38d8e000, 0x38d90000, 0x38d92000, 0x38d94000, 0x38d96000, 0x38d98000, 0x38d9a000, 0x38d9c000, 0x38d9e000,
   0x38da0000, 0x38da2000, 0x38da4000, 0x38da6000, 0x38da8000, 0x38daa000, 0x38dac000, 0x38dae000, 0x38db0000, 0x38db2000,
   0x38db4000, 0x38db6000, 0x38db8000, 0x38dba000, 0x38dbc000, 0x38dbe000, 0x38dc0000, 0x38dc2000, 0x38dc4000, 0x38dc6000,
   0x38dc8000, 0x38dca000, 0x38dcc000, 0x38dce000, 0x38dd0000, 0x38dd2000, 0x38dd4000, 0x38dd6000, 0x38dd8000, 0x38dda000,
   0x38ddc000, 0x38dde000, 0x38de0000, 0x38de2000, 0x38de4000, 0x38de6000, 0x38de8000, 0x38dea000, 0x38dec000, 0x38dee000,
   0x38df0000, 0x38df2000, 0x38df4000, 0x38df6000, 0x38df8000, 0x38dfa000, 0x38dfc000, 0x38dfe000, 0x38e00000, 0x38e02000,
   0x38e04000, 0x38e06000, 0x38e08000, 0x38e0a000, 0x38e0c000, 0x38e0e000, 0x38e10000, 0x38e12000, 0x38e14000, 0x38e16000,
   0x38e18000, 0x38e1a000, 0x38e1c000, 0x38e1e000, 0x38e20000, 0x38e22000, 0x38e24000, 0x38e26000, 0x38e28000, 0x38e2a000,
   0x38e2c000, 0x38e2e000, 0x38e30000, 0x38e32000, 0x38e34000, 0x38e36000, 0x38e38000, 0x38e3a000, 0x38e3c000, 0x38e3e000,
   0x38e40000, 0x38e42000, 0x38e44000, 0x38e46000, 0x38e48000, 0x38e4a000, 0x38e4c000, 0x38e4e000, 0x38e50000, 0x38e52000,
   0x38e54000, 0x38e56000, 0x38e58000, 0x38e5a000, 0x38e5c000, 0x38e5e000, 0x38e60000, 0x38e62000, 0x38e64000, 0x38e66000,
   0x38e68000, 0x38e6a000, 0x38e6c000, 0x38e6e000, 0x38e70000, 0x38e72000, 0x38e74000, 0x38e76000, 0x38e78000, 0x38e7a000,
   0x38e7c000, 0x38e7e000, 0x38e80000, 0x38e82000, 0x38e84000, 0x38e86000, 0x38e88000, 0x38e8a000, 0x38e8c000, 0x38e8e000,
   0x38e90000, 0x38e92000, 0x38e94000, 0x38e96000, 0x38e98000, 0x38e9a000, 0x38e9c000, 0x38e9e000, 0x38ea0000, 0x38ea2000,
   0x38ea4000, 0x38ea6000, 0x38ea8000, 0x38eaa000, 0x38eac000, 0x38eae000, 0x38eb0000, 0x38eb2000, 0x38eb4000, 0x38eb6000,
   0x38eb8000, 0x38eba000, 0x38ebc000, 0x38ebe000, 0x38ec0000, 0x38ec2000, 0x38ec4000, 0x38ec6000, 0x38ec8000, 0x38eca000,
   0x38ecc000, 0x38ece000, 0x38ed0000, 0x38ed2000, 0x38ed4000, 0x38ed6000, 0x38ed8000, 0x38eda000, 0x38edc000, 0x38ede000,
   0x38ee0000, 0x38ee2000, 0x38ee4000, 0x38ee6000, 0x38ee8000, 0x38eea000, 0x38eec000, 0x38eee000, 0x38ef0000, 0x38ef2000,
   0x38ef4000, 0x38ef6000, 0x38ef8000, 0x38efa000, 0x38efc000, 0x38efe000, 0x38f00000, 0x38f02000, 0x38f04000, 0x38f06000,
   0x38f08000, 0x38f0a000, 0x38f0c000, 0x38f0e000, 0x38f10000, 0x38f12000, 0x38f14000, 0x38f16000, 0x38f18000, 0x38f1a000,
   0x38f1c000, 0x38f1e000, 0x38f20000, 0x38f22000, 0x38f24000, 0x38f26000, 0x38f28000, 0x38f2a000, 0x38f2c000, 0x38f2e000,
   0x38f30000, 0x38f32000, 0x38f34000, 0x38f36000, 0x38f38000, 0x38f3a000, 0x38f3c000, 0x38f3e000, 0x38f40000, 0x38f42000,
   0x38f44000, 0x38f46000, 0x38f48000, 0x38f4a000, 0x38f4c000, 0x38f4e000, 0x38f50000, 0x38f52000, 0x38f54000, 0x38f56000,
   0x38f58000, 0x38f5a000, 0x38f5c000, 0x38f5e000, 0x38f60000, 0x38f62000, 0x38f64000, 0x38f66000, 0x38f68000, 0x38f6a000,
   0x38f6c000, 0x38f6e000, 0x38f70000, 0x38f72000, 0x38f74000, 0x38f76000, 0x38f78000, 0x38f7a000, 0x38f7c000, 0x38f7e000,
   0x38f80000, 0x38f82000, 0x38f84000, 0x38f86000, 0x38f88000, 0x38f8a000, 0x38f8c000, 0x38f8e000, 0x38f90000, 0x38f92000,
   0x38f94000, 0x38f96000, 0x38f98000, 0x38f9a000, 0x38f9c000, 0x38f9e000, 0x38fa0000, 0x38fa2000, 0x38fa4000, 0x38fa6000,
   0x38fa8000, 0x38faa000, 0x38fac000, 0x38fae000, 0x38fb0000, 0x38fb2000, 0x38fb4000, 0x38fb6000, 0x38fb8000, 0x38fba000,
   0x38fbc000, 0x38fbe000, 0x38fc0000, 0x38fc2000, 0x38fc4000, 0x38fc6000, 0x38fc8000, 0x38fca000, 0x38fcc000, 0x38fce000,
   0x38fd0000, 0x38fd2000, 0x38fd4000, 0x38fd6000, 0x38fd8000, 0x38fda000, 0x38fdc000, 0x38fde000, 0x38fe0000, 0x38fe2000,
   0x38fe4000, 0x38fe6000, 0x38fe8000, 0x38fea000, 0x38fec000, 0x38fee000, 0x38ff0000, 0x38ff2000, 0x38ff4000, 0x38ff6000,
   0x38ff8000, 0x38ffa000, 0x38ffc000, 0x38ffe000, 0x38000000, 0x38002000, 0x38004000, 0x38006000, 0x38008000, 0x3800a000,
   0x3800c000, 0x3800e000, 0x38010000, 0x38012000, 0x38014000, 0x38016000, 0x38018000, 0x3801a000, 0x3801c000, 0x3801e000,
   0x38020000, 0x38022000, 0x38024000, 0x38026000, 0x38028000, 0x3802a000, 0x3802c000, 0x3802e000, 0x38030000, 0x38032000,
   0x38034000, 0x38036000, 0x38038000, 0x3803a000, 0x3803c000, 0x3803e000, 0x38040000, 0x38042000, 0x38044000, 0x38046000,
   0x38048000, 0x3804a000, 0x3804c000, 0x3804e000, 0x38050000, 0x38052000, 0x38054000, 0x38056000, 0x38058000, 0x3805a000,
   0x3805c000, 0x3805e000, 0x38060000, 0x38062000, 0x38064000, 0x38066000, 0x38068000, 0x3806a000, 0x3806c000, 0x3806e000,
   0x38070000, 0x38072000, 0x38074000, 0x38076000, 0x38078000, 0x3807a000, 0x3807c000, 0x3807e000, 0x38080000, 0x38082000,
   0x38084000, 0x38086000, 0x38088000, 0x3808a000, 0x3808c000, 0x3808e000, 0x38090000, 0x38092000, 0x38094000, 0x38096000,
   0x38098000, 0x3809a000, 0x3809c000, 0x3809e000, 0x380a0000, 0x380a2000, 0x380a4000, 0x380a6000, 0x380a8000, 0x380aa000,
   0x380ac000, 0x380ae000, 0x380b0000, 0x380b2000, 0x380b4000, 0x380b6000, 0x380b8000, 0x380ba000, 0x380bc000, 0x380be000,
   0x380c0000, 0x380c2000, 0x380c4000, 0x380c6000, 0x380c8000, 0x380ca000, 0x380cc000, 0x380ce000, 0x380d0000, 0x380d2000,
   0x380d4000, 0x380d6000, 0x380d8000, 0x380da000, 0x380dc000, 0x380de000, 0x380e0000, 0x380e2000, 0x380e4000, 0x380e6000,
   0x380e8000, 0x380ea000, 0x380ec000, 0x380ee000, 0x380f0000, 0x380f2000, 0x380f4000, 0x380f6000, 0x380f8000, 0x380fa000,
   0x380fc000, 0x380fe000, 0x38100000, 0x38102000, 0x38104000, 0x38106000, 0x38108000, 0x3810a000, 0x3810c000, 0x3810e000,
   0x38110000, 0x38112000, 0x38114000, 0x38116000, 0x38118000, 0x3811a000, 0x3811c000, 0x3811e000, 0x38120000, 0x38122000,
   0x38124000, 0x38126000, 0x38128000, 0x3812a000, 0x3812c000, 0x3812e000, 0x38130000, 0x38132000, 0x38134000, 0x38136000,
   0x38138000, 0x3813a000, 0x3813c000, 0x3813e000, 0x38140000, 0x38142000, 0x38144000, 0x38146000, 0x38148000, 0x3814a000,
   0x3814c000, 0x3814e000, 0x38150000, 0x38152000, 0x38154000, 0x38156000, 0x38158000, 0x3815a000, 0x3815c000, 0x3815e000,
   0x38160000, 0x38162000, 0x38164000, 0x38166000, 0x38168000, 0x3816a000, 0x3816c000, 0x3816e000, 0x38170000, 0x38172000,
   0x38174000, 0x38176000, 0x38178000, 0x3817a000, 0x3817c000, 0x3817e000, 0x38180000, 0x38182000, 0x38184000, 0x38186000,
   0x38188000, 0x3818a000, 0x3818c000, 0x3818e000, 0x38190000, 0x38192000, 0x38194000, 0x38196000, 0x38198000, 0x3819a000,
   0x3819c000, 0x3819e000, 0x381a0000, 0x381a2000, 0x381a4000, 0x381a6000, 0x381a8000, 0x381aa000, 0x381ac000, 0x381ae000,
   0x381b0000, 0x381b2000, 0x381b4000, 0x381b6000, 0x381b8000, 0x381ba000, 0x381bc000, 0x381be000, 0x381c0000, 0x381c2000,
   0x381c4000, 0x381c6000, 0x381c8000, 0x381ca000, 0x381cc000, 0x381ce000, 0x381d0000, 0x381d2000, 0x381d4000, 0x381d6000,
   0x381d8000, 0x381da000, 0x381dc000, 0x381de000, 0x381e0000, 0x381e2000, 0x381e4000, 0x381e6000, 0x381e8000, 0x381ea000,
   0x381ec000, 0x381ee000, 0x381f0000, 0x381f2000, 0x381f4000, 0x381f6000, 0x381f8000, 0x381fa000, 0x381fc000, 0x381fe000,
   0x38200000, 0x38202000, 0x38204000, 0x38206000, 0x38208000, 0x3820a000, 0x3820c000, 0x3820e000, 0x38210000, 0x38212000,
   0x38214000, 0x38216000, 0x38218000, 0x3821a000, 0x3821c000, 0x3821e000, 0x38220000, 0x38222000, 0x38224000, 0x38226000,
   0x38228000, 0x3822a000, 0x3822c000, 0x3822e000, 0x38230000, 0x38232000, 0x38234000, 0x38236000, 0x38238000, 0x3823a000,
   0x3823c000, 0x3823e000, 0x38240000, 0x38242000, 0x38244000, 0x38246000, 0x38248000, 0x3824a000, 0x3824c000, 0x3824e000,
   0x38250000, 0x38252000, 0x38254000, 0x38256000, 0x38258000, 0x3825a000, 0x3825c000, 0x3825e000, 0x38260000, 0x38262000,
   0x38264000, 0x38266000, 0x38268000, 0x3826a000, 0x3826c000, 0x3826e000, 0x38270000, 0x38272000, 0x38274000, 0x38276000,
   0x38278000, 0x3827a000, 0x3827c000, 0x3827e000, 0x38280000, 0x38282000, 0x38284000, 0x38286000, 0x38288000, 0x3828a000,
   0x3828c000, 0x3828e000, 0x38290000, 0x38292000, 0x38294000, 0x38296000, 0x38298000, 0x3829a000, 0x3829c000, 0x3829e000,
   0x382a0000, 0x382a2000, 0x382a4000, 0x382a6000, 0x382a8000, 0x382aa000, 0x382ac000, 0x382ae000, 0x382b0000, 0x382b2000,
   0x382b4000, 0x382b6000, 0x382b8000, 0x382ba000, 0x382bc000, 0x382be000, 0x382c0000, 0x382c2000, 0x382c4000, 0x382c6000,
   0x382c8000, 0x382ca000, 0x382cc000, 0x382ce000, 0x382d0000, 0x382d2000, 0x382d4000, 0x382d6000, 0x382d8000, 0x382da000,
   0x382dc000, 0x382de000, 0x382e0000, 0x382e2000, 0x382e4000, 0x382e6000, 0x382e8000, 0x382ea000, 0x382ec000, 0x382ee000,
   0x382f0000, 0x382f2000, 0x382f4000, 0x382f6000, 0x382f8000, 0x382fa000, 0x382fc000, 0x382fe000, 0x38300000, 0x38302000,
   0x38304000, 0x38306000, 0x38308000, 0x3830a000, 0x3830c000, 0x3830e000, 0x38310000, 0x38312000, 0x38314000, 0x38316000,
   0x38318000, 0x3831a000, 0x3831c000, 0x3831e000, 0x38320000, 0x38322000, 0x38324000, 0x38326000, 0x38328000, 0x3832a000,
   0x3832c000, 0x3832e000, 0x38330000, 0x38332000, 0x38334000, 0x38336000, 0x38338000, 0x3833a000, 0x3833c000, 0x3833e000,
   0x38340000, 0x38342000, 0x38344000, 0x38346000, 0x38348000, 0x3834a000, 0x3834c000, 0x3834e000, 0x38350000, 0x38352000,
   0x38354000, 0x38356000, 0x38358000, 0x3835a000, 0x3835c000, 0x3835e000, 0x38360000, 0x38362000, 0x38364000, 0x38366000,
   0x38368000, 0x3836a000, 0x3836c000, 0x3836e000, 0x38370000, 0x38372000, 0x38374000, 0x38376000, 0x38378000, 0x3837a000,
   0x3837c000, 0x3837e000, 0x38380000, 0x38382000, 0x38384000, 0x38386000, 0x38388000, 0x3838a000, 0x3838c000, 0x3838e000,
   0x38390000, 0x38392000, 0x38394000, 0x38396000, 0x38398000, 0x3839a000, 0x3839c000, 0x3839e000, 0x383a0000, 0x383a2000,
   0x383a4000, 0x383a6000, 0x383a8000, 0x383aa000, 0x383ac000, 0x383ae000, 0x383b0000, 0x383b2000, 0x383b4000, 0x383b6000,
   0x383b8000, 0x383ba000, 0x383bc000, 0x383be000, 0x383c0000, 0x383c2000, 0x383c4000, 0x383c6000, 0x383c8000, 0x383ca000,
   0x383cc000, 0x383ce000, 0x383d0000, 0x383d2000, 0x383d4000, 0x383d6000, 0x383d8000, 0x383da000, 0x383dc000, 0x383de000,
   0x383e0000, 0x383e2000, 0x383e4000, 0x383e6000, 0x383e8000, 0x383ea000, 0x383ec000, 0x383ee000, 0x383f0000, 0x383f2000,
   0x383f4000, 0x383f6000, 0x383f8000, 0x383fa000, 0x383fc000, 0x383fe000, 0x38400000, 0x38402000, 0x38404000, 0x38406000,
   0x38408000, 0x3840a000, 0x3840c000, 0x3840e000, 0x38410000, 0x38412000, 0x38414000, 0x38416000, 0x38418000, 0x3841a000,
   0x3841c000, 0x3841e000, 0x38420000, 0x38422000, 0x38424000, 0x38426000, 0x38428000, 0x3842a000, 0x3842c000, 0x3842e000,
   0x38430000, 0x38432000, 0x38434000, 0x38436000, 0x38438000, 0x3843a000, 0x3843c000, 0x3843e000, 0x38440000, 0x38442000,
   0x38444000, 0x38446000, 0x38448000, 0x3844a000, 0x3844c000, 0x3844e000, 0x38450000, 0x38452000, 0x38454000, 0x38456000,
   0x38458000, 0x3845a000, 0x3845c000, 0x3845e000, 0x38460000, 0x38462000, 0x38464000, 0x38466000, 0x38468000, 0x3846a000,
   0x3846c000, 0x3846e000, 0x38470000, 0x38472000, 0x38474000, 0x38476000, 0x38478000, 0x3847a000, 0x3847c000, 0x3847e000,
   0x38480000, 0x38482000, 0x38484000, 0x38486000, 0x38488000, 0x3848a000, 0x3848c000, 0x3848e000, 0x38490000, 0x38492000,
   0x38494000, 0x38496000, 0x38498000, 0x3849a000, 0x3849c000, 0x3849e000, 0x384a0000, 0x384a2000, 0x384a4000, 0x384a6000,
   0x384a8000, 0x384aa000, 0x384ac000, 0x384ae000, 0x384b0000, 0x384b2000, 0x384b4000, 0x384b6000, 0x384b8000, 0x384ba000,
   0x384bc000, 0x384be000, 0x384c0000, 0x384c2000, 0x384c4000, 0x384c6000, 0x384c8000, 0x384ca000, 0x384cc000, 0x384ce000,
   0x384d0000, 0x384d2000, 0x384d4000, 0x384d6000, 0x384d8000, 0x384da000, 0x384dc000, 0x384de000, 0x384e0000, 0x384e2000,
   0x384e4000, 0x384e6000, 0x384e8000, 0x384ea000, 0x384ec000, 0x384ee000, 0x384f0000, 0x384f2000, 0x384f4000, 0x384f6000,
   0x384f8000, 0x384fa000, 0x384fc000, 0x384fe000, 0x38500000, 0x38502000, 0x38504000, 0x38506000, 0x38508000, 0x3850a000,
   0x3850c000, 0x3850e000, 0x38510000, 0x38512000, 0x38514000, 0x38516000, 0x38518000, 0x3851a000, 0x3851c000, 0x3851e000,
   0x38520000, 0x38522000, 0x38524000, 0x38526000, 0x38528000, 0x3852a000, 0x3852c000, 0x3852e000, 0x38530000, 0x38532000,
   0x38534000, 0x38536000, 0x38538000, 0x3853a000, 0x3853c000, 0x3853e000, 0x38540000, 0x38542000, 0x38544000, 0x38546000,
   0x38548000, 0x3854a000, 0x3854c000, 0x3854e000, 0x38550000, 0x38552000, 0x38554000, 0x38556000, 0x38558000, 0x3855a000,
   0x3855c000, 0x3855e000, 0x38560000, 0x38562000, 0x38564000, 0x38566000, 0x38568000, 0x3856a000, 0x3856c000, 0x3856e000,
   0x38570000, 0x38572000, 0x38574000, 0x38576000, 0x38578000, 0x3857a000, 0x3857c000, 0x3857e000, 0x38580000, 0x38582000,
   0x38584000, 0x38586000, 0x38588000, 0x3858a000, 0x3858c000, 0x3858e000, 0x38590000, 0x38592000, 0x38594000, 0x38596000,
   0x38598000, 0x3859a000, 0x3859c000, 0x3859e000, 0x385a0000, 0x385a2000, 0x385a4000, 0x385a6000, 0x385a8000, 0x385aa000,
   0x385ac000, 0x385ae000, 0x385b0000, 0x385b2000, 0x385b4000, 0x385b6000, 0x385b8000, 0x385ba000, 0x385bc000, 0x385be000,
   0x385c0000, 0x385c2000, 0x385c4000, 0x385c6000, 0x385c8000, 0x385ca000, 0x385cc000, 0x385ce000, 0x385d0000, 0x385d2000,
   0x385d4000, 0x385d6000, 0x385d8000, 0x385da000, 0x385dc000, 0x385de000, 0x385e0000, 0x385e2000, 0x385e4000, 0x385e6000,
   0x385e8000, 0x385ea000, 0x385ec000, 0x385ee000, 0x385f0000, 0x385f2000, 0x385f4000, 0x385f6000, 0x385f8000, 0x385fa000,
   0x385fc000, 0x385fe000, 0x38600000, 0x38602000, 0x38604000, 0x38606000, 0x38608000, 0x3860a000, 0x3860c000, 0x3860e000,
   0x38610000, 0x38612000, 0x38614000, 0x38616000, 0x38618000, 0x3861a000, 0x3861c000, 0x3861e000, 0x38620000, 0x38622000,
   0x38624000, 0x38626000, 0x38628000, 0x3862a000, 0x3862c000, 0x3862e000, 0x38630000, 0x38632000, 0x38634000, 0x38636000,
   0x38638000, 0x3863a000, 0x3863c000, 0x3863e000, 0x38640000, 0x38642000, 0x38644000, 0x38646000, 0x38648000, 0x3864a000,
   0x3864c000, 0x3864e000, 0x38650000, 0x38652000, 0x38654000, 0x38656000, 0x38658000, 0x3865a000, 0x3865c000, 0x3865e000,
   0x38660000, 0x38662000, 0x38664000, 0x38666000, 0x38668000, 0x3866a000, 0x3866c000, 0x3866e000, 0x38670000, 0x38672000,
   0x38674000, 0x38676000, 0x38678000, 0x3867a000, 0x3867c000, 0x3867e000, 0x38680000, 0x38682000, 0x38684000, 0x38686000,
   0x38688000, 0x3868a000, 0x3868c000, 0x3868e000, 0x38690000, 0x38692000, 0x38694000, 0x38696000, 0x38698000, 0x3869a000,
   0x3869c000, 0x3869e000, 0x386a0000, 0x386a2000, 0x386a4000, 0x386a6000, 0x386a8000, 0x386aa000, 0x386ac000, 0x386ae000,
   0x386b0000, 0x386b2000, 0x386b4000, 0x386b6000, 0x386b8000, 0x386ba000, 0x386bc000, 0x386be000, 0x386c0000, 0x386c2000,
   0x386c4000, 0x386c6000, 0x386c8000, 0x386ca000, 0x386cc000, 0x386ce000, 0x386d0000, 0x386d2000, 0x386d4000, 0x386d6000,
   0x386d8000, 0x386da000, 0x386dc000, 0x386de000, 0x386e0000, 0x386e2000, 0x386e4000, 0x386e6000, 0x386e8000, 0x386ea000,
   0x386ec000, 0x386ee000, 0x386f0000, 0x386f2000, 0x386f4000, 0x386f6000, 0x386f8000, 0x386fa000, 0x386fc000, 0x386fe000,
   0x38700000, 0x38702000, 0x38704000, 0x38706000, 0x38708000, 0x3870a000, 0x3870c000, 0x3870e000, 0x38710000, 0x38712000,
   0x38714000, 0x38716000, 0x38718000, 0x3871a000, 0x3871c000, 0x3871e000, 0x38720000, 0x38722000, 0x38724000, 0x38726000,
   0x38728000, 0x3872a000, 0x3872c000, 0x3872e000, 0x38730000, 0x38732000, 0x38734000, 0x38736000, 0x38738000, 0x3873a000,
   0x3873c000, 0x3873e000, 0x38740000, 0x38742000, 0x38744000, 0x38746000, 0x38748000, 0x3874a000, 0x3874c000, 0x3874e000,
   0x38750000, 0x38752000, 0x38754000, 0x38756000, 0x38758000, 0x3875a000, 0x3875c000, 0x3875e000, 0x38760000, 0x38762000,
   0x38764000, 0x38766000, 0x38768000, 0x3876a000, 0x3876c000, 0x3876e000, 0x38770000, 0x38772000, 0x38774000, 0x38776000,
   0x38778000, 0x3877a000, 0x3877c000, 0x3877e000, 0x38780000, 0x38782000, 0x38784000, 0x38786000, 0x38788000, 0x3878a000,
   0x3878c000, 0x3878e000, 0x38790000, 0x38792000, 0x38794000, 0x38796000, 0x38798000, 0x3879a000, 0x3879c000, 0x3879e000,
   0x387a0000, 0x387a2000, 0x387a4000, 0x387a6000, 0x387a8000, 0x387aa000, 0x387ac000, 0x387ae000, 0x387b0000, 0x387b2000,
   0x387b4000, 0x387b6000, 0x387b8000, 0x387ba000, 0x387bc000, 0x387be000, 0x387c0000, 0x387c2000, 0x387c4000, 0x387c6000,
   0x387c8000, 0x387ca000, 0x387cc000, 0x387ce000, 0x387d0000, 0x387d2000, 0x387d4000, 0x387d6000, 0x387d8000, 0x387da000,
   0x387dc000, 0x387de000, 0x387e0000, 0x387e2000, 0x387e4000, 0x387e6000, 0x387e8000, 0x387ea000, 0x387ec000, 0x387ee000,
   0x387f0000, 0x387f2000, 0x387f4000, 0x387f6000, 0x387f8000, 0x387fa000, 0x387fc000, 0x387fe000
};

const uint32_t HalfFloat::ExponentTable[64]=
{
   0x00000000, 0x00800000, 0x01000000, 0x01800000, 0x02000000, 0x02800000, 0x03000000, 0x03800000, 0x04000000, 0x04800000,
   0x05000000, 0x05800000, 0x06000000, 0x06800000, 0x07000000, 0x07800000, 0x08000000, 0x08800000, 0x09000000, 0x09800000,
   0x0a000000, 0x0a800000, 0x0b000000, 0x0b800000, 0x0c000000, 0x0c800000, 0x0d000000, 0x0d800000, 0x0e000000, 0x0e800000,
   0xff000000, 0x47800000, 0x80000000, 0x00800000, 0x01000000, 0x01800000, 0x02000000, 0x02800000, 0x03000000, 0x03800000,
   0x04000000, 0x04800000, 0x05000000, 0x05800000, 0x06000000, 0x06800000, 0x07000000, 0x07800000, 0x08000000, 0x08800000,
   0x09000000, 0x09800000, 0x0a000000, 0x0a800000, 0x0b000000, 0x0b800000, 0x0c000000, 0x0c800000, 0x0d000000, 0x0d800000,
   0x0e000000, 0x0e800000, 0x0f000000, 0xc7800000
};

const uint32_t HalfFloat::OffsetTable[64]=
{
   0x00000000, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000000, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400, 0x00000400,
   0x00000400, 0x00000400, 0x00000400, 0x00000400
};

//////////////////////////////////////////////////////////////////////////////

const uint16_t HalfFloat::BaseTable[512]=
{
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040,
   0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x0c00, 0x1000, 0x1400, 0x1800, 0x1c00,
   0x2000, 0x2400, 0x2800, 0x2c00, 0x3000, 0x3400, 0x3800, 0x3c00, 0x4000, 0x4400,
   0x4800, 0x4c00, 0x5000, 0x5400, 0x5800, 0x5c00, 0x6000, 0x6400, 0x6800, 0x6c00,
   0x7000, 0x7400, 0x7800, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00,
   0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x7c00, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
   0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8001,
   0x8002, 0x8004, 0x8008, 0x8010, 0x8020, 0x8040, 0x8080, 0x8100, 0x8200, 0x8400,
   0x8800, 0x8c00, 0x9000, 0x9400, 0x9800, 0x9c00, 0xa000, 0xa400, 0xa800, 0xac00,
   0xb000, 0xb400, 0xb800, 0xbc00, 0xc000, 0xc400, 0xc800, 0xcc00, 0xd000, 0xd400,
   0xd800, 0xdc00, 0xe000, 0xe400, 0xe800, 0xec00, 0xf000, 0xf400, 0xf800, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00, 0xfc00,
   0xfc00, 0xfc00
};

const uint16_t HalfFloat::ShiftTable[512]=
{
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0017, 0x0016, 0x0015, 0x0014, 0x0013, 0x0012, 0x0011,
   0x0010, 0x000f, 0x000e, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d,
   0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d,
   0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d,
   0x000d, 0x000d, 0x000d, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x000d, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0017,
   0x0016, 0x0015, 0x0014, 0x0013, 0x0012, 0x0011, 0x0010, 0x000f, 0x000e, 0x000d,
   0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d,
   0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d,
   0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x000d, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018,
   0x0018, 0x000d
};