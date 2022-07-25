section .data
 const2 dq 2.0
 constn2 dq -2.0
 const8 dq 8.0
 constn5 dq -5.0
section .text
global F1
global F2
global F3

F1: ;calculate F1 = exp(x)+2
 finit ;f(x)=exp(x) calculation 
 push ebp
 mov ebp, esp
 fld qword [ebp + 8]
fldl2e ;st0=log2(e)
fmulp st1, st0 ;st0=log2(e) *arg
fld1
fld st1
fprem
f2xm1
faddp   st1, st0
fscale
fstp    st1

fld qword[const2] ;calculating f(x)=exp(x) + 2  
faddp
 pop ebp
 ret
 
F2: ;calculating F2(x)= -2*arg +8
 finit
 push ebp
 mov ebp, esp
 fld qword [ebp + 8];st0=arg
 fld qword [constn2];st0=-2
 fmulp ; st0= -2*arg
 fld qword [const8] 
 faddp; F2(x)=st0=-2*arg+8
 pop ebp
 ret
F3: ;calculating F3(x)= -5/x
 finit
 push ebp
 mov ebp, esp
 fld qword [constn5]   ; st0=-5
 fld qword [ebp + 8] ;st0=arg, st1=-5
 FDIVP ;F3(x)=st0=-5/x

 pop ebp
 ret
