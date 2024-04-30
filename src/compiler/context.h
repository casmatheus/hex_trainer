#pragma once

// Compiler
#ifdef __clang__
#define COMPILER_CLANG
#elif defined(_MSC_EXTENSIONS)
#define COMPILER_CL
#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER_GCC
#else 
#error "Compiler Not Supported"
#endif

// Warnings We Disable on the MSVC toolchain
#ifdef COMPILER_CL
// "Informational" Warning, It's not a REAL Warning
#pragma warning(disable : 5045)

// Padding Added Warning, Represents No Real Issue
#pragma warning(disable : 4820)

// Anonymous structs/unions were a C11 Feature
// No Reason to give a Warning over Them
#pragma warning(disable : 4201)

// Unrecheable Code Warning
// MSVC Wrongly gives this out all th time
#pragma warning(disable : 4201)
#endif  // COMPILER_CL

