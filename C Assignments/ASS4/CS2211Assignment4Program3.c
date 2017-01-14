/*

Author: Peter Valovcik

A program that uses a function to determine the smallest combination of bills a user can use to pay an amount they have entered.

*/

#include <stdio.h>

/* Function prototype */

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies);


int main(void){
    
    int dollars, twenty = 0, ten = 0, five = 0, two = 0, one = 0, *twenties = &twenty, *tens = &ten, *fives = &five, *toonies = &two, *loonies = &one;
    short scanReturn;
	char charTest;
    
    /*
    Prompt the user to enter a positive dollar amount. If the number entered is not valid, then keep looping and asking for a new input
    until a valid input is entered.
    */

    printf("Please enter a dollar amount more than zero rounded to the nearest dollar:\n");
    scanReturn = scanf("%d", &dollars);
    while (scanReturn == 0 || dollars < 1){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please enter an integer dollar amount more than zero:\n");
        scanReturn = scanf("%d", &dollars);
    }
    
    /* Call function to determine bills needed to pay */
    
    pay_amount(dollars, twenties, tens, fives, toonies, loonies);
    
    /* Print the smallest combination of bills that can be used to pay */
    
    printf("You can pay with these bills:\n");
    if (twenty > 0) {
        printf("$20 x %5d\n", twenty);
    }
    if (ten > 0) {
        printf("$10 x %5d\n", ten);
    }
    if (five > 0) {
        printf("$5  x %5d\n", five);
    }
    if (two > 0) {
        printf("$2  x %5d\n", two);
    }
    if (one > 0) {
        printf("$1  x %5d\n", one);
    }
    
    return 0;
}

/*
Function that takes in pointers and a dollar amount and changes the variables to which the pointers are pointing to the smallest combination
of bills that can be used to pay the input dollar amount. 
*/

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonies){
    
    *twenties = dollars / 20;
    *tens = (dollars % 20) / 10;
    *fives = (dollars % 10) / 5;
    *toonies = (dollars % 5) / 2;
    *loonies = (dollars % 5 % 2) / 1;
        
}
