section .data
E_const dq 2.7182818
tmp dq 0
x dq 0
global F1
global F2
global F3
global Der1
global Der2
global Der3
const0 dq 1.000000

const1 dq 0
const2 dq -5.000000
const3 dq 0


const4 dq 0
const5 dq 0
const6 dq -2.000000
const7 dq 0
const8 dq 8.000000


;
const9 dq 0.000000

const10 dq 0
const11 dq 0
const12 dq 0
const13 dq 0.000000
const14 dq 0
const15 dq 0
const16 dq -5.000000
const17 dq 1.000000
const18 dq 0
const19 dq 0
const20 dq 0

const21 dq 0
const22 dq 0
const23 dq 0
const24 dq 0.000000
const25 dq 0
const26 dq 0
const27 dq -2.000000
const28 dq 1.000000
const29 dq 0.000000

F1:
push ebp
mov ebp, esp 
finit
fld qword[const0]
pop ebp
ret
F2:
push ebp
mov ebp, esp 
finit
fld qword [ebp + 8]
fstp qword [const3]
fld qword[const3]
fld qword[const2]
FDIVRP
FSTP qword[const1]
fld qword[const1]
pop ebp
ret
F3:
push ebp
mov ebp, esp 
finit
fld qword [ebp + 8]
fstp qword [const7]
fld qword[const7]
fld qword[const6]
FMULP
FSTP qword[const5]
fld qword[const8]
fld qword[const5]
FADDP
FSTP qword[const4]
fld qword[const4]
pop ebp
ret
Der1:
push ebp
mov ebp, esp 
finit
fld qword[const9]
pop ebp
ret
Der2:
push ebp
mov ebp, esp 
finit
fld qword [ebp + 8]
fstp qword [const14]
fld qword[const14]
fld qword[const13]
FMULP
FSTP qword[const12]
fld qword[const17]
fld qword[const16]
FMULP
FSTP qword[const15]
fld qword[const15]
fld qword[const12]
FSUBRP
FSTP qword[const11]
fld qword [ebp + 8]
fstp qword [const19]
fld qword [ebp + 8]
fstp qword [const20]
fld qword[const20]
fld qword[const19]
FMULP
FSTP qword[const18]
fld qword[const18]
fld qword[const11]
FDIVRP
FSTP qword[const10]
fld qword[const10]
pop ebp
ret
Der3:
push ebp
mov ebp, esp 
finit
fld qword [ebp + 8]
fstp qword [const25]
fld qword[const25]
fld qword[const24]
FMULP
FSTP qword[const23]
fld qword[const28]
fld qword[const27]
FMULP
FSTP qword[const26]
fld qword[const26]
fld qword[const23]
FADDP
FSTP qword[const22]
fld qword[const29]
fld qword[const22]
FADDP
FSTP qword[const21]

fld qword[const21]
pop ebp
ret
