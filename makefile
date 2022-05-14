all:
	nasm -f elf -o f_asm.o f_asm.asm
	gcc -m32 -c main.c -o main.o
	gcc -m32 main.o f_asm.o -o meduzen -lm
clean:
	rm *.o
