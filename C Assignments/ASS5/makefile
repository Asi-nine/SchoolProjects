# Author: Peter Valovcik
# makefile for operation.c, operation_functions.c, operation_functions.h

# MACRO definitions
CC  = gcc
CFLAG = -std=c99 -Wall

# All Targets
all: operation

# addition depends on the files operation.o operation_functions.o
operation: operation.o operation_functions.o
	$(CC) $(CFLAG) -o operation operation.o operation_functions.o

# operation.o depends on the source and header files
operation.o: operation.c operation_functions.h
	$(CC) $(CFLAG) -c operation.c

# operation_functions.o depends on the source and header files
operation_functions.o: operation_functions.c operation_functions.h
	$(CC) $(CFLAG) -c operation_functions.c

# test cases
test: operation
	operation 1.4 2 1 2
	operation 6 0 6.6 0
	operation 0 2 0 4.5
	operation 0 2.4 0 4
	operation 0 2 0 4
	operation 1 0 0 4
	operation 0 6.4 5.2 0
	operation 0 0 1 4
	operation 7 2 0 0
	operation 0 0 0 0
	operation -1 -1 -1 -1
	
# test case for failure too few arguments (program exit)
testfew: operation
	operation 0 1 2

# test case for failure too few arguments (program exit)
testmany: operation
	operation 0 0 0 0 0

#Clean the build directory
clean:
	rm -f *.o operation

