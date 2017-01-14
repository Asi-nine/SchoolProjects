#include <stdio.h>

/*
Author: Peter Valovcik

Program that will take a 24 hour clock time input from a user. It will then take a duration of time, which can be both positive and negative
and determine the time after adding/subtracting that duration to/from the originally input time. It will then return the time after having waited
that duration.
*/

int main(void){

    int timeOfDay, timeOfDayHour, timeOfDayMin, timeDuration, timeDurationHour, timeDurationMin;
    int finalTimeHour, finalTimeMin, durationMinTotal, dayMinTotal, totalTime;
    short scanReturn, charTest;
    
    /* 
    Prompt the user to enter a time. If the time entered is not valid based on a 24 hour clock, then keep looping and asking for a new input
    until a valid input is entered.
    */
    
    printf("Please enter a time based on a 24 hour clock in the form HHMM (H = hour, M = min): \n");
    scanReturn = scanf("%d", &timeOfDay);
    while (scanReturn == 0 || timeOfDay < 0 || timeOfDay >= 2400 || (timeOfDay % 100) > 59){
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ; // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter a time based on a 24 hour clock in the form HHMM (H = hour, M = min): \n");
        scanReturn = scanf("%d", &timeOfDay);
    }
    
    
    timeOfDayHour = timeOfDay / 100; //calculate hours
    timeOfDayMin = timeOfDay % 100; //calculate minutes
    dayMinTotal = (timeOfDayHour * 60) + timeOfDayMin; //convert to a total of minutes based on hour and minutes
    
    /* 
    Prompt the user to enter a time duration. If the duration entered is not valid based on a 24 hour clock for a 59 minute limit, 
    then keep looping and asking for a new input until a valid input is entered. Can be negative or positive.
    */
    
    printf("Please indicate how much time will pass in the form DHHMM (D = direction: + for forward or - for backward, H = hour, M = min): \n");
    scanReturn = scanf("%d", &timeDuration);
    while (scanReturn == 0 || timeDuration < -9999 || timeDuration > 9999 || (timeDuration % 100) > 59 || (timeDuration % 100) < -59) {
        while((charTest = getchar()) != EOF && charTest != '\n'){
            ; // do nothing loop that deals with infinite loop that does not allow user to reinput which occurs otherwise
        }
        printf("That was an invalid input. Please re-enter how much time will pass in the form DHHMM (D = direction: + for forward or ");
        printf("- for backward, H = hour, M = min): \n");
        scanReturn = scanf("%d", &timeDuration);
    }
    
    timeDurationHour = timeDuration / 100;  //calculate hours
    timeDurationMin = timeDuration % 100;  //calculate minutes
    durationMinTotal = (timeDurationHour * 60) + timeDurationMin;  //convert to a total of minutes based on hour and minutes
    
    totalTime = dayMinTotal + durationMinTotal;  // get time after waiting the duration from the initial time
    
    /*
    Check if the end time is "positive" or "negative" then determines what the final time is based on that since the approach is different
    depending on that.
    */
    if (totalTime >= 0) {
        finalTimeHour = (totalTime / 60) % 24;
        finalTimeMin = (totalTime % 60);
    } else {
        finalTimeHour = (23 + ((totalTime / 60) % 24));
        finalTimeMin = (60 + (totalTime % 60));
    }
    
    
    printf("The time is %2.2d%2.2d after waiting.\n", finalTimeHour, finalTimeMin); // reports the final time
    
    return 0;
}
