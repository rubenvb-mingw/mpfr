p = 100
S = RealField(ceil(p*log(10)/log(2)))
x = S(3)
x = sqrt(x)-1
y = S(5)
y = sqrt(y)
print("Digits=100")
N = 1000000
s = cputime()
for _ in  xrange(N):
   z = x * y

print "mul:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x / y

print "div:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sqrt()

print "sqrt:", 1000*cputime(s)/N

N = 100000
s = cputime()
for _ in  xrange(N):
   z = x.exp()

print "exp: ", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.log()

print "log:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sin()

print "sin:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.cos()

print "cos:", 1000*cputime(s)/N

N = 10000

s = cputime()
for _ in  xrange(N):
   z = x.arccos()

print "acos:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.arctan()

print "atan:", 1000*cputime(s)/N

p = 1000
S = RealField(ceil(p*log(10)/log(2)))
x = S(3)
x = sqrt(x)-1
y = S(5)
y = sqrt(y)

print("Digits=1000")
N=100000

s = cputime()
for _ in  xrange(N):
   z = x * y

print "mul:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x / y

print "div:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sqrt()

print "sqrt:", 1000*cputime(s)/N

N = 10000

s = cputime()
for _ in  xrange(N):
   z = x.exp()

print "exp:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.log()

print "log:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sin()

print "sin:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.cos()

print "cos:", 1000*cputime(s)/N

N = 1000

s = cputime()
for _ in  xrange(N):
   z = x.arccos()

print "acos:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.arctan()

print "atan:", 1000*cputime(s)/N

p = 10000
S = RealField(ceil(p*log(10)/log(2)))
x = S(3)
x = sqrt(x)-1
y = S(5)
y = sqrt(y)

print("Digits=10000")
N=10000

s = cputime()
for _ in  xrange(N):
   z = x * y

print "mul:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x / y

print "div:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sqrt()

print "sqrt:", 1000*cputime(s)/N

N = 1000

s = cputime()
for _ in  xrange(N):
   z = x.exp()

print "exp:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.log()

print "log:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.sin()

print "sin:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.cos()

print "cos:", 1000*cputime(s)/N

N = 100

s = cputime()
for _ in  xrange(N):
   z = x.arccos()

print "acos:", 1000*cputime(s)/N

s = cputime()
for _ in  xrange(N):
   z = x.arctan()

print "atan:", 1000*cputime(s)/N

quit
