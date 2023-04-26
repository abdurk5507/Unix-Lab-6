#include <stdio.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

//Independence Day
#define TARGET_1_DAY 4
#define TARGET_1_MONTH 7
#define TARGET_1_YEAR 2023

//Christmas Day
#define TARGET_2_DAY 25
#define TARGET_2_MONTH 12
#define TARGET_2_YEAR 2023

struct target_date {
    int day;
    int month;
    int year;
};

//Used for sequence #
static int count = 0;

//Count # of signals
static int interrupt_count = 0;

void daysLeft(int flag){
    //Declare struct to hold multiple dates
    struct target_date targets[] = {
        {TARGET_1_DAY, TARGET_1_MONTH, TARGET_1_YEAR},
        {TARGET_2_DAY, TARGET_2_MONTH, TARGET_2_YEAR}
    };

    //Determines # of iterations in for loop
    //int num_targets = sizeof(targets) / sizeof(targets[0]);

    //for (int i = 0; i < num_targets; i++) {
        //Used to display sequence
        count++;

        //Get the current time
        time_t current_time = time(NULL);
        struct tm *current_tm = localtime(&current_time);

        //Calculate the remaining seconds to Christmas day 2023
        struct tm target_tm = {0, 0, 0, targets[flag].day, targets[flag].month - 1, targets[flag].year - 1900};
        time_t target_time = mktime(&target_tm);
        double remaining_seconds = difftime(target_time, current_time);

        //Calculate the remaining days to target date
        int days = (int) floor(remaining_seconds / (24 * 3600));

        //Output the sequence number, current time, and remaining days to Christmas day 2023
        printf("%d. Current date and time: %04d-%02d-%02d %02d:%02d:%02d\n", count, current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);
        
        //Output date, time, days remaining, and seconds remaining
        if(flag == 1){
            printf("   Days until Christmas Day 2023: %d\n", days);
            printf("   Christmas Day is in %d seconds\n\n", (int)remaining_seconds);
        }
        else if (flag == 0){
            printf("   Days until Independence Day 2023: %d\n", days);
            printf("   Independence Day is in %d seconds\n\n", (int)remaining_seconds);
        }
        
    //}
}

void signal_handler(int signum){
    interrupt_count++;

    if (interrupt_count <= 3) {
        //Prompt the user to quit or continue
        char choice;
        printf("Do you want to quit? (y/n) ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            //User chose to quit
            exit(1);
        } else if (choice == 'n' || choice == 'N') {
            //User chose to continue
            daysLeft(0); //add a flag variable as an input and put that in the function
        } else {
            //Invalid input, repeat the question
            signal_handler(signum);
        }
    } else {
        //Reset the signal handler to the default behavior
        signal(SIGINT, SIG_DFL);
        printf("\nCTRL-C pressed more than 3 times. Resetting to default behavior.\n");
    }
    
    printf("\nInterrupt signal received.\n");
    // Call the daysLeft() function to display the number of days till the target date
    daysLeft(0);
}

int main() {
    //int flag = 0;

    // Register the signal handler function for SIGINT signal
    for(;;){
        signal(SIGINT, signal_handler);
    }
   

    //daysLeft(0);
    //daysLeft(1);
    //daysLeft();
    //daysLeft();
    //daysLeft();
}
