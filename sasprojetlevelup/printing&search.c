#include "main.h"
extern int validiticonecteur;
extern task elements[MAX_TASKS]; // Declare elements as extern
extern int id; 
extern  struct user arrayusers[20];
extern int useruniqueid ;
void printelements() {
    
    for(int i = 0; i < id; i++) {
        printf("ID : " CYAN "%d\n" RESET "TASK NAME : " GREEN "%s\n" RESET
               "description :\n%s\n"
               "deadline : " YELLOW "%s\n" RESET
               "status " MAGENTA "%s\n" RESET "left time: " BLUE "%.2lf DAY(S)\n" RESET, elements[i].id,
               elements[i].title,
               elements[i].description,
               elements[i].deadline,
               elements[i].status, elements[i].lefttime);
        printf("\n");
    }
    printf("\n");
}

int find(int sid) {
    int found = 0;
    int i;
    for (i = 0; i < id; i++) {
        if (sid == elements[i].id) {
            system("clear");
            printf("ID : " CYAN "%d\n" RESET "TASK NAME : " GREEN "%s\n" RESET
                   "description :\n%s\n"
                   "deadline : " YELLOW "%s\n" RESET
                   "status " MAGENTA "%s\n" RESET "\n\n\n",
                   elements[i].id,
                   elements[i].title,
                   elements[i].description,
                   elements[i].deadline,
                   elements[i].status);
            return i;
        }
    }
    system("clear");
    printf(RED "       not found\n" RESET);

    return -1;
}

void findchr(char *title) {
    for(int i = 0; i < id; i++) {
        if(strcmp(title, elements[i].title) == 0) {
            system("clear");
            printf("ID : " CYAN "%d\n" RESET "TASK NAME : " GREEN "%s\n" RESET
                   "description :\n%s\n"
                   "deadline : " YELLOW "%s\n" RESET
                   "status " MAGENTA "%s\n" RESET,
                   elements[i].id,
                   elements[i].title,
                   elements[i].description,
                   elements[i].deadline,
                   elements[i].status);
            return;
        }
    }
    system("clear");
    printf(RED "not found\n" RESET);
}
