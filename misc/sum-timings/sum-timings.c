#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gmp.h>
#include <mpfr.h>

/* Warning! These timings are very inaccurate: in practice, one can get
 * more than a factor 3 (but less than 4) between two invocations. Using
 * only one core improves a bit, but not much (e.g. 0.1192 -> 0.2324 s).
 * However, this test can be regarded as sufficient to compare the three
 * algorithms (sum_old, sum_new, sum_add), because the goal is to detect
 * factors between them much larger than 2.
 */

/* Minor improvements done on 2016-06-17:
 *   - Use a single MPFR object for the result. Using one per function
 *     was useless and could introduce a (probably very little) bias
 *     due to different alignment and locality.
 *   - Before doing timings, run each code once, in case the initial run
 *     would take much more time (this is again unlikely).
 * However, these improvements will remain unnoticeable until there is a
 * way to get accurate timings.
 */

/* Note: It may be useful to check with precy slightly different from precx
 * because mpfr_add has a special optimization when all the precisions are
 * the same.
 */

typedef int (*sumf) (mpfr_ptr, mpfr_ptr *const, unsigned long, mpfr_rnd_t);

#ifdef ONLY_SUM
# define N 1
# define FP_LIST mpfr_sum
# define FN_LIST "sum"
# define sum_ref mpfr_sum
#else
# define N 3
# define FP_LIST mpfr_sum, mpfr_sum_new, mpfr_sum_add
# define FN_LIST "sum_old", "sum_new", "sum_add"
# define sum_ref mpfr_sum_new
#endif

static sumf fp[N] = { FP_LIST };
static char *fn[N] = { FN_LIST };

static void
check_random (mpfr_rnd_t r, long n, long nc,
              mpfr_prec_t precx, mpfr_prec_t precy,
              unsigned long emax, long ntests, unsigned long seed)
{
  mpfr_t *x, s;
  mpfr_ptr *p;
  long i, j;
  gmp_randstate_t state;
  clock_t c;

  gmp_randinit_default (state);
  gmp_randseed_ui (state, seed);

  mpfr_init2 (s, precy);

  x = (mpfr_t *) malloc (n * sizeof (mpfr_t));
  p = (mpfr_ptr *) malloc (n * sizeof (mpfr_ptr));
  for (i = 0; i < n; i++)
    {
      mpfr_init2 (x[i], precx);
      if (i < n - nc)
        {
          mpfr_urandom (x[i], state, r);
          if (gmp_urandomm_ui (state, 2))
            mpfr_neg (x[i], x[i], MPFR_RNDN);
          mpfr_mul_2ui (x[i], x[i], gmp_urandomm_ui (state, emax), MPFR_RNDN);
        }
      else
        {
          sum_ref (x[i], p, i, MPFR_RNDN);
          mpfr_neg (x[i], x[i], MPFR_RNDN);
          if (mpfr_zero_p (x[i]))
            {
              /* Stop here as it is not very useful to fill the array
                 with zeros. */
              mpfr_clear (x[i]);
              n = i;
              break;
            }
        }
      p[i] = x[i];
    }

  if (nc)  /* random permutation with 2*n random transpositions */
    for (i = 0; i < 2*n; i++)
      {
        int i1, i2;
        i1 = gmp_urandomm_ui (state, n);
        i2 = gmp_urandomm_ui (state, n);
        mpfr_swap (x[i1], x[i2]);
      }

  /* Before doing timings, run each code once. */
  for (i = 0; i < N; i++)
    fp[i] (s, p, n, r);

  for (i = 0; i < N; i++)
    {
      c = clock ();
      for (j = 0; j < ntests; j++)
        fp[i] (s, p, n, r);
      c = clock () - c;
      mpfr_printf ("%s took %7.4f s  (%Rg)\n", fn[i],
                   (double) c / CLOCKS_PER_SEC, s);
    }

  for (i = 0; i < n; i++)
    mpfr_clear (x[i]);
  free (x);
  free (p);
  mpfr_clear (s);
  gmp_randclear (state);
}

int main (int argc, char *argv[])
{
  int r;
  long n, nc, precx, precy, emax, ntests;
  unsigned long seed;

  if (argc != 9)
    {
      fprintf (stderr, "Usage: %s <rndmode> <size> <nc> <precx> <precy>"
               " <emax> <ntests> <seed>\n", argv[0]);
      exit (1);
    }

  r = atoi (argv[1]);
  if (r < 0 || r > 4)
    {
      fprintf (stderr, "%s: invalid rounding mode = %d\n", argv[0], r);
      exit (1);
    }

  n = atol (argv[2]);
  if (n < 0)
    {
      fprintf (stderr, "%s: invalid size n = %ld\n", argv[0], n);
      exit (1);
    }

  nc = atol (argv[3]);
  if (nc < 0 || nc >= n)
    {
      fprintf (stderr, "%s: invalid nc = %ld\n", argv[0], nc);
      exit (1);
    }

  precx = atol (argv[4]);
  if (precx < MPFR_PREC_MIN || precx > MPFR_PREC_MAX)
    {
      fprintf (stderr, "%s: invalid precx = %ld\n", argv[0], precx);
      exit (1);
    }

  precy = atol (argv[5]);
  if (precy < MPFR_PREC_MIN || precy > MPFR_PREC_MAX)
    {
      fprintf (stderr, "%s: invalid precy = %ld\n", argv[0], precy);
      exit (1);
    }

  emax = atol (argv[6]);
  if (emax < 1)
    {
      fprintf (stderr, "%s: invalid emax = %ld\n", argv[0], emax);
      exit (1);
    }

  ntests = atol (argv[7]);
  if (ntests < 1)
    {
      fprintf (stderr, "%s: invalid ntests = %ld\n", argv[0], ntests);
      exit (1);
    }

  seed = (unsigned long) atol (argv[8]);

  check_random ((mpfr_rnd_t) r, n, nc, precx, precy, emax, ntests, seed);

  return 0;
}
