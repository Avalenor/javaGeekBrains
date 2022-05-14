global f1
global f2
global f3
global df1
global df2
global df3
																										  ; // double f1(double x){
																										  ; // 	return (3 / (pow(x - 1, 2) + 1));
																										  ; // }
f1:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax

	fld1
	fld1
	fld1
	faddp
	faddp

	fld qword[ebp - 16]
	fld1
	fsubp
	fld qword[ebp - 16]
	fld1
	fsubp
	fmulp
	fld1
	faddp
	fdivp

	mov esp, ebp
	pop ebp
	ret

																										  ; // double f2(double x){
																										  ; // 	return sqrt(x + 0.5);
																										  ; // }
f2:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax

	fld qword[ebp - 16]

	fld1
	fld1
	fld1
	faddp
	fdivp
	faddp
	fsqrt

	mov esp, ebp
	pop ebp
	ret
																									     ; // double f3(double x){
																										  ; // 	return pow(e, -x);
																										  ; // }
f3:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax

	fld1
	fld qword[ebp - 16]

	fldl2e
	fmulp
	fld1
	fld st1
	fprem
	f2xm1
	faddp
	fscale
	fstp st1
	fdivp

	mov esp, ebp
	pop ebp
	ret
																										  ; // double df1(double x){
																										  ; // 	return ((6 * (1 - x)) / pow(pow(x - 1, 2) + 1, 2));
																										  ; // }

df1:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax


	fld1
	fld1
	fld1
	fld1
	fld1
	fld1
	faddp
	faddp
	faddp
	faddp
	faddp

	fld1
	fld qword[ebp - 16]
	fsubp
	fmulp
	;------------------
	fld qword[ebp - 16]
	fld1
	fsubp
	fld qword[ebp - 16]
	fld1
	fsubp

	fmulp

	fld1
	faddp
	fld qword[ebp - 16]
	fld1
	fsubp
	fld qword[ebp - 16]
	fld1
	fsubp
	fmulp
	fld1
	faddp
	fmulp
	;-------------------
	fdivp

	mov esp, ebp
	pop ebp
	ret
																										  ; // double df2(double x){
																										  ; // 	return (1 / (2 * sqrt(x + 0.5)));
																										  ; // }
df2:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax

	fld1   ;1

	fld1
	fld1
	faddp  ;2

	fld1
	fld1
	fld1
	faddp
	fdivp
	fld qword[ebp - 16]
	faddp
	fsqrt

	fmulp  ;2 * sqrt
	fdivp  ;1/2*sqrt

	mov esp, ebp
	pop ebp
	ret
																										  ; // double df3(double x){
																										  ; // 	return ((-1) / pow(e, x));
																										  ; // }

df3:
	push ebp
	mov ebp, esp

	sub esp, 24
	mov eax, dword[ebp+8]
	mov dword[ebp-16], eax
	mov eax, dword[ebp+12]
	mov dword[ebp-12], eax

	fld1
	fchs
	fld qword[ebp - 16]

	fldl2e
	fmulp
	fld1
	fld st1
	fprem
	f2xm1
	faddp
	fscale
	fstp st1
	fdivp

	mov esp, ebp
	pop ebp
	ret
