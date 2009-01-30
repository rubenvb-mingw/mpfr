/* from Richard Kreckel */

#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <iostream>
#include <cln/cln.h>
using namespace std;
using namespace cln;

int cputime()
{
	struct rusage rus;
	
	getrusage (RUSAGE_SELF, &rus);
	return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}

main(int argc, char *argv[])
{
	int st, st2, N=1;
	
	if (argc != 2 && argc != 3) {
		cerr << "Usage: timing digits" << endl;
		exit(1);
	}
	int n = atoi(argv[1]);
	int prec = (int) ( n * log(10.0) / log(2.0) + 1.0 );
	cout << "prec=" << prec << ", n=" << n << endl;

	cl_F x = sqrt(cl_float(3, float_format(n)));
	cl_F y = sqrt(cl_float(5, float_format(n)));
	cl_F z;

	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			z = x * y;
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000);
	cout << "x*y        took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;
	
	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			z = x / y;
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000);
	cout << "x/y        took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;

	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			z = sqrt(x);
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000);
	cout << "sqrt(x)    took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;

	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			z = exp(x);
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000); 	  
	cout << "exp(x)     took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;

	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			z = ln(x);
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000); 	  
	cout << "log(x)     took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;

	N = 1;
	st = cputime();
	do {
		for (int i=0; i<N; i++)
			cos_sin_t z2 = cos_sin(x);
		N = 2*N;
		st2 = cputime();
	} while (st2-st<1000); 	  
	cout << "sin_cos(x) took " << (double)(st2-st)/(N-1) << " ms "
	     << "(" << N-1 << " eval in " << st2-st << "ms)" << endl;

	return 0;
}
