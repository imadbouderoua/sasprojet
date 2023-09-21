#include "main.h"

extern task elements[MAX_TASKS];
extern int id;

char *day;
char *year;
char *month;

int checkwe9t(char deadlinee[]) {
    char *p;
    p = strdup(deadlinee);
    char *day;
    day = strtok(p, "/");
    char *month;
    month = strtok(NULL, "/");
    char *year;
    year = strtok(NULL, "/");
    char *hour;
    hour = strtok(NULL, "/");
    char *minute;
    minute = strtok(NULL, "/");
    char *second;
    second = strtok(NULL, "/");

    long long int endtime = calculateTimeLeft(atoi(year), atoi(month), atoi(day), atoi(hour), atoi(minute), atoi(second));
    //printf("%lld\n",endtime);
    if (endtime < 0) {
        printf(RED "The deadline has already passed.\n" RESET);
        return 0;
    }
    double days = (double)endtime / 86400.0;
    elements[id].lefttime = days;
    return 1;
}

long long calculateTimeLeft(int year, int month, int day, int hour, int minute, int second) {
    // Get the current time
    time_t currentTime;
    struct tm *currentTimeInfo;
    time(&currentTime);
    currentTimeInfo = localtime(&currentTime);

    // Create a tm structure for the deadline time
    struct tm deadlineTime;
    deadlineTime.tm_year = year - 1900; // Adjust year
    deadlineTime.tm_mon = month - 1;   // Adjust month
    deadlineTime.tm_mday = day;
    deadlineTime.tm_hour = hour;
    deadlineTime.tm_min = minute;
    deadlineTime.tm_sec = second;

    // Calculate the time difference
    time_t currentTimestamp = mktime(currentTimeInfo);
    time_t deadlineTimestamp = mktime(&deadlineTime);
    long long timeDifference = (long long)difftime(deadlineTimestamp, currentTimestamp);
    if (timeDifference <= 0) {
        printf(RED "The deadline has already passed.\n" RESET);
        return -1;
    }
    return timeDifference;
}
