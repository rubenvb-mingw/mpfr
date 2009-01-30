# 100 digits #
DIGITS:=100: x:=sqrt(3.0): y:=sqrt(5.0):

N:=100000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
1.0*(st-st0)/N;

N:=10000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
1.0*(st-st0)/N;

# 1000 digits
DIGITS:=1000: x:=sqrt(3.0): y:=sqrt(5.0):

N:=1000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
1.0*(st-st0)/N;

N:=100:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
1.0*(st-st0)/N;

# 10000 digits
DIGITS:=10000: x:=sqrt(3.0): y:=sqrt(5.0):

N:=100:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
1.0*(st-st0)/N;

N:=1:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
1.0*(st-st0)/N;
