/* Test file for the beta function

Copyright 2017 Free Software Foundation, Inc.
Contributed by ChemicalDevelopment.

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

/* TODO: Test the ternary value and the flags. Add tgeneric tests. */

/* FIXME: do not use mpfr_printf in the tests. */
#define FAILED(p, r, z, w, expected, rnd_mode) do {                     \
    mpfr_printf ("prec=%d, rnd=%s case failed for z=%Rf, w=%Rf."        \
                 " Got %Rb, expected %Rb\n", p,                         \
                 mpfr_print_rnd_mode (rnd_mode), z, w, r, expected);    \
    exit(1);                                                            \
  } while (0)

#define TEST(p, r, z, w, expected) TESTRND(p, r, z, w, expected, MPFR_RNDN)

#define TESTRND(p, r, z, w, expected, rnd_mode) do {                    \
    mpfr_beta (r, z, w, rnd_mode);                                      \
    if (not_same (r, expected))                                         \
      FAILED(p, r, z, w, expected, rnd_mode);                           \
  } while (0)

static int
not_same (mpfr_t a, mpfr_t b)
{
  int res = 0;

  if (mpfr_cmp(a, b) != 0)
    res = 1;
  if (! mpfr_nan_p(a) != ! mpfr_nan_p(b))
    res = 1;
  return res;
}

static void
test_beta_special (mp_prec_t prec)
{
  mpfr_t z, w, r, expect;

  mpfr_init2 (r, prec);
  mpfr_init2 (z, prec);
  mpfr_init2 (w, prec);
  mpfr_init2 (expect, prec);

  mpfr_set_inf (z, 1);
  mpfr_set_inf (w, 1);
  mpfr_set_zero (expect, 1);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_zero (w, 1);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_zero (w, -1);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_str (w, "-.1e0", 2, MPFR_RNDN);
  mpfr_set_inf (expect, 1);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_str (w, "-1.1e0", 2, MPFR_RNDN);
  mpfr_set_inf (expect, -1);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_str (w, "-1e0", 2, MPFR_RNDN);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, 1);
  mpfr_set_str (w, "-2e0", 2, MPFR_RNDN);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  if (prec > 81)
    {
      mpfr_set_inf (z, 1);
      mpfr_set_str (w, "-1e80", 2, MPFR_RNDN);
      mpfr_set_nan (expect);
      TEST(prec, r, z, w, expect);

      mpfr_set_inf (z, 1);
      mpfr_set_str (w, "-1e80", 2, MPFR_RNDN);
      mpfr_sub_d (w, w, .1, MPFR_RNDN);
      mpfr_set_inf (expect, 1);
      TEST(prec, r, z, w, expect);

      mpfr_set_str (w, "-1e80", 2, MPFR_RNDN);
      mpfr_sub_d (w, w, 1.1, MPFR_RNDN);
      mpfr_set_inf (expect, -1);
      TEST(prec, r, z, w, expect);
    }

  mpfr_set_str (z, "1.1e0", 2, MPFR_RNDN);
  mpfr_set_inf (w, -1);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  mpfr_set_str (z, "11e0", 2, MPFR_RNDN);
  mpfr_set_inf (w, -1);
  mpfr_set_zero (expect, -1);
  TEST(prec, r, z, w, expect);

  mpfr_set_str (z, "10e0", 2, MPFR_RNDN);
  mpfr_set_inf (w, -1);
  mpfr_set_zero (expect, -1);
  TEST(prec, r, z, w, expect);

  mpfr_set_inf (z, -1);
  mpfr_set_inf (w, -1);
  mpfr_set_nan (expect);
  TEST(prec, r, z, w, expect);

  mpfr_clear (r);
  mpfr_clear (z);
  mpfr_clear (w);
  mpfr_clear (expect);
}

static void
test_beta_2exp (mp_prec_t prec, int trials, int spread)
{
  mpfr_t r, z, w, expect;
  int i;

  mpfr_init2 (r, prec);
  mpfr_init2 (z, prec);
  mpfr_init2 (w, prec);
  mpfr_init2 (expect, prec);
  for (i = -(spread*trials)/2; spread*i < trials / 2; i += spread)
    {
      mpfr_set_si_2exp (z, 1, i, MPFR_RNDN);
      mpfr_set_ui (w, 1, MPFR_RNDN);
      mpfr_set_si_2exp (expect, 1, -i, MPFR_RNDN);

      TEST(prec, r, z, w, expect);
    }

  mpfr_clear (r);
  mpfr_clear (z);
  mpfr_clear (w);
  mpfr_clear (expect);
}

static void
test_beta_hardcoded (mp_prec_t prec)
{
  mpfr_t r, z, w, expect;
  mp_prec_t oprec = 1;

  if (prec < 10)
    prec = 10;
  mpfr_init2 (z, prec);
  mpfr_init2 (w, prec);
  mpfr_init2 (r, oprec);
  mpfr_init2 (expect, oprec);

  mpfr_set_ui (z, 3, MPFR_RNDN);
  mpfr_set_ui (w, 3, MPFR_RNDN);
  mpfr_set_str (expect, "1e-5", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDN);

  mpfr_set_str (expect, "1.1e-5", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDU);

  mpfr_set_str (expect, "1e-5", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDD);

  mpfr_set_ui (z, 5, MPFR_RNDN);
  mpfr_set_ui (w, 27, MPFR_RNDN);
  mpfr_set_str (expect, "1e-20", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDN);

  mpfr_set_str (expect, "1e-19", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDU);

  mpfr_set_ui (z, 5, MPFR_RNDN);
  mpfr_set_ui (w, 27, MPFR_RNDN);
  mpfr_set_str (expect, "1e-20", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDN);


  mpfr_set_ui (z, 121, MPFR_RNDN);
  mpfr_set_ui (w, 2, MPFR_RNDN);
  mpfr_set_str (expect, "1e-14", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDN);

  mpfr_set_ui (z, 121, MPFR_RNDN);
  mpfr_set_ui (w, 151, MPFR_RNDN);
  mpfr_set_str (expect, "1e-271", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDN);

  mpfr_set_str (expect, "1e-272", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDD);

  mpfr_set_str (expect, "1e-271", 2, MPFR_RNDN);
  TESTRND(prec, r, z, w, expect, MPFR_RNDU);

  mpfr_clear (r);
  mpfr_clear (z);
  mpfr_clear (w);
  mpfr_clear (expect);
}

/* makes sure beta(a, b) = beta(b, a) */
static void
test_beta_refl (mp_prec_t prec, mp_rnd_t rnd_mode)
{
  mpfr_t r, z, w, expect;

  mpfr_init2 (z, prec);
  mpfr_init2 (w, prec);
  mpfr_init2 (r, prec);
  mpfr_init2 (expect, prec);

  mpfr_set_ui (z, 3, MPFR_RNDN);
  mpfr_set_ui (w, 3, MPFR_RNDN);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);

  mpfr_set_ui (z, 5, MPFR_RNDN);
  mpfr_set_ui (w, 100, MPFR_RNDN);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);

  mpfr_set_nan (z);
  mpfr_set_ui (w, 100, MPFR_RNDN);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);

  mpfr_set_nan (z);
  mpfr_set_ui (w, 1, MPFR_RNDN);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);

  mpfr_set_nan (z);
  mpfr_set_nan (w);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);
  mpfr_set_nan (z);
  mpfr_set_nan (w);
  mpfr_beta (expect, w, z, rnd_mode);
  TESTRND(prec, r, z, w, expect, rnd_mode);

  mpfr_clear (r);
  mpfr_clear (z);
  mpfr_clear (w);
  mpfr_clear (expect);
}

int
main ()
{
  test_beta_special (10);
  test_beta_special (100);
  test_beta_special (1000);

  test_beta_2exp (1, 10, 1);
  test_beta_2exp (100, 40, 3);

  test_beta_hardcoded (10);
  test_beta_hardcoded (100);

  test_beta_refl (1, MPFR_RNDN);
  test_beta_refl (100, MPFR_RNDD);

  return 0;
}
