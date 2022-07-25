COMPILER=gcc
OPT=-O2 -std=gnu99 -m32 -lm
.PHONY: all clean help test

all: main

clean:
	rm -rf main.o integral.o root.o main
	rm -rf func.o 
func.o: func.s
	nasm -DUNIX -Werror -f elf -o func.o func.s

integral.o: integral.c
	$(COMPILER) integral.c -c -o integral.o $(OPT)

root.o: root.c
	$(COMPILER) root.c -c -o root.o $(OPT)

main.o: main.c
	$(COMPILER) main.c -c -o main.o $(OPT)

main: main.o integral.o root.o func.o
	$(COMPILER) -o main main.o integral.o root.o func.o  $(OPT)

help: main
	./main -help

test: main
	./main -test -axis -iter
area: main
	./main -area