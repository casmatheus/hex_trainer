#pragma once 

#include "core/nums.h"

extern u64 xoshiro_seed[4];
extern u64 splitmix64_seed;
u64 xoshiro256ss(void);
u64 splitmix64(void);
