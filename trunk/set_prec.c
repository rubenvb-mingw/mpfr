/* mpfr_set_prec -- reset the precision of a floating-point number

Copyright (C) 1999, 2001 Free Software Foundation, Inc.

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
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "gmp-impl.h"
#include "mpfr.h"
#include "mpfr-impl.h"

int
mpfr_set_prec (mpfr_ptr x, mp_prec_t p)
{
  mp_prec_t xsize;

  if (p == 0)
    return 1;

  xsize = (p - 1)/BITS_PER_MP_LIMB + 1; /* new limb size */

  if (xsize > MPFR_ABSSIZE(x)) {
    MPFR_MANT(x) = (mp_ptr) (*__gmp_reallocate_func) (MPFR_MANT(x), 
		 MPFR_ABSSIZE(x)*BYTES_PER_MP_LIMB, xsize * BYTES_PER_MP_LIMB);
    MPFR_SIZE(x) = xsize; /* new number of allocated limbs */
  }

  MPFR_PREC(x) = p;

  return MPFR_MANT(x) == NULL;
}

mp_prec_t
mpfr_get_prec (mpfr_srcptr x)
{
  return MPFR_PREC(x);
}
