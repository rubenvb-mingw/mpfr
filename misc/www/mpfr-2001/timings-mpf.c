#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"

#if defined (USG) || defined (__SVR4) || defined (_UNICOS) || defined(HPUX)
#include <time.h>

int
cputime ()
{
  if (CLOCKS_PER_SEC < 100000)
    return clock () * 1000 / CLOCKS_PER_SEC;
  return clock () / (CLOCKS_PER_SEC / 1000);
}
#else
#include <sys/types.h>
#include <sys/resource.h>

int
cputime ()
{
  struct rusage rus;

  getrusage (0, &rus);
  return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}
#endif

main(int argc, char *argv[])
{
  int n, prec, st, N=1, i; mpf_t x, y, z;
  
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits [N]\n"); exit(1);
  }
  n = atoi(argv[1]);
  if (argc==3) N = atoi(argv[2]);
  prec = (int) ( n * log(10.0) / log(2.0) + 1.0 );
  printf("prec=%u\n", prec);
  mpf_init2(x, prec); mpf_init2(y, prec); mpf_init2(z, prec);
  mpf_set_d(x, 3.0); mpf_sqrt(x, x);
  mpf_set_d(y, 5.0); mpf_sqrt(y, y);

  st = cputime(); for (i=0;i<N;i++) mpf_mul(z, x, y);
  printf("x*y took %1.2ems\n", (double)(cputime()-st)/N);

  st = cputime(); for (i=0;i<N;i++) mpf_div(z, x, y);
  printf("x/y took %1.2ems\n", (double)(cputime()-st)/N);

  st = cputime(); for (i=0;i<N;i++) mpf_sqrt(z, x);
  printf("sqrt(x) took %1.2ems\n", (double)(cputime()-st)/N);

  mpf_clear(x); mpf_clear(y); mpf_clear(z);
}
