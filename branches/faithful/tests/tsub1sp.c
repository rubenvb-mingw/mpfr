/* Test file for mpfr_sub1sp.

Copyright 2003-2017 Free Software Foundation, Inc.
Contributed by the AriC and Caramba projects, INRIA.

This file is part of the GNU MPFR Library.

The GNU MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LESSER.  If not, see
http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */

#include "mpfr-test.h"

static void check_special (void);
static void check_random (mpfr_prec_t p);
static void check_underflow (mpfr_prec_t p);
static void check_corner (mpfr_prec_t p);

static void
bug20170109 (void)
{
  mpfr_t a, b, c;

  mpfr_init2 (a, 111);
  mpfr_init2 (b, 111);
  mpfr_init2 (c, 111);
  mpfr_set_str_binary (b, "0.110010010000111111011010101000100010000101101000110000100011010011000100110001100110001010001011100000001101110E1");
  mpfr_set_str_binary (c, "0.111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111E-63");
  mpfr_sub (a, b, c, MPFR_RNDN);
  mpfr_set_str_binary (b, "0.110010010000111111011010101000100010000101101000110000100011001111000100110001100110001010001011100000001101110E1");
  MPFR_ASSERTN(mpfr_equal_p (a, b));
  mpfr_clear (a);
  mpfr_clear (b);
  mpfr_clear (c);
}

int
main (void)
{
  mpfr_prec_t p;

  tests_start_mpfr ();

  bug20170109 ();
  check_special ();
  for (p = MPFR_PREC_MIN ; p < 200 ; p++)
    {
      check_underflow (p);
      check_random (p);
      check_corner (p);
    }

  tests_end_mpfr ();
  return 0;
}

#define STD_ERROR                                                       \
  do                                                                    \
    {                                                                   \
      printf("ERROR: for %s and p=%lu and i=%d:\nY=",                   \
             mpfr_print_rnd_mode ((mpfr_rnd_t) r), (unsigned long) p, i); \
      mpfr_dump (y);                                                    \
      printf ("Z="); mpfr_dump (z);                                     \
      printf ("Real: "); mpfr_dump (x2);                                \
      printf ("Got : "); mpfr_dump (x);                                 \
      abort();                                                          \
    }                                                                   \
 while (0)

#define STD_ERROR2                                                      \
  do                                                                    \
    {                                                                   \
      printf("ERROR: for %s and p=%lu and i=%d:\nY=",                   \
             mpfr_print_rnd_mode ((mpfr_rnd_t) r), (unsigned long) p, i); \
      mpfr_dump (y);                                                    \
      printf ("Z="); mpfr_dump (z);                                     \
      printf ("R="); mpfr_dump (x);                                     \
      printf ("Wrong inexact flag. Real: %d. Got: %d\n",                \
              inexact1, inexact2);                                      \
      exit(1);                                                          \
    }                                                                   \
 while (0)

static void
check_random (mpfr_prec_t p)
{
  mpfr_t x,y,z,x2;
  int r;
  int i, inexact1, inexact2;

  mpfr_inits2 (p, x, y, z, x2, (mpfr_ptr) 0);

  for (i = 0 ; i < 500 ; i++)
    {
      mpfr_urandomb (y, RANDS);
      mpfr_urandomb (z, RANDS);
      if (MPFR_IS_PURE_FP(y) && MPFR_IS_PURE_FP(z))
        for(r = 0 ; r < MPFR_RND_MAX ; r++)
          {
            if (r == MPFR_RNDF)
              continue; /* mpfr_sub1 and mpfr_sub1sp could differ,
                           and inexact makes no sense */
            inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
            inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
            if (mpfr_cmp(x, x2))
              STD_ERROR;
            if (inexact1 != inexact2)
              STD_ERROR2;
          }
    }

  mpfr_clears (x, y, z, x2, (mpfr_ptr) 0);
}

static void
check_special (void)
{
  mpfr_t x,y,z,x2;
  int r;
  mpfr_prec_t p;
  int i = -1, inexact1, inexact2;
  mpfr_exp_t es;

  mpfr_inits (x, y, z, x2, (mpfr_ptr) 0);

  for (r = 0 ; r < MPFR_RND_MAX ; r++)
    {
      if (r == MPFR_RNDF)
        continue; /* comparison between sub1 and sub1sp makes no sense here */

      p = 53;
      mpfr_set_prec(x, 53);
      mpfr_set_prec(x2, 53);
      mpfr_set_prec(y, 53);
      mpfr_set_prec(z, 53);

      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011000001101101011011001E31");

      mpfr_sub1sp (x, y, y, (mpfr_rnd_t) r);
      if (mpfr_cmp_ui(x, 0))
        {
          printf("Error for x-x with p=%lu. Expected 0. Got:",
                 (unsigned long) p);
          mpfr_dump (x);
          exit(1);
        }

      mpfr_set(z, y, (mpfr_rnd_t) r);
      mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp_ui(x, 0))
        {
          printf("Error for x-y with y=x and p=%lu. Expected 0. Got:",
                 (unsigned long) p);
          mpfr_dump (x);
          exit(1);
        }
      /* diff = 0 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011001001101101011011001E31");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff = 1 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011000001101101011011001E30");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff = 2 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011000101101101011011001E32");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff = 32 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011000001101101011011001E63");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff = 52 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011010001101101011011001E83");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff = 53 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011111000001101101011011001E31");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      /* Diff > 200 */
      mpfr_set_str_binary (y,
       "0.10110111101101110010010010011011000001101101011011001E331");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
       "0.10000000000000000000000000000000000000000000000000000E31");
      mpfr_set_str_binary (z,
       "0.11111111111111111111111111111111111111111111111111111E30");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
       "0.10000000000000000000000000000000000000000000000000000E31");
      mpfr_set_str_binary (z,
       "0.11111111111111111111111111111111111111111111111111111E29");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
       "0.10000000000000000000000000000000000000000000000000000E52");
      mpfr_set_str_binary (z,
       "0.10000000000010000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
        "0.11100000000000000000000000000000000000000000000000000E53");
      mpfr_set_str_binary (z,
        "0.10000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(z, y, z, (mpfr_rnd_t) r);
      mpfr_set(x, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
       "0.10000000000000000000000000000000000000000000000000000E53");
      mpfr_set_str_binary (z,
       "0.10100000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
        "0.10000000000000000000000000000000000000000000000000000E54");
      mpfr_set_str_binary (z,
        "0.10100000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 63;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);
      mpfr_set_str_binary (y,
      "0.100000000000000000000000000000000000000000000000000000000000000E62");
      mpfr_set_str_binary (z,
      "0.110000000000000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 64;
      mpfr_set_prec(x, 64);
      mpfr_set_prec(x2, 64);
      mpfr_set_prec(y, 64);
      mpfr_set_prec(z, 64);

      mpfr_set_str_binary (y,
      "0.1100000000000000000000000000000000000000000000000000000000000000E31");
      mpfr_set_str_binary (z,
      "0.1111111111111111111111111110000000000000000000000000011111111111E29");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
      "0.1000000000000000000000000000000000000000000000000000000000000000E63");
      mpfr_set_str_binary (z,
      "0.1011000000000000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
      "0.1000000000000000000000000000000000000000000000000000000000000000E63");
      mpfr_set_str_binary (z,
      "0.1110000000000000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
        "0.10000000000000000000000000000000000000000000000000000000000000E63");
      mpfr_set_str_binary (z,
        "0.10000000000000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
      "0.1000000000000000000000000000000000000000000000000000000000000000E64");
      mpfr_set_str_binary (z,
      "0.1010000000000000000000000000000000000000000000000000000000000000E00");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      MPFR_SET_NAN(x);
      MPFR_SET_NAN(x2);
      mpfr_set_str_binary (y,
      "0.1000000000000000000000000000000000000000000000000000000000000000"
                          "E-1073741823");
      mpfr_set_str_binary (z,
      "0.1100000000000000000000000000000000000000000000000000000000000000"
                          "E-1073741823");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 9;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);

      mpfr_set_str_binary (y, "0.100000000E1");
      mpfr_set_str_binary (z, "0.100000000E-8");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 34;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);

      mpfr_set_str_binary (y, "-0.1011110000111100010111011100110100E-18");
      mpfr_set_str_binary (z, "0.1000101010110011010101011110000000E-14");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 124;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);

      mpfr_set_str_binary (y,
"0.1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000E1");
      mpfr_set_str_binary (z,
"0.1011111000100111000011001000011101010101101100101010101001000001110100001101110110001110111010000011101001100010111110001100E-31");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 288;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);

      mpfr_set_str_binary (y,
     "0.111000110011000001000111101010111011110011101001101111111110000011100101000001001010110010101010011001010100000001110011110001010101101010001011101110100100001011110100110000101101100011010001001011011010101010000010001101001000110010010111111011110001111101001000101101001100101100101000E80");
      mpfr_set_str_binary (z,
     "-0.100001111111101001011010001100110010100111001110000110011101001011010100001000000100111011010110110010000000000010101101011000010000110001110010100001100101011100100100001011000100011110000001010101000100011101001000010111100000111000111011001000100100011000100000010010111000000100100111E-258");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 85;
      mpfr_set_prec(x, p);
      mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p);
      mpfr_set_prec(z, p);

      mpfr_set_str_binary (y,
"0.1111101110100110110110100010101011101001100010100011110110110010010011101100101111100E-4");
      mpfr_set_str_binary (z,
"0.1111101110100110110110100010101001001000011000111000011101100101110100001110101010110E-4");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      p = 64;
      mpfr_set_prec(x, p); mpfr_set_prec(x2, p);
      mpfr_set_prec(y, p); mpfr_set_prec(z, p);

      mpfr_set_str_binary (y,
                          "0.11000000000000000000000000000000"
                          "00000000000000000000000000000000E1");
      mpfr_set_str_binary (z,
                          "0.10000000000000000000000000000000"
                          "00000000000000000000000000000001E0");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
                          "0.11000000000000000000000000000000"
                          "000000000000000000000000000001E1");
      mpfr_set_str_binary (z,
                          "0.10000000000000000000000000000000"
                          "00000000000000000000000000000001E0");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      es = mpfr_get_emin ();
      set_emin (-1024);

      mpfr_set_str_binary (y,
                          "0.10000000000000000000000000000000"
                          "000000000000000000000000000000E-1023");
      mpfr_set_str_binary (z,
                          "0.10000000000000000000000000000000"
                          "00000000000000000000000000000001E-1023");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      mpfr_set_str_binary (y,
                           "0.10000000000000000000000000000000"
                           "000000000000000000000000000000E-1023");
      mpfr_set_str_binary (z,
                           "0.1000000000000000000000000000000"
                           "000000000000000000000000000000E-1023");
      inexact1 = mpfr_sub1(x2, y, z, (mpfr_rnd_t) r);
      inexact2 = mpfr_sub1sp(x, y, z, (mpfr_rnd_t) r);
      if (mpfr_cmp(x, x2))
        STD_ERROR;
      if (inexact1 != inexact2)
        STD_ERROR2;

      set_emin (es);
    }

  mpfr_clears (x, y, z, x2, (mpfr_ptr) 0);
}

static void
check_underflow (mpfr_prec_t p)
{
  mpfr_t x, y, z;
  int inexact;

  mpfr_inits2 (p, x, y, z, (mpfr_ptr) 0);

  if (p >= 2) /* we need p >= 2 so that 3 is exact */
    {
      mpfr_set_ui_2exp (y, 4, mpfr_get_emin () - 2, MPFR_RNDN);
      mpfr_set_ui_2exp (z, 3, mpfr_get_emin () - 2, MPFR_RNDN);
      inexact = mpfr_sub (x, y, z, MPFR_RNDN);
      if (inexact >= 0 || (mpfr_cmp_ui (x, 0) != 0))
        {
          printf ("4*2^(emin-2) - 3*2^(emin-2) with RNDN failed for p=%lu\n",
                  p);
          printf ("Expected inexact < 0 with x=0\n");
          printf ("Got inexact=%d with x=", inexact);
          mpfr_dump (x);
          exit (1);
        }
    }

  if (p >= 3) /* we need p >= 3 so that 5 is exact */
    {
      mpfr_set_ui_2exp (y, 5, mpfr_get_emin () - 2, MPFR_RNDN);
      mpfr_set_ui_2exp (z, 4, mpfr_get_emin () - 2, MPFR_RNDN);
      inexact = mpfr_sub (x, y, z, MPFR_RNDN);
      if (inexact >= 0 || (mpfr_cmp_ui (x, 0) != 0))
        {
          printf ("5*2^(emin-2) - 4*2^(emin-2) with RNDN failed for p=%lu\n",
                  p);
          printf ("Expected inexact < 0 with x=0\n");
          printf ("Got inexact=%d with x=", inexact);
          mpfr_dump (x);
          exit (1);
        }
    }

  mpfr_clears (x, y, z, (mpfr_ptr) 0);
}

/* check corner cases of mpfr_sub1sp in case d = 1 and limb = MPFR_LIMB_HIGHBIT */
static void
check_corner (mpfr_prec_t p)
{
  mpfr_t x, y, z;
  mpfr_exp_t e;
  int inex, odd;

  if (p < 4) /* ensures that the initial value of z is > 1 below */
    return;

  mpfr_inits2 (p, x, y, z, (mpfr_ptr) 0);
  mpfr_const_pi (y, MPFR_RNDN);
  mpfr_set_ui (z, 2, MPFR_RNDN);
  inex = mpfr_sub (z, y, z, MPFR_RNDN); /* z is near pi-2, thus y-z is near 2 */
  MPFR_ASSERTN(inex == 0);
  for (e = 0; e < p; e++)
    {
      /* add 2^(-e) to z */
      mpfr_mul_2exp (z, z, e, MPFR_RNDN);
      inex = mpfr_add_ui (z, z, 1, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      mpfr_div_2exp (z, z, e, MPFR_RNDN);

      /* compute x = y - z which should be exact, near 2-2^(-e) */
      inex = mpfr_sub (x, y, z, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      MPFR_ASSERTN(mpfr_get_exp (x) == 1);

      /* restore initial z */
      mpfr_mul_2exp (z, z, e, MPFR_RNDN);
      inex = mpfr_sub_ui (z, z, 1, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      mpfr_div_2exp (z, z, e, MPFR_RNDN);

      /* subtract 2^(-e) to z */
      mpfr_mul_2exp (z, z, e, MPFR_RNDN);
      inex = mpfr_sub_ui (z, z, 1, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      mpfr_div_2exp (z, z, e, MPFR_RNDN);

      /* ensure last significant bit of z is 0 so that y-z is exact */
      odd = mpfr_min_prec (z) == p;
      if (odd) /* add one ulp to z */
        mpfr_nextabove (z);

      /* compute x = y - z which should be exact, near 2+2^(-e) */
      inex = mpfr_sub (x, y, z, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      MPFR_ASSERTN(mpfr_get_exp (x) == 2);

      /* restore initial z */
      if (odd)
        mpfr_nextbelow (z);
      mpfr_mul_2exp (z, z, e, MPFR_RNDN);
      inex = mpfr_add_ui (z, z, 1, MPFR_RNDN);
      MPFR_ASSERTN(inex == 0);
      mpfr_div_2exp (z, z, e, MPFR_RNDN);
    }
  mpfr_clears (x, y, z, (mpfr_ptr) 0);
}