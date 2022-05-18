section .data
    const2 dq 2.0
    constm2 dq -2.0
    const8 dq 8.0
    constm5 dq -5.0
    const5 dq 5.0
    
section .text
    global f1
    global f2
    global f3
    global df1
    global df2
    global df3
   
f1:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[ebp + 8]
    fldl2e
    fmulp
    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale
    fstp st1
    fstp st1
    
    fld qword[const2]
    faddp
    
    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]
    fld qword [constm2]
    fmulp
    fld qword [const8]
    faddp
    
    mov esp, ebp
    pop ebp
    ret
    
f3:
    push ebp
    mov ebp, esp
    
    fld qword [ebp + 8]
    fld qword [constm5]
    fdivrp 

    mov esp, ebp
    pop ebp
    ret
     
df1:
    push ebp
    mov ebp, esp
    
    fld1
    fld qword[ebp + 8]
    fldl2e
    fmulp
    fld1
    fld st1
    fprem
    f2xm1
    faddp
    fscale
    fstp st1
    fstp st1
    
    
    mov esp, ebp
    pop ebp
    ret

df2:
    push ebp
    mov ebp, esp
    
    fld qword [constm2]
     
    mov esp, ebp
    pop ebp
    ret
    
df3:
    push ebp
    mov ebp, esp
    
    
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmulp
    fld qword [const5]
    fdivrp
    
    mov esp, ebp
    pop ebp
    ret