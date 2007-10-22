/* Test file for mpfr_subnormalize.

Copyright 2005, 2006, 2007 Free Software Foundation, Inc.
Contributed by the Arenaire and Cacao projects, INRIA.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include <stdio.h>
#include <stdlib.h>

#include "mpfr-test.h"

static const struct {
  const char *in;
  int i;
  mp_rnd_t rnd;
  const char *out;
} tab[] ={
  {"1E1",  0, GMP_RNDN, "1E1"},
  {"1E1", -1, GMP_RNDZ, "1E1"},
  {"1E1", -1, GMP_RNDD, "1E1"},
  {"1E1",  1, GMP_RNDU, "1E1"},
  {"0.10000E-10", 0, GMP_RNDN, "0.1E-10"},
  {"0.10001E-10", 0, GMP_RNDN, "0.1E-10"},
  {"0.11001E-10", 0, GMP_RNDN, "0.1E-9"},
  {"0.11001E-10", 0, GMP_RNDZ, "0.1E-10"},
  {"0.11001E-10", 0, GMP_RNDU, "0.1E-9"},
  {"0.11000E-10", 0, GMP_RNDN, "0.1E-9"},
  {"0.11111E-8", 0, GMP_RNDN, "0.10E-7"},
  {"0.10111E-8", 0, GMP_RNDN, "0.11E-8"},
  {"0.11110E-8", -1, GMP_RNDN, "0.10E-7"},
  {"0.10110E-8", 1, GMP_RNDN, "0.101E-8"}
};

static void
check1 (void)
{
  mpfr_t x;
  int i, j;

  mpfr_set_default_prec (9);
  mpfr_set_emin (-10);
  mpfr_set_emax (10);

  mpfr_init (x);
  for (i = 0; i < (sizeof (tab) / sizeof (tab[0])); i++)
    {
      mpfr_set_str (x, tab[i].in, 2, GMP_RNDN);
      j = mpfr_subnormalize (x, tab[i].i, tab[i].rnd);
      if (mpfr_cmp_str (x, tab[i].out, 2, GMP_RNDN) != 0)
        {
          printf ("Error for i=%d\nFor:%s\nExpected:%s\nGot:",
                  i, tab[i].in, tab[i].out);
          mpfr_dump (x);
          exit (1);
        }
    }
  mpfr_clear (x);
}

/* bug found by Kevin P. Rauch on 22 Oct 2007 */
static void
check2 (void)
{
  mpfr_t x, y, z;
  int tern;

  mpfr_init2 (x, 32);
  mpfr_init2 (y, 32);
  mpfr_init2 (z, 32);

  mpfr_set_ui (x, 0xC0000000U, GMP_RNDN);
  mpfr_neg (x, x, GMP_RNDN);
  mpfr_set_ui (y, 0xFFFFFFFEU, GMP_RNDN);
  mpfr_set_exp (x, 0);
  mpfr_set_exp (y, 0);
  mpfr_set_emin (-29);

  tern = mpfr_mul (z, x, y, GMP_RNDN);
  /* z = -0.BFFFFFFE, tern > 0 */

  tern = mpfr_subnormalize (z, tern, GMP_RNDN);
  /* z should be -0.75 */
  MPFR_ASSERTN (tern < 0 && mpfr_cmp_si_2exp (z, -3, -2) == 0);

  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (z);
}

/* bug found by Kevin P. Rauch on 22 Oct 2007 */
static void
check3 (void)
{
  mpfr_t x, y, z;
  int tern;

  mpfr_init2 (x, 32);
  mpfr_init2 (y, 32);
  mpfr_init2 (z, 32);

  mpfr_set_ui (x, 0xBFFFFFFFU, GMP_RNDN); /* 3221225471/2^32 */
  mpfr_set_ui (y, 0x80000001U, GMP_RNDN); /* 2147483649/2^32 */
  mpfr_set_exp (x, 0);
  mpfr_set_exp (y, 0);
  mpfr_set_emin (-1);

  /* the exact product is 6917529028714823679/2^64, which is rounded to
     3/8 = 0.375, which is smaller, thus tern < 0 */
  tern = mpfr_mul (z, x, y, GMP_RNDN);
  MPFR_ASSERTN (tern < 0 && mpfr_cmp_ui_2exp (z, 3, -3) == 0);

  tern = mpfr_subnormalize (z, tern, GMP_RNDN);
  /* since emin = -1, and EXP(z)=-1, z should be rounded to precision
     EXP(z)-emin+1 = 1, i.e., z should be a multiple of the smallest possible
     positive representable value with emin=-1, which is 1/4. The two
     possible values are 1/4 and 2/4, which are at equal distance of z.
     But since tern < 0, we should choose the largest value, i.e., 2/4. */
  MPFR_ASSERTN (tern > 0 && mpfr_cmp_ui_2exp (z, 1, -1) == 0);

  /* here is another test for the alternate case, where z was rounded up
     first, thus we have to round down */
  mpfr_set_str_binary (x, "0.11111111111010110101011011011011");
  mpfr_set_str_binary (y, "0.01100000000001111100000000001110");
  tern = mpfr_mul (z, x, y, GMP_RNDN);
  MPFR_ASSERTN (tern > 0 && mpfr_cmp_ui_2exp (z, 3, -3) == 0);
  tern = mpfr_subnormalize (z, tern, GMP_RNDN);
  MPFR_ASSERTN (tern < 0 && mpfr_cmp_ui_2exp (z, 1, -2) == 0);

  /* finally the case where z was exact, which we simulate here */
  mpfr_set_ui_2exp (z, 3, -3, GMP_RNDN);
  tern = mpfr_subnormalize (z, 0, GMP_RNDN);
  MPFR_ASSERTN (tern > 0 && mpfr_cmp_ui_2exp (z, 1, -1) == 0);

  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (z);
}

int
main (int argc, char *argv[])
{
  tests_start_mpfr ();

  check1 ();
  check2 ();
  check3 ();

  tests_end_mpfr ();
  return 0;
}
