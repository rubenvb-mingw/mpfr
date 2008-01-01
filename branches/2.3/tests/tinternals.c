/* tinternals -- Test for internals.

Copyright 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
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

#define MPFR_NEED_LONGLONG_H
#include "mpfr-test.h"

static void
test_int_ceil_log2 (void)
{
  int i;
  int val[16] = { 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4 };

  for (i = 1; i < 17; i++)
    {
      MPFR_ASSERTN (MPFR_INT_CEIL_LOG2 (i) == val[i-1]);
      MPFR_ASSERTN (MPFR_INT_CEIL_LOG2 (i) == __gmpfr_int_ceil_log2 (i));
    }
}

static void
test_round_near_x (void)
{
  mpfr_t x, y, z, eps;
  mp_exp_t e;
  int failures = 0, mx, neg, err, dir, r, inex, inex2;
  char buffer[7], *p;

  mpfr_inits (x, y, z, eps, (void *) 0);
  mpfr_set_prec (x, 5);
  mpfr_set_prec (y, 3);
  mpfr_set_prec (z, 3);
  mpfr_set_prec (eps, 2);
  mpfr_set_ui_2exp (eps, 1, -32, GMP_RNDN);

  for (mx = 16; mx < 32; mx++)
    {
      mpfr_set_ui_2exp (x, mx, -2, GMP_RNDN);
      for (p = buffer, neg = 0;
           neg <= 1;
           mpfr_neg (x, x, GMP_RNDN), p++, neg++)
        for (err = 2; err <= 6; err++)
          for (dir = 0; dir <= 1; dir++)
            for (r = 0; r < GMP_RND_MAX; r++)
              {
                inex = mpfr_round_near_x (y, x, err, dir, r);

                if (inex == 0 && err < 6)
                  {
                    /* The test is more restrictive than necessary.
                       So, no failure in this case. */
                    continue;
                  }

                inex2 = ((dir ^ neg) ? mpfr_add : mpfr_sub) (z, x, eps, r);
                if (inex * inex2 <= 0)
                  printf ("Bad return value (%d instead of %d) for:\n",
                          inex, inex2);
                else if (mpfr_equal_p (y, z))
                  continue;  /* correct inex and y */
                else
                  {
                    printf ("Bad MPFR value (should have got ");
                    mpfr_out_str (stdout, 2, 3, z, GMP_RNDZ);
                    printf (") for:\n");
                  }

                if (!mpfr_get_str (buffer, &e, 2, 5, x, GMP_RNDZ) || e != 3)
                  {
                    printf ("mpfr_get_str failed in test_round_near_x\n");
                    exit (1);
                  }
                printf ("x = %c%c%c%c.%c%c, ", neg ? '-' : '+',
                        p[0], p[1], p[2], p[3], p[4]);
                printf ("err = %d, dir = %d, r = %s --> inex = %2d",
                        err, dir, mpfr_print_rnd_mode (r), inex);
                if (inex != 0)
                  {
                    printf (", y = ");
                    mpfr_out_str (stdout, 2, 3, y, GMP_RNDZ);
                  }
                printf ("\n");
                if (inex == 0)
                  printf ("Rounding was possible!\n");
                if (++failures == 10)  /* show at most 10 failures */
                  exit (1);
              }
    }

  if (failures)
    exit (1);

  mpfr_clears (x, y, z, eps, (void *) 0);
}

int
main (int argc, char **argv)
{
  tests_start_mpfr ();

  /* The tested function and macro exist in MPFR 2.2.0, but with a
     different (incorrect, but with no effect in 2.2.0) behavior. */
#if MPFR_VERSION >= MPFR_VERSION_NUM(2,3,0)
  test_int_ceil_log2 ();
#endif

  test_round_near_x ();

  tests_end_mpfr ();
  return 0;
}
