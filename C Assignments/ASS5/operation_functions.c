/*	Author: Peter Valovcik
	
	A set of three functions that perform arithmetic on complex numbers. A function for multiplication, division and one for both
	addition and subtraction exist.
	
*/

#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

// Definition for squaring a number since it is used somewhat frequently.
#define SQUARE(n) ((n)*(n))

/* 	Function to multiply two complex numbers that are taken as arguments. Follows the rules of multiplying that type of number and 
	returns the result as a	Complex_type. */
Complex_type multiply(struct complex_tag num1, struct complex_tag num2){
	Complex_type numMult = {((num1.real*num2.real) - (num1.imaginary*num2.imaginary)), ((num2.real*num1.imaginary) + (num1.real*num2.imaginary))};
	return numMult;
}

/*	Function to divide 2 complex numbers. It takes the pointers to the numbers and to where their division result will be stored as
	arguments. Returns -2 if division by 0 will occur and 0 otherwise. */
int divide(struct complex_tag *num1, struct complex_tag *num2, struct complex_tag *numDiv){
	
	// Make sure division by zero does not occur. Exit the function by returning -2 and an error message if it would.
	if ((SQUARE(num2->real) + SQUARE(num2->imaginary)) == 0){
		printf("ERROR: Input will result in division by zero.\n");
		return -2;
	}else{
	
	// Set the real value of the division.
	numDiv->real = ((num1->real * num2->real) + (num1->imaginary * num2->imaginary)) / (SQUARE(num2->real) + SQUARE(num2->imaginary));
	
	// Set the imaginary value of the division.
	numDiv->imaginary = ((num2->real * num1->imaginary) - (num1->real * num2->imaginary)) / (SQUARE(num2->real) + SQUARE(num2->imaginary));
	}
	
	return 0;	
}

/* 	Function to perform an addition and substraction on two complex numbers that are taken as arguments and store the results
	of these operations in structures which have their memory allocated within the function. The input of pointer to a pointer
	will ultimately point to the pointer of this allocated memory. Will return -1 if there is insufficient memory for allocation
	and 0 otherwise. */
int sumAndDifference(struct complex_tag num1, struct complex_tag num2, struct complex_tag **numSum, struct complex_tag **numDiff){
	
	// Allocate memory for the results of both addition and subtraction
	*numSum = malloc(sizeof(struct complex_tag));
	*numDiff = malloc(sizeof(struct complex_tag));
	
	// Check to make sure memory allocation was successful. Exit function by returning -1 if not.
	if (!numSum || !numDiff){
		printf("ERROR: Insufficient free memory.\n");
		return -1;
	}else{
	
	// Set real and imaginary parts of addition
	(*numSum)->real = (num1.real + num2.real);
	(*numSum)->imaginary = (num1.imaginary + num2.imaginary);
	
	// Set real and imaginary parts of subtraction
	(*numDiff)->real = (num1.real - num2.real);
	(*numDiff)->imaginary = (num1.imaginary - num2.imaginary);
	}
	
	return 0;
}

