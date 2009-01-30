/* compile this file with "gcc -mfp-rounding-mode=d bug.c -lm".
The following output is correct:

charlier% gcc -mfp-rounding-mode=d bug.c -lm
charlier% ./a.out
x+y=1.52691009397285539840e+19

The following is buggy:

javelet% gcc -mfp-rounding-mode=d bug.c -lm
javelet% ./a.out
x+y=1.53051297367475179520e+19

 */

#include <fenv.h>

main()
{
  double x, y, z;

  fesetround(FE_UPWARD);
  x = 1.95312500000000043368e-03;
  y = 1.52691009397285519360e+19;
  z = x + y;
  printf("x+y=%1.20e\n", z);
}
