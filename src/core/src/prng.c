#include "core/prng.h"

/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

/* 
  This is xoshiro256** 1.0, one of our all-purpose, rock-solid
  generators. It has excellent (sub-ns) speed, a state (256 bits) that is
  large enough for any parallel application, and it passes all tests we
  are aware of.

  For generating just floating-point numbers, xoshiro256+ is even faster.

  The state must be seeded so that it is not everywhere zero. If you have
  a 64-bit seed, we suggest to seed a splitmix64 generator and use its
  output to fill 'seed'. 
*/

static inline u64 rotl(u64 x, i32 k) {
  return (x << k) | (x >> (64 - k));
}


u64 xoshiro_seed[4] = {0};
u64 xoshiro256ss(void) {
  u64 result = rotl(xoshiro_seed[1] * 5, 7) * 9;

  u64 t = xoshiro_seed[1] << 17;

  xoshiro_seed[2] ^= xoshiro_seed[0];
  xoshiro_seed[3] ^= xoshiro_seed[1];
  xoshiro_seed[1] ^= xoshiro_seed[2];
  xoshiro_seed[0] ^= xoshiro_seed[3];

  xoshiro_seed[2] ^= t;

  xoshiro_seed[3] = rotl(xoshiro_seed[3], 45);

  return result;
}

/*  
  Written in 2015 by Sebastiano Vigna (vigna@acm.org)

  To the extent possible under law, the author has dedicated all copyright
  and related and neighboring rights to this software to the public domain
  worldwide. This software is distributed without any warranty.

  See <http://creativecommons.org/publicdomain/zero/1.0/>.


  This is a fixed-increment version of Java 8's SplittableRandom generator
  See http://dx.doi.org/10.1145/2714064.2660195 and 
  http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html

  It is a very fast generator passing BigCrush, and it can be useful if
  for some reason you absolutely want 64 bits of state.
*/

u64 splitmix64_seed = 0;
u64 splitmix64(void) {
  u64 z = (splitmix64_seed += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}
