#include <stdio.h>

/*
Author: Peter Valovcik

Program that calculates Euler's number based on its summation series to the accuracy such that terms of the summation are added until
they are less than the value entered by the user. It then tells the user the number of terms that were added and reports Euler's number
to 15 decimal places.
*/

int main(void){
    
    double eulersNumber, input, loopCheck = 1, factorial;
    short scanReturn, charTest, numTerms = 0;
    
    /*
    Prompt user for an input of a value of accuracy to which Euler's number will be determined.
    */
    
    printf("Please enter a positive decimal number less than 1 to represent the accuracy you would like of Euler's number.");
    printf("\nFor example, 0.001 would indicate accuracy to the summation of terms of the number that are greater than or equal to 0.001: \n");
    
    /*
    If the input is invalid (not a positive number less than 1) then the program will reprompt for a valid input until a valid one is received.
    */
    
    scanReturn = scanf("%lf", &input);
    while (scanReturn == 0 || input >= 1 || input <= 0){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter a positive decimal number less than 1 to represent the accuracy you would like of Euler's number:\n");
        scanReturn = scanf("%lf", &input);
    }
    
    /*
    Calculate a factorial number and add its reciprocal to Eulers number representation. Keeps track of how many terms from the summation
    equaltion have been added in total.
    */
    
    for (int j = 0; loopCheck >= input; j++){
        if (j == 0){   // accounts for the case of zero factorial, which is equal to 1
            factorial = 1;
        }else {
        factorial = factorial * j;
        loopCheck =  1 / (factorial * (j + 1)); // holds the value of the next term of the summation to check before next iteration
        }
        eulersNumber = eulersNumber + ( 1 / factorial);
        numTerms++;     
    }
    
    /*
    Prints the value of Euler's number to 15 decimal places as well as how many terms of the summation were added to get this value of it.
    */
    
    printf("e = %.15lf based on the addition of %d terms.\n", eulersNumber, numTerms);

    return 0;
}
