from mpmath.lib import (dps_to_prec, fmul, fdiv, fsqrt, fexp, flog,
    fsin, fcos, facos, fatan, from_int, fsub, MODE)

from timeit import default_timer as clock

# uncomment if psyco is not available (this is slower)
#import psyco
#psyco.full()

# uncomment if gmpy is not available (this is slower)
assert MODE == 'gmpy'

def benchmark(dps):
    prec = dps_to_prec(dps)
    rounding = 'n'
    x = fsub(fsqrt(from_int(3), prec, rounding), from_int(1), prec, rounding)
    y = fsqrt(from_int(5), prec, rounding)
    print("Digits=%i" % dps)
    N = 10000 * 100 // dps

    t1 = clock()
    for _ in  xrange(N):
        z = fmul(x, y, prec, rounding)
    t2 = clock()
    print "mul:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = fdiv(x, y, prec, rounding)
    t2 = clock()
    print "div:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = fsqrt(x, prec, rounding)
    t2 = clock()
    print "sqrt:", 1000*(t2-t1)/N

    N //= 10

    t1 = clock()
    for _ in  xrange(N):
        z = fexp(x, prec, rounding)
    t2 = clock()
    print "exp:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = flog(x, prec, rounding)
    t2 = clock()
    print "log:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = fsin(x, prec, rounding)
    t2 = clock()
    print "sin:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = fcos(x, prec, rounding)
    t2 = clock()
    print "cos:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = facos(x, prec, rounding)
    t2 = clock()
    print "acos:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = fatan(x, prec, rounding)
    t2 = clock()
    print "atan:", 1000*(t2-t1)/N

benchmark(100)
benchmark(1000)
benchmark(10000)
