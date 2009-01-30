/* modified version, thanks to Norbert Mueller */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "m_apm.h"

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
  M_APM x, y, z;
  
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits \n"); exit(1);
  }
  n = atoi(argv[1]);
 
  x = m_apm_init (); y = m_apm_init (); z = m_apm_init ();

  m_apm_set_long (x, 3); m_apm_set_long (y, 1);
  m_apm_sqrt (x, n, x); m_apm_subtract (x, x, y);
  m_apm_set_long (y, 5); m_apm_sqrt (y, n, y);
  m_apm_log (z, n, x);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_multiply (z, x, y);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*y        took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_divide(z, n, x, y);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("x/y        took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_sqrt(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("sqrt(x)    took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_exp(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("exp(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_log(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("log(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_sin(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("sin(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_cos(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("cos(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_acos(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arccos(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);
  
  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) m_apm_atan(z, n, x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arctan(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  m_apm_free (x); m_apm_free (y); m_apm_free (z);
}
