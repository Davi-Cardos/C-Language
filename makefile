# Makefile 

CC = gcc
CFLAGS = -O2 -fopenmp
LIBS = -lgmp

all: soma_prog

soma_prog: soma_prog.c
	$(CC) soma_prog.c -o soma_prog $(CFLAGS) $(LIBS)

clean:
	rm -f soma_prog
