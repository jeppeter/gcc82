/* { dg-do run } */
/* { dg-options "-O3 -mpower8-vector -Wno-psabi" } */
/* { dg-require-effective-target lp64 } */
/* { dg-require-effective-target p8vector_hw } */

#ifndef CHECK_H
#define CHECK_H "sse2-check.h"
#endif

#include CHECK_H

#ifndef TEST
#define TEST sse2_test_punpckhqdq_1
#endif

#include <emmintrin.h>

static __m128i
__attribute__((noinline, unused))
test (__m128i s1, __m128i s2)
{
  __asm("" : "+v"(s1), "+v"(s2));
  return _mm_unpackhi_epi64 (s1, s2); 
}

static void
TEST (void)
{
  union128i_q u, s1, s2;
  long long  e[2];
   
  s1.x = _mm_set_epi64x (10,-40);
  s2.x = _mm_set_epi64x (1134, -7839);
  u.x = test (s1.x, s2.x); 
  
  e[0] = s1.a[1];
  e[1] = s2.a[1];

  if (check_union128i_q (u, e))
    abort ();
}