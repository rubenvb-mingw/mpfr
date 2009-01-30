/* modified version, thanks to Norbert Mueller */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "mpfr.h"

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
  int n, prec, st, st2, N=1, i; mpfr_t x, y, z, z2;
  
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits \n"); exit(1);
  }
  n = atoi(argv[1]);
  prec = (int) ( n * log(10.0) / log(2.0) + 1.0 );
  printf("prec=%u\n", prec);
  mpfr_init2(x, prec); mpfr_init2(y, prec); mpfr_init2(z, prec); 
mpfr_init2(z2, prec);
  mpfr_set_d(x, 3.0, GMP_RNDN); mpfr_sqrt(x, x, GMP_RNDN);
  mpfr_set_d(y, 5.0, GMP_RNDN); mpfr_sqrt(y, y, GMP_RNDN);

  mpfr_log(z, x, GMP_RNDN);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_add(z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x+y        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_sub(z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x-y        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_mul(z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*y        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_div(z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x/y        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);


  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_mul_ui (z, x, 4294967291, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*i        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_div_ui (z, x, 4294967291, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x/i        took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  mpfr_set_prec (y, 64);
  mpfr_random (y);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_mul (z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*(2 limbs)took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_div (z, x, y, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("x/(2 limbs)took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_sqrt(z, x, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("sqrt(x)    took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);


  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_exp(z, x, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("exp(x)     took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);


  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_log(z, x, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("log(x)     took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);


  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_cos(z, x, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("cos(x)     took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
	for (i=0;i<N;i++) mpfr_sin(z, x, GMP_RNDN);
	N=2*N;
	st2=cputime();
  } while (st2-st<1000); 	  
  printf("sin(x)     took %f ms (%d eval in %d ms)\n", 
(double)(st2-st)/(N-1),N-1,st2-st);

  mpfr_clear(x); mpfr_clear(y); mpfr_clear(z);
}
