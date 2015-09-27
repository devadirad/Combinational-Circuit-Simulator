COMPILER = gcc
CCFLAGS  = -Wall -ansi -pedantic -w
all: comb

comb: comb.o
	$(COMPILER) $(CCFLAGS) -o comb comb.o -lm
comb.o: comb.c comb.h
	$(COMPILER) $(CCFLAGS) -c comb.c 
clean:
	rm -f comb comb.o