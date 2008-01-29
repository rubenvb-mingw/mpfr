/* mpfr_swap (U, V) -- Swap U and V.

Copyright 2000, 2001, 2002, 2003, 2004, 2006, 2007, 2008 Free Software Foundation, Inc.
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

#include <string.h>

#include "mpfr-impl.h"

/* Using memcpy is a few slower than swapping by hand. */

void
mpfr_swap (mpfr_ptr u, mpfr_ptr v)
{
  mpfr_prec_t p1, p2;
  mpfr_sign_t s1, s2;
  mp_exp_t e1, e2;
  mp_limb_t *m1, *m2;

  p1 = MPFR_PREC(u);
  p2 = MPFR_PREC(v);
  MPFR_PREC(v) = p1;
  MPFR_PREC(u) = p2;

  s1 = MPFR_SIGN(u);
  s2 = MPFR_SIGN(v);
  MPFR_SIGN(v) = s1;
  MPFR_SIGN(u) = s2;

  e1 = MPFR_EXP(u);
  e2 = MPFR_EXP(v);
  MPFR_EXP(v) = e1;
  MPFR_EXP(u) = e2;

  m1 = MPFR_MANT(u);
  m2 = MPFR_MANT(v);
  MPFR_MANT(v) = m1;
  MPFR_MANT(u) = m2;
}
