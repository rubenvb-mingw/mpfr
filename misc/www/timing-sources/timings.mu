DIGITS:=100: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=100000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
"Digits:=100 x*y", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
"x/y", 1.0*(st-st0)/N;

N:=N/100:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
"sqrt(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
"exp(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
"ln(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do sin(x) end_for: st:=time()-st:
"sin(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do cos(x) end_for: st:=time()-st:
"cos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arccos(x) end_for: st:=time()-st:
"arccos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arctan(x) end_for: st:=time()-st:
"arctan(x)", 1.0*(st-st0)/N;


DIGITS:=1000: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=10000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
"Digits=1000 x*y", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
"x/y", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
"sqrt(x)", 1.0*(st-st0)/N;

N:=N/100:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
"exp(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
"ln(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do sin(x) end_for: st:=time()-st:
"sin(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do cos(x) end_for: st:=time()-st:
"cos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arccos(x) end_for: st:=time()-st:
"Arccos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arctan(x) end_for: st:=time()-st:
"arctan(x)", 1.0*(st-st0)/N;


DIGITS:=10000: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=1000:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x*y end_for: st:=time()-st:
"Digits=10000 x*y", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x/y end_for: st:=time()-st: 
"x/y", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do x^(1/2) end_for: st:=time()-st:
"sqrt(x)", 1.0*(st-st0)/N;

N:=N/100:
st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do exp(x) end_for: st:=time()-st:
"exp(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do ln(x) end_for: st:=time()-st:
"ln(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do sin(x) end_for: st:=time()-st:
"sin(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do cos(x) end_for: st:=time()-st:
"cos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arccos(x) end_for: st:=time()-st:
"arccos(x)", 1.0*(st-st0)/N;

st0:=time(): for i from 1 to N do end_for: st0:=time()-st0:
st:=time(): for i from 1 to N do arctan(x) end_for: st:=time()-st:
"arctan(x)",1.0*(st-st0)/N;
