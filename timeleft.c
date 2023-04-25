#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#define DEBUG

//Function prototypes
int calculateTimeLeft(int futureMonth, int futureDay, int futureYear);
void confirmFutureDate(int futureMonth, int futureDay, int futureYear, int totalSeconds);

int main() {
    //Get the current time
    time_t current_time = time(NULL);
    struct tm *current_tm = localtime(&current_time);

    //Output the current time
    printf("Current date and time: %04d-%02d-%02d %s %02d:%02d:%02d %s MDT\n",
           current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday,
           (current_tm->tm_wday == 0) ? "Sunday" :
           (current_tm->tm_wday == 1) ? "Monday" :
           (current_tm->tm_wday == 2) ? "Tuesday" :
           (current_tm->tm_wday == 3) ? "Wednesday" :
           (current_tm->tm_wday == 4) ? "Thursday" :
           (current_tm->tm_wday == 5) ? "Friday" : "Saturday",
           (current_tm->tm_hour % 12 == 0) ? 12 : current_tm->tm_hour % 12, current_tm->tm_min, current_tm->tm_sec,
           (current_tm->tm_hour >= 12) ? "PM" : "AM");

    //Get the target date from the user
    int futureMonth, futureDay, futureYear, totalSeconds;
    
    printf("Please enter a target date in the future (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &futureMonth, &futureDay, &futureYear);
    
    //Calculate the time remaining
    totalSeconds = calculateTimeLeft(futureMonth, futureDay, futureYear);

    #ifdef DEBUG
    printf("Total seconds: %d\n", totalSeconds);
    #endif

    //Verify seconds calculation matches remaing time calculation
    confirmFutureDate(futureMonth, futureDay, futureYear, totalSeconds);

    return 0;
}

int calculateTimeLeft(int futureMonth, int futureDay, int futureYear) {
    //Declare variables
    int days, hours, minutes, remaining_seconds;

    //Get the current time
    time_t current_time = time(NULL);
    struct tm *current_tm = localtime(&current_time);

    //Set the target time
    struct tm target_tm = {0, 0, 0, futureDay, futureMonth - 1, futureYear - 1900};
    time_t target_time = mktime(&target_tm);

    //Calculate the remaining seconds and convert them to days, hours, minutes, and seconds
    remaining_seconds = difftime(target_time, current_time);
    
    days = remaining_seconds / (24 * 3600);                 /*Days calculation*/
    remaining_seconds = remaining_seconds % (24 * 3600);
    
    hours = remaining_seconds / 3600;                       /*Hours calculation*/
    remaining_seconds %= 3600;
    
    minutes = remaining_seconds / 60;                       /*Minutes calculation*/
    remaining_seconds %= 60;

    //Output the remaining time
    printf("Until the target date: %d Days, %d Hours, %d Minutes, %d Seconds\n", days, hours, minutes, remaining_seconds);

    //Output the total number of seconds to the target date
    printf("Total number of seconds of the target date: %d seconds\n", (int)difftime(target_time, current_time));

    return (int)difftime(target_time, current_time);
}

//This function is used to answer the extra credit question
void confirmFutureDate(int futureMonth, int futureDay, int futureYear, int totalSeconds) {
    //Get the current time
    time_t current_time = time(NULL);
    struct tm *current_tm = localtime(&current_time);

    //Set the target time
    struct tm target_tm = {0, 0, 0, futureDay, futureMonth - 1, futureYear - 1900};
    time_t target_time = mktime(&target_tm);

    //Get the future date from the total number of seconds
    time_t future_time = current_time + totalSeconds;
    struct tm *future_tm = localtime(&future_time);

    #ifdef DEBUG
    printf("Future year: %d\n", futureYear);
    printf("Future month: %d\n", futureMonth);
    printf("Future day: %d\n", futureDay);
    #endif

    //Confirm if the calculated future date matches the entered future date
    if (future_tm->tm_year + 1900 == futureYear && future_tm->tm_mon + 1 == futureMonth && future_tm->tm_mday == futureDay) {
        printf("The calculated total number of seconds matches the entered future date of %04d-%02d-%02d.\n", futureYear, futureMonth, futureDay);
    } else {
        printf("The calculated total number of seconds does not match the entered future date.\n");
    }
}
