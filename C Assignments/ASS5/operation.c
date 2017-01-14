/*	Author: Peter Valovcik
	
	Main function takes 4 double values as command line arguments. It treats the first two as the real and imaginary parts of
	a complex number respectfully, and the latter two as the real as the real and imaginary parts of a different complex number.
	It then performs multiplication, division, addition and subtraction of these two complex numbers and prints the results of
	the operations.
*/

#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

int main(int argc, char *argv[]){
	
	// Check to see that a proper number of command line arguments were issued when the program was run; exit program if not.
	if(argc != 5){
		printf("Invalid number of arguments. Four arguments of type double are required at execution.\n");
		exit(EXIT_FAILURE);
	}
	
	// Declaration of necessary structures and pointers to said structures.
	struct complex_tag first;
	struct complex_tag second;
	Complex_type firstTimesSecond;
	struct complex_tag plus;
	struct complex_tag *plusPt = &plus;
	struct complex_tag minus;
	struct complex_tag *minusPt = &minus;
	struct complex_tag firstDividedBySecond;
	struct complex_tag **firstPlusSecond = &plusPt;
	struct complex_tag **firstMinusSecond = &minusPt;
	
	// Set the real and imaginary parts of the first complex number from the first 2 command line arguments.
	first.real = atof(argv[1]);
	first.imaginary = atof(argv[2]);
	
	// Set the real and imaginary parts of the second complex number from the last 2 command line arguments.
	second.real = atof(argv[3]);
	second.imaginary = atof(argv[4]);
	
	// Perform multiplication of the complex numbers.
	firstTimesSecond = multiply(first, second);
	
	// Print the complex numbers and the result of their multiplication.
	printf("First complex number: %f + i(%f)\n", first.real, first.imaginary);
	printf("Second complex number: %f + i(%f)\n", second.real, second.imaginary);
	printf("Multiplication result (first x second): %f + i(%f)\n", firstTimesSecond.real, firstTimesSecond.imaginary);
	
	/* 	Performs a division while also checking if a division was performed. Prints the result of the division or that none
		was performed if division by 0 would have occured */
	if(!(divide(&first, &second, &firstDividedBySecond))){
		printf("Division result (first / second): %f + i(%f)\n", firstDividedBySecond.real, firstDividedBySecond.imaginary);
	} else {
		printf("No division was computed\n");
	}
	/* 	Performs addition and subtraction while also checking if they were performed. These will fail only if memory allocation
		within the function that performs them fails. Will print the result of both operations or that neither were performed 
		if there was not enough memory to allocate. */
	if(!(sumAndDifference(first, second, firstPlusSecond, firstMinusSecond))){
		printf("Addition result (first + second): %f + i(%f)\n", (*firstPlusSecond)->real, (*firstPlusSecond)->imaginary);
		printf("Subtraction result (first - second): %f + i(%f)\n", (*firstMinusSecond)->real, (*firstMinusSecond)->imaginary);
	} else {
		printf("No sum or difference were computed\n");
	}
	
	return 0;
}
