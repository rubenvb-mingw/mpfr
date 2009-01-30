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

main(int argc, char *argv[])
{
  int n, prec, st, N=1, i, ltop; GEN x, y, z;
  
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits [N]\n"); exit(1);
  }
  n = atoi(argv[1]);
  if (argc==3)  N = atoi(argv[2]);
  prec = (int) ( n * log(10.0) / log(2.0) + 1.0 );
  printf("prec=%u\n", prec);

  init(40000000, 10000); 

  x = gsqrt(stoi(3), (prec - 1)/BITS_IN_LONG + 2); 
  y = gsqrt(stoi(5), (prec - 1)/BITS_IN_LONG + 2);

  ltop = avma; 

  st = cputime(); for (i=0;i<N;i++) z = gmul(x, y); 
  printf("x*y took %1.2ems\n", (double)(cputime()-st)/N);
  avma = ltop;

  st = cputime(); for (i=0;i<N;i++) z = gdiv(x, y); 
  printf("x/y took %1.2ems\n", (double)(cputime()-st)/N);
  avma = ltop; 

  st = cputime(); for (i=0;i<N;i++) z = gsqrt(x, evalprecp(x)); 
  printf("sqrt(x) took %1.2ems\n", (double)(cputime()-st)/N);
  avma = ltop;

  st = cputime(); for (i=0;i<N;i++) z = gexp(x, evalprecp(x)); 
  printf("exp(x) took %1.2ems\n", (double)(cputime()-st)/N);
  avma = ltop;

  st = cputime(); for (i=0;i<N;i++) z = glog(x, evalprecp(x)); 
  printf("log(x) took %1.2ems\n", (double)(cputime()-st)/N);
  avma = ltop;
}
