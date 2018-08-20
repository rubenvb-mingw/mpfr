#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "cln/cln.h"

using namespace std;
using namespace cln;

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

  
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: timing digits \n"); exit(1);
  }
  n = atoi(argv[1]);

  float_format_t precision = float_format(n);
  cl_F x = sqrt (cl_float (3, precision)) - 1;
  cl_F y = sqrt (cl_float (5, precision));
  cl_F z;
  
  cout << "Prec=" << precision << endl;

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = x*y;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*y        took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = x*x;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("x*x        took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = x / y;
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("x/y        took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);


  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = sqrt (x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("sqrt(x)    took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = exp (x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("exp(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = ln (x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("log(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = sin(x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000); 	  
  printf("sin(x)     took %f ms (%d eval in %d ms)\n", 
	 (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = cos(x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("cos(x)     took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);


  cl_N xx = x;
  cl_N zz;

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) zz = acos (xx);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arccos(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

  N=1;  st = cputime();
  do {
    for (i=0;i<N;i++) z = atan (x);
    N=2*N;
    st2=cputime();
  } while (st2-st<1000);
  printf("arctan(x)  took %f ms (%d eval in %d ms)\n",
         (double)(st2-st)/(N-1),N-1,st2-st);

}