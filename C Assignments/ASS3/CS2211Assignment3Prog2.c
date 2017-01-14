#include <stdio.h>

/*
Author: Peter Valovcik

Program that will take a loan value, yearly interest rate, amount of monthly payment, and number of monthly payments made from a user.
The program will then calculate the total loan each month after accruing interest and making the monthly payment and report to the user
the value of the loan for each month. If the loan is paid in full, the program will let the user know how many months paying it took as
well as the amount of the final payment.
*/

int main(void){

    int months, monthsTotal = 0;
    short charTest, scanReturn;
    float loan, monthlyPayment, rate, rateInput, finalPayment;
    
     /* 
    Prompt the user to enter a loan value. Must be positive or will keep prompting for re-entry. 
    */
    
    printf("Please enter the value of your loan: \n");
    scanReturn = scanf("%f", &loan);
    while (scanReturn == 0 || loan <= 0){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter the value of your loan: \n");
        scanReturn = scanf("%f", &loan);
    }
    
     /* 
    Prompt the user to enter a yearly interest rate. Must be positive or 0 or will keep prompting for re-entry. 
    */

    printf("Please enter the yearly interest rate: \n");
    scanReturn = scanf("%f", &rateInput);
    while (scanReturn == 0 || rateInput < 0){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter the yearly interest rate: \n");
        scanReturn = scanf("%f", &rateInput);
    }
    
     /* 
    Prompt the user to enter a value representing how much they pay each month. Must be positive or will keep prompting for re-entry. 
    */

    printf("Please enter the value of your monthly payments: \n");
    scanReturn = scanf("%f", &monthlyPayment);
    while (scanReturn == 0 || monthlyPayment <= 0){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter the value of your monthly payments: \n");
        scanReturn = scanf("%f", &monthlyPayment);
    }
    
     /* 
    Prompt the user to enter the number of months they will make payments for. Must be positive or will keep prompting for re-entry.
    If a decimal input is entered, only the total number of entire months of payment will be accounted for, so anything passed the 
    decimal point will be discarded, and not rounded.
    */

    printf("Please enter the number of months you will make payments for: \n");
    scanReturn = scanf("%d", &months);
    while (scanReturn == 0 || months <= 0){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter the number of payments you will make: \n");
        scanReturn = scanf("%d", &months);
    }

    rate = 1 + ((rateInput / 12) / 100); // sets up an easier to use variable representing monthly rate based on the yearly rate
    
    /*
    Loop through for each month, and calculate the value of the loan after factoring in interest followed by the monthly payment.
    Report how much loan remains after each month of payment, and the value of the final payment if the loan was paid off as well 
    as how many months it took to do so.
    */ 
    
    while (months > 0) {
        
        /*
        Check if the loan will be paid off this month. If so report the value of the final payment and how many months it has been.
        Also let the user know that no loan remains.
        */
        
        if (loan * rate <= monthlyPayment){
            finalPayment = loan * rate;
            monthsTotal++;
            printf("After %d months the final payment of $%.2f was made.\n No loan remaining! :)\n", monthsTotal, finalPayment);
            return 0;
        }
            
        loan = loan * rate - monthlyPayment;
        monthsTotal++;
        months--;
        
        /*
        Small check just to see if it is the first month of payment in order to use the singular of the word 'month' instead of plural
        'months' in the print statement.
        */
        
        if (monthsTotal == 1) {
            printf("After %d month of payment, the remaining loan balance is: $%.2f\n\n", monthsTotal, loan);
        } else {
            printf("After %d months of payments, the remaining loan balance is: $%.2f\n\n", monthsTotal, loan);
        }       
    }   
    return 0;
}
