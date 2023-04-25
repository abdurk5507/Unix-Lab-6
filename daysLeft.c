#include <stdio.h>
#include <time.h>
#include <math.h>

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

void daysLeft(){
    //Declare struct to hold multiple dates
    struct target_date targets[] = {
        {TARGET_1_DAY, TARGET_1_MONTH, TARGET_1_YEAR},
        {TARGET_2_DAY, TARGET_2_MONTH, TARGET_2_YEAR}
    };

    //Determines # of iterations in for loop
    int num_targets = sizeof(targets) / sizeof(targets[0]);

    for (int i = 0; i < num_targets; i++) {
        //Used to display sequence
        count++;

        //Get the current time
        time_t current_time = time(NULL);
        struct tm *current_tm = localtime(&current_time);

        //Calculate the remaining seconds to Christmas day 2023
        struct tm target_tm = {0, 0, 0, targets[i].day, targets[i].month - 1, targets[i].year - 1900};
        time_t target_time = mktime(&target_tm);
        double remaining_seconds = difftime(target_time, current_time);

        //Calculate the remaining days to target date
        int days = (int) floor(remaining_seconds / (24 * 3600));

        //Output the sequence number, current time, and remaining days to Christmas day 2023
        printf("%d. Current date and time: %04d-%02d-%02d %02d:%02d:%02d\n", count, current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);
        
        //Output date, time, days remaining, and seconds remaining
        if(count % 2 == 0){
            printf("   Days until Christmas Day 2023: %d\n", days);
            printf("   Christmas Day is in %d seconds\n\n", (int)remaining_seconds);
        }
        else{
            printf("   Days until Independence Day 2023: %d\n", days);
            printf("   Independence Day is in %d seconds\n\n", (int)remaining_seconds);
        }
        
    }
}

int main() {
    daysLeft();
    //daysLeft();
    //daysLeft();
    //daysLeft();
    //daysLeft();
}
