/*

Author: Peter Valovcik

A program that makes a magic square of size 1, 3, 5, 7, 9, 11, or 13 based on user input. A magic square has the summation of any row, column or diagonal as the same number. This magic square is based of of starting with the number 1 in the middle position of the top row, and building it around it accordingly.

*/

#include <stdio.h>

int main(void){
	int size;
    int magic_square[13][13] = {0};
    int insert = 2;
    int row = 0, rowPrevious;
    int column = 0, columnPrevious;
    short scanReturn;
	char charTest;
	
	 /*
    Prompt the user to enter an odd integer between 1 and 13 inclusive. If the number entered is not valid, then keep looping and asking for a new input
    until a valid input is entered.
    */
	
	printf("Please enter the size of the magic square you would like (odd integers between 1-13 inclusive): \n");
	scanReturn = scanf("%d", &size);
	while (scanReturn == 0 || size < 1 || size > 13 || size % 2 != 1){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ;  // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please enter an odd integer between 1 and 13 inclusive:\n");
        scanReturn = scanf("%d", &size);
    }
    
	
	
	column = size/2;
	*((*(magic_square + row)) + column) = 1;    // putting the 1 in proper position
	
	/*
	Loop through every number up to the square of the size of the square starting with 2 (since 1 was already done), and insert it one row above, and one
	column to the right of the previously inserted number. If that space is occupied, insert it one row below the previously inserted number. Make sure
	to account for end of beginning of rows resetting to the end, and end of columns resetting to the beginning.
	*/
	
	
	while(insert <= size*size){
	    rowPrevious = row;
	    columnPrevious = column;
	    
	    if (row == 0) {                                     // reset rows to end if would go below zero
	        row = size-1;
	    } else {
	        row--;
	    }
	    if (column == size-1) {                             // reset columns to beginning if would go passed end
	        column = 0;
	    } else {
	        column++;
	    }
	    if (*((*(magic_square + row)) + column) != 0){      // change input location if location following pattern is already occupied
	        if (rowPrevious != size-1){
	            row = rowPrevious + 1;
	            column = columnPrevious;
	        } else {
	            row = 0;
	            column = columnPrevious;
	        }
	    }
	    *((*(magic_square + row)) + column) = insert;
	    insert++;
	}

    /*
    Print the magic square.
    */	
	
    printf("\n");
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
		    printf("%5d", *((*(magic_square + i)) + j ));
		}
		printf("\n");
	}
	
	return 0;
}
