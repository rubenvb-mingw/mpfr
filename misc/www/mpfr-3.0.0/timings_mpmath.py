from mpmath.settings import dps_to_prec, MODE
from mpmath.libmpf import mpf_mul, mpf_div, mpf_sqrt, from_int, mpf_sub
from mpmath.libelefun import mpf_exp, mpf_log, mpf_sin, mpf_cos, mpf_acos, mpf_atan

from timeit import default_timer as clock

# comment out if psyco is not available
#import psyco
#psyco.full()

# comment out if gmpy is not available
assert MODE == 'gmpy'

def benchmark(dps):
    prec = dps_to_prec(dps)
    rounding = 'n'
    x = mpf_sub(mpf_sqrt(from_int(3), prec, rounding), from_int(1), prec, rounding)
    y = mpf_sqrt(from_int(5), prec, rounding)
    print("Digits=%i" % dps)
    N = 10000 * 100 // dps

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_mul(x, y, prec, rounding)
    t2 = clock()
    print "mul:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_div(x, y, prec, rounding)
    t2 = clock()
    print "div:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_sqrt(x, prec, rounding)
    t2 = clock()
    print "sqrt:", 1000*(t2-t1)/N

    N //= 10

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_exp(x, prec, rounding)
    t2 = clock()
    print "exp:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_log(x, prec, rounding)
    t2 = clock()
    print "log:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_sin(x, prec, rounding)
    t2 = clock()
    print "sin:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_cos(x, prec, rounding)
    t2 = clock()
    print "cos:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_acos(x, prec, rounding)
    t2 = clock()
    print "acos:", 1000*(t2-t1)/N

    t1 = clock()
    for _ in  xrange(N):
        z = mpf_atan(x, prec, rounding)
    t2 = clock()
    print "atan:", 1000*(t2-t1)/N

benchmark(100)
benchmark(1000)
benchmark(10000)
