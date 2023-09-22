#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 1000
//colors 
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define PURPLE "\x1B[35m"

typedef struct task {
    int id;
    char title[30];
    char description[100];
    char deadline[20];
    char status[20];
    double lefttime;
    int forenkey;
} task;


//optional
typedef struct user{
    int userid ;
    char full_name[40];
    char email[100];
    struct task *linkedtask;
}user;

void traiter_choix(int choix);
void addlist();
void printelements();
int import();
int find(int sid);
void findchr(char *);
void save(int id);
int calcLength();
void modify();
void delete();
int checkwe9t(char deadlinee[20]);
void sortElementsByTitle();
long long calc_deadline(int y, int m, int d);
long long calculateTimeLeft(int year, int month, int day, int hour, int minute, int second);
double secondsToDays(long long seconds);
void sortbydeadline();
void printjust3();
void split_tasks();
void showdeadlineforalltasks();
int isValidDeadlineFormat(const char *);

//log func
void chekwho();
void login();
void saveloger();
void readusersdoc();
void logindeja();
int checkuserpresence();
void filterdata();
void fetchdata();
void filterdata();
int getLastID();
#endif // MAIN_H
