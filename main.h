#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100

typedef struct task {
    int id;
    char title[30];
    char description[100];
    char deadline[20];
    char status[20];
} task;

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
#endif // MAIN_H
