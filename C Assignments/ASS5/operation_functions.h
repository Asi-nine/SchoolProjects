/*	Author: Peter Valovcik
	
	Header file that includes some functions to perform arithmetic on complex numbers as well as definitions of structures representing 
	complex numbers.
*/

// A structure representing a complex number containing a real and imaginary part.
struct complex_tag{
	double real;
	double imaginary;
};


// Defining a type of a structure representing a complex number containing a real and imaginary part.
typedef struct{
	double real;
	double imaginary;
}Complex_type;

//Function to multiply 2 complex numbers.
Complex_type multiply(struct complex_tag num1, struct complex_tag num2);

//Function to divide 2 complex numbers.
int divide(struct complex_tag *num1, struct complex_tag *num2, struct complex_tag *numDiv);

//Function to add and subtract 2 complex numbers.
int sumAndDifference(struct complex_tag num1, struct complex_tag num2, struct complex_tag **numSum, struct complex_tag **numDiff);

