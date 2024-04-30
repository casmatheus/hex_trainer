#pragma once

#include "compiler/static_assert.h"

//clang-format off

// Standard Types
typedef signed char         i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long long   i64;

typedef unsigned char       u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef i32 bool32;
typedef i8 bool8;

typedef float  f32;
typedef double f64;


// Numeric Limit Definitions
#define i8_MAX  ((i8)   127)
#define i8_MIN  ((i8)  -i8_MAX - 1)

#define i16_MAX ((i16)  32767)
#define i16_MIN ((i16) -i16_MAX - 1)

#define i32_MAX ((i32)  2147483647)
#define i32_MIN ((i32) -i32_MAX - 1)

#define i64_MAX ((i64)  9223372036854775807ll)
#define i64_MIN ((i64) -i64_MAX - 1)

#define u8_MAX  ((u8) 255u)
#define u8_MIN  ((u8) 0u)

#define u16_MAX ((u16) 65535u)
#define u16_MIN ((u16) 0u)

#define u32_MAX ((u32) 4294967295u)
#define u32_MIN ((u32) 0u)

#define u64_MAX ((u64) 18446744073709551615llu)
#define u64_MIN ((u64) 0llu)

// Static Asserts For Type Sizes
StaticAssert(sizeof(i8)  == 1, "sizeof(i8) Must be 1 Byte"  );
StaticAssert(sizeof(i16) == 2, "sizeof(i16) Must be 2 Bytes");
StaticAssert(sizeof(i32) == 4, "sizeof(i32) Must be 4 Bytes");
StaticAssert(sizeof(i64) == 8, "sizeof(i64) Must be 8 Bytes");

StaticAssert(sizeof(u8)  == 1, "sizeof(u8) Must be 1 Byte"  );
StaticAssert(sizeof(u16) == 2, "sizeof(u16) Must be 2 Bytes");
StaticAssert(sizeof(u32) == 4, "sizeof(u32) Must be 4 Bytes");
StaticAssert(sizeof(u64) == 8, "sizeof(u64) Must be 8 Bytes");

StaticAssert(sizeof(f32) == 4, "sizeof(f32) Must be 4 Bytes");
StaticAssert(sizeof(f64) == 8, "sizeof(f64) Must be 8 Bytes");

//clang-format on
