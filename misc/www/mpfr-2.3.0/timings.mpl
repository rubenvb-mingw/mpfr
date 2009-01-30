kernelopts(printbytes=false): # thanks to Dave Hare
readlib(`evalf/exp`): readlib(`evalf/ln`): # thanks to Dave Hare, again
readlib(`evalf/sin`): readlib(`evalf/cos`):
readlib(`evalf/arccos`): readlib(`evalf/arcsin`):
readlib(forget):

# 100 digits
Digits:=100: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=10000:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x*y od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x/y od: st:=time()-st: 
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x^(1/2) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

N:=N/10:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/exp/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/ln`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/sin/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/cos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

# evalf/arccos calls evalf(arcsin()) thus we need to forget evalf
st0:=time(): to N do forget(evalf) od: st0:=time()-st0:
st:=time(): to N do forget(evalf): `evalf/arccos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/arctan/real`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

# 1000 digits
Digits:=1000: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=1000:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x*y od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x/y od: st:=time()-st: 
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x^(1/2) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

N:=N/10:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/exp/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/ln`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/sin/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/cos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

# evalf/arccos calls evalf(arcsin()) thus we need to forget evalf
st0:=time(): to N do forget(evalf) od: st0:=time()-st0:
st:=time(): to N do forget(evalf): `evalf/arccos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/arctan/real`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

# 10000 digits
Digits:=10000: x:=sqrt(3.0)-1.0: y:=sqrt(5.0):

N:=100:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x*y od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x/y od: st:=time()-st: 
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do x^(1/2) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

N:=N/10:
st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/exp/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/ln`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/sin/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/cos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

# evalf/arccos calls evalf(arcsin()) thus we need to forget evalf
st0:=time(): to N do forget(evalf) od: st0:=time()-st0:
st:=time(): to N do forget(evalf): `evalf/arccos/general`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);

st0:=time(): to N do od: st0:=time()-st0:
st:=time(): to N do `evalf/arctan/real`(x) od: st:=time()-st:
evalf(1000*(st-st0)/N, 3);
