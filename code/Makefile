all: solver

solver: solver.o 
	gcc -o solver solver.o


sover.o: solver.c 
	 gcc -o solver.o -c solver.c -Wall -O

clean: rm -f *.o core

mrproper: clean
	  rm -f main
