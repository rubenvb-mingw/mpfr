#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <gmp.h>
#include <mpfr.h>

#ifdef USE_TIMP

#include <timp.h>
typedef unsigned long long st_time_t;
#define K 55  /* odd */

#else

typedef clock_t st_time_t;
#define K 5  /* odd */

#endif

/* Warning! These timings are very inaccurate: in practice, one can get
 * more than a factor 3 (but less than 4) between two invocations. Using
 * only one core improves a bit, but not much (e.g. 0.1192 -> 0.2324 s).
 * However, this test can be regarded as sufficient to compare the three
 * algorithms (sum_old, sum_new, sum_add), because the goal is to detect
 * factors between them much larger than 3.
 */

/* Minor improvements done on 2016-06-17:
 *   - Use a single MPFR object for the result. Using one per function
 *     was useless and could introduce a (probably very little) bias
 *     due to different alignment and locality.
 *   - Before doing timings, run each code once, in case the initial run
 *     would take much more time (this is again unlikely).
 * However, these improvements will remain unnoticeable until there is a
 * way to get accurate timings.
 *
 * Improvement done on 2016-06-18: Each test is done 5 times and one
 * keeps the median. This allows one to avoid most big differences
 * between two invocations of the same test, but not completely; a
 * factor larger than 3 can still be obtained (see above). Doing the
 * tests 7 times instead of 5 does not help at all.
 *
 * The pseudo-random numbers have changed on 2016-12-28. The rounding mode
 * was previously used to determine them, but for no good reason; this was
 * a mistake.
 *
 * Support for timp.h (from tools/mbench) added on 2017-01-02. Compile
 * with -DUSE_TIMP to use it. But timings are still inaccurate. Timing
 * intervals are now output to try to avoid a bad interpretation, but
 * even with K = 25, for two fixed tests A and B and two runs 1 and 2,
 * one can get A1 < B1 and B2 < A2, where I < J means that interval I
 * strictly precedes interval J, i.e. sup(I) < inf(J).
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
# define RND_MAX 5
/* 5 can only be used in the faithful branch or once this branch
   has been merged in the trunk. */
#else
# define N 3
# define FP_LIST mpfr_sum, mpfr_sum_new, mpfr_sum_add
# define FN_LIST "sum_old", "sum_new", "sum_add"
# define sum_ref mpfr_sum_new
# define RND_MAX 4
#endif

#define SIZE 64

static sumf fp[N] = { FP_LIST };
static char *fn[N] = { FN_LIST };

int cmp (const void *a, const void *b)
{
  st_time_t u, v;

  u = * (st_time_t *) a;
  v = * (st_time_t *) b;
  return u < v ? -1 : u > v;
}

static void
check_random (mpfr_rnd_t r, long n, long nc,
              mpfr_prec_t precx, mpfr_prec_t precy,
              unsigned long emax, long ntests, unsigned long seed)
{
  mpfr_t *x, s;
  mpfr_ptr *p;
  long i, k;
  gmp_randstate_t state;
  st_time_t t[N][K];
  char str[N][SIZE];

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
          mpfr_urandom (x[i], state, MPFR_RNDN);
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

#ifdef USE_TIMP
  TIMP_OVERHEAD ();
#endif

  for (k = 0; k < K; k++)
    for (i = 0; i < N; i++)
      {
#ifdef USE_TIMP
        t[i][k] = TIMP_MEASURE (fp[i] (s, p, n, r));
#else
        st_time_t c;
        long j;

        c = clock ();
        for (j = 0; j < ntests; j++)
          fp[i] (s, p, n, r);
        t[i][k] = clock () - c;
#endif
        if (k == 0)
          mpfr_snprintf (str[i], SIZE, "%Rg", s);
      }

  for (i = 0; i < N; i++)
    {
      /* The simplest way to get the median in C is to sort... */
      qsort (t[i], K, sizeof t[0][0], cmp);
#ifdef USE_TIMP
      /* Let's remove the first and the last measurements. */
      printf ("%s took %llu cycles [%llu to %llu (+%.1f%%)] (%s)\n",
              fn[i], t[i][(K-1)/2], t[i][1], t[i][K-2],
              100.0 * (t[i][K-2] - t[i][1]) / t[i][1], str[i]);
#else
      printf ("%s took %7.4f s  (%s)\n", fn[i],
              (double) t[i][(K-1)/2] / CLOCKS_PER_SEC, str[i]);
#endif
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

  assert ((K & 1) != 0);

  if (argc != 9)
    {
      fprintf (stderr, "Usage: %s <rndmode> <size> <nc> <precx> <precy>"
               " <emax> <ntests> <seed>\n", argv[0]);
      exit (1);
    }

  r = atoi (argv[1]);
  if (r < 0 || r > RND_MAX)
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
