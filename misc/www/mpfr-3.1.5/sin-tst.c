#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

int main (int argc, char **argv)
{
  mpfr_t x, y, z, s, c;
  mpfr_prec_t prec;
  const char *p = mpfr_get_patches ();

  printf ("MPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
          mpfr_get_version (), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
          MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
  printf ("MPFR patches: %s\n\n", p[0] ? p : "[none]");

  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s <x>\n", argv[0]);
      exit (1);
    }

  for (prec = 1000000; prec < 2000000; prec += 100000)
    {
      mpfr_inits2 (prec, x, y, z, s, c, (mpfr_ptr) 0);
      mpfr_set_str (x, argv[1], 0, MPFR_RNDN);
      mpfr_sin_cos (s, c, x, MPFR_RNDN);
      mpfr_asin (y, s, MPFR_RNDN);
      mpfr_sub (y, y, x, MPFR_RNDN);
      mpfr_printf ("prec = %7Pd: %.6Ra [asin(sin)]\n", prec, y);
      mpfr_mul_2ui (z, x, 1, MPFR_RNDN);
      mpfr_sin (y, z, MPFR_RNDN);
      mpfr_mul (z, s, c, MPFR_RNDN);
      mpfr_mul_2ui (z, z, 1, MPFR_RNDN);
      mpfr_sub (y, y, z, MPFR_RNDN);
      mpfr_printf ("prec = %7Pd: %.6Ra [sin(2x)]\n", prec, y);
      mpfr_clears (x, y, z, s, c, (mpfr_ptr) 0);
    }

  return 0;
}
