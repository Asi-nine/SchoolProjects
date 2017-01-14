/*

Author: Peter Valovcik

A program that will calculate the value of pi using a random number generator and the equation for area of a circle based on a number
of trials that a user will input. It will do those trials 10 times, report the value of pi calculated each time, and finally a mean and
standard deviation of those 10.

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    
	double x, y;
	double pi, sum = 0, squaresum = 0, mean, sd, countIn = 0;
	long N;
	short scanReturn;
	char charTest;
	
	/* 
    Prompt the user to enter a positive integer. If the number entered is not valid, then keep looping and asking for a new input
    until a valid input is entered.
    */
	
	printf("Please enter a positive integer (decimal numbers will ignore the value passed the decimal):\n");
	scanReturn = scanf("%ld", &N);
    while (scanReturn == 0 || N < 1){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please enter a positive integer:\n");
        scanReturn = scanf("%ld", &N);
    }
    
	srand((unsigned) time(NULL));               // initialize random number generator based on time
	
	for(int j = 0; j < 10; j++){                // loop 10 times
		for(long i = 0; i < N; i++){            // loop user input times
			x = (double)rand() / RAND_MAX;      // generate a number between 0 and 1 inclusive for x
			y = (double)rand() / RAND_MAX;      // generate a number between 0 and 1 inclusive for y
			if(x*x + y*y <= 1){                 // check if the randomly generated point lies within the circle
				countIn++;
			}
		}
		pi = (countIn/N)*4;                             // calculate pi
		printf("#%d value of pi: %f\n", (j+1), pi);     
		sum += pi;                                      // calculate sum
		squaresum += pi*pi;                             // calculate the squared sum
		countIn = 0;                                    
	}
	
	mean = sum / 10;                                    // calculate mean
	sd = ((squaresum/10) - (mean*mean));                // calculate part of standard deviation
	if (sd < 0) {                                       // make sure standard deviation squared isn't negative before rooting
		sd = -sd;
	}
	sd = sqrt(sd);                                      // finish standard deviation calculation
	
	printf("The mean is: %f\n", mean);
	printf("The standard deviation is: %f\n", sd);
	
	return 0;
}
