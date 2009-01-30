#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "pari/pari.h"

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

int
main(int argc, char *argv[])
{
  int n, prec, st, st2, N, i;
  GEN x, y, z;
  unsigned long ltop;
  unsigned long long_prec;

  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits [N]\n"); exit(1);
  }
  n = atoi(argv[1]);
  if (argc==3)  N = atoi(argv[2]);
  prec = (int) ( n * log(10.0) / log(2.0) + 1.0 );
  long_prec = (prec - 1)/BITS_IN_LONG + 3;
  printf ("Prec=%d LongPrec=%lu\n", prec, long_prec);

  pari_init (20000000, 1000); 

  x = gsqrt(stoi(3), long_prec); x = addsr (-1, x);
  y = gsqrt(stoi(5), long_prec);
  z = gsqrt(stoi(7), long_prec);

  ltop = avma;

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = mulrr (x, y), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("x*y        took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = divrr (x, y), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("x/y        took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gsqrt (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("sqrt(x)    took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gexp (x, long_prec);
    avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("exp(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = glog (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("log(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gsin (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("sin(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gcos (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("cos(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gacos (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arccos(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = gatan (x, long_prec), avma = ltop;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arctan(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

}
