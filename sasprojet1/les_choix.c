#include "main.h"

extern int id;

task elements[MAX_TASKS];
char *day ;
char *year ;
char *month ;

void addlist() {
    if (id >= MAX_TASKS) {
        printf("Max number of tasks reached.\n");
        return;
    }

    if (id >= MAX_TASKS) {
        printf("Max number of tasks reached.\n");
        return;
    }
    //bring id max
    int maxID = 0;
    for (int i = 0; i < id; i++) {
        if (elements[i].id > maxID) {
            maxID = elements[i].id;
        }
    }

    elements[id].id = maxID + 1;
    
    printf("Enter task title: ");
    scanf(" %[^\n]", elements[id].title);

    printf("Enter task description: ");
    scanf(" %[^\n]", elements[id].description);
    
    while(1){
    printf("Enter task deadline (DD/M/Y/H/MIN/S): ");
scanf(" %99[^\n]%*c", elements[id].deadline);

    if(checkwe9t(elements[id].deadline)){ break;} //first check dl mochkil 1
    }
    
    while(1){
        printf("choose status :\n"
                "      do\n"
                "      doing\n"
                "      done\n");

        scanf(" %[^\n]", elements[id].status);   
        if(strcmp("do",elements[id].status) != 0 &&
            strcmp("done",elements[id].status) != 0 &&
          strcmp("doing",elements[id].status) != 0)
        {printf("invalid status\n");continue ;}else break;
    }
    id++;
    save(id);
}
void save(int id) {
    FILE *file = fopen("todo_database.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    if (id > 0) {
        for (int i = 0; i < id; i++) {
            fprintf(file, "%d,%s,%s,%s,%s,%.2lf left\n",
                    elements[i].id,
                    elements[i].title,
                    elements[i].description,
                    elements[i].deadline,
                    elements[i].status,elements[i].lefttime);
        }
    }

    fclose(file);
    printf("Tasks saved successfully.\n\n\n");
}

void printelements(){
    for(int i = 0; i < id;i++){
        printf("ID : %d TASK NAME : %s\n"
                "description :\n%s\n"
                "deadline : %s\n"
                "status %s\nleft time: %.2lf DAY(S)\n",elements[i].id,
            elements[i].title,
            elements[i].description,
            elements[i].deadline,
            elements[i].status,elements[i].lefttime);
            printf("\n");
    }
    printf("\n");
}
int import() {
    char line[1024];
    FILE *file = fopen("todo_database.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    
    int importedTasks = 0; // Initialize a variable to keep track of the number of imported tasks

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%99[^,],%99[^,],%19[^,],%lf left", // Updated sscanf format
                   &elements[id].id,
                   elements[id].title,
                   elements[id].description,
                   elements[id].deadline,
                   elements[id].status,
                   &elements[id].lefttime) == 6) { 
            id++; // Increment id for each successfully imported task
            importedTasks++;
        }
    }
    id = elements[id].id;
    fclose(file);
    return importedTasks; // Return the number of imported tasks
}
int find(int sid) {
    int found = 0;
    int i;
    for (i = 0; i < id; i++) {
        if (sid == elements[i].id) {
            printf("ID : %d TASK NAME : %s\n"
                   "description :\n%s\n"
                   "deadline : %s\n"
                   "status %s\n\n\n",
                   elements[i].id,
                   elements[i].title,
                   elements[i].description,
                   elements[i].deadline,
                   elements[i].status);
            return i;
        }
    }
    printf("       not found\n");
    return -1;
}

void findchr(char *title){
    for(int i = 0;i < id;i++ ){
            if(strcmp(title,elements[i].title) == 0){
                printf("ID : %d TASK NAME : %s\n"
                   "description :\n%s\n"
                   "deadline : %s\n"
                   "status %s\n",
                   elements[i].id,
                   elements[i].title,
                   elements[i].description,
                   elements[i].deadline,
                   elements[i].status);
                return;
            }
    }
    printf("not found\n");
}
void modify() {
    printf("Enter the person id: ");
    int id;
    scanf("%d", &id);

    int i = find(id);
    if (i == -1) {

        printf("Person with ID %d not found.\n", id);
        return;
    }
    while(1){
    printf("What do you want to modify:\n");
    printf("1. Description\n");
    printf("2. Status\n");
    printf("3. Deadline\n");

    int mchoix;
    scanf("%d", &mchoix);
    int val=0;
    switch (mchoix) {
        case 1:
            printf("Enter new description: ");
            scanf(" %[^\n]", elements[i].description);
            val = 1;
            break;
        case 2:
                     while(1){
                    printf("choose status :\n"
                            "   do\n"
                            "   doing\n"
                            "   done\n");

                    scanf(" %[^\n]", elements[i].status);   
                    if(strcmp("do",elements[i].status) != 0 &&
                        strcmp("done",elements[i].status) != 0 &&
                    strcmp("doing",elements[i].status) != 0)
                    {printf("invalid status\n");continue ;}else break;
                }
            val =1;
            break;
        case 3:
            printf("Enter new deadline (DD/M/Y/H/MIN/S): ");
            char tester[40];
            scanf(" %99[^\n]", tester);
            if(checkwe9t(tester)){strcpy(elements[i].deadline,tester);val = 1;break;}
            else{continue;}
        default:
            printf("Sorry, but we don't have that modification option yet.\n");
            break;
    }
    if(val == 1)
        break;
    }

 
    int length = calcLength();
    printf("Modified person %d information successfully.\n", id);
    save(length);
}

int calcLength() {
    return id;
}
void delete(){
    printf("enter the task id\n");
    int td;scanf("%d",&td);
    int index  = find(td);

    if (index < 0 || index >= id) {
        printf("Invalid index for deletion.\n");
        return;
    }

    for (int i = index; i < id - 1; i++) {
        elements[i] = elements[i + 1];
    }

    id--;

    save(id);
}

int checkwe9t(char deadlinee[]){
    char *p;
    p = strdup(deadlinee);
    char *day ;
    day = strtok(p,"/");
    char *month ;
    month = strtok(NULL,"/");
    char *year ;
    year = strtok(NULL,"/");
    char *hour ;
    hour = strtok(NULL,"/");
    char *minute ;
    minute = strtok(NULL,"/");
    char *second ;
    second = strtok(NULL,"/");

    
    long long int  endtime = calculateTimeLeft(atoi(year), atoi(month), atoi(day), atoi(hour), atoi(minute), atoi(second));
    //printf("%lld\n",endtime);
    if (endtime < 0)
        return 0;
    double days = (double)endtime / 86400.0;
    elements[id].lefttime = days;
    return 1;
}

void sortElementsByTitle() {
    for (int i = 0; i < id - 1; i++) {
        for (int j = 0; j < id - i - 1; j++) {
            if (strcmp(elements[j].title, elements[j + 1].title) > 0) {
                task tmp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = tmp;
            }
        }
    }
}
void sortbydeadline(){
    for (int i = 0; i < id - 1; i++) {
        for (int j = 0; j < id - i - 1; j++) {
            if (elements[j].lefttime > elements[j + 1].lefttime) {
                task tmp = elements[j];
                elements[j] = elements[j + 1];
                elements[j + 1] = tmp;
            }
        }
    }
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
        printf("The deadline has already passed.\n");
        return -1;
    }
    return timeDifference;
}
void printjust3(){
    for(int i = 0; i < id;i++){
        if(elements[i].lefttime > 3) continue;
        printf("ID : %d TASK NAME : %s\n"
                "description :\n%s\n"
                "deadline : %s\n"
                "status %s\nleft time: %.2lf DAY(S)\n",elements[i].id,
            elements[i].title,
            elements[i].description,
            elements[i].deadline,
            elements[i].status,elements[i].lefttime);
            printf("\n");
    }
    printf("\n");
}
void split_tasks(){
    int done=0;int yet= 0;
    for(int i = 0; i < id;i++){
        if(strcmp(elements[i].status,"done") == 0) 
            done++;
        else
            yet++;
    }
    int total = done + yet;
    
    if (total > 0) {
        float percentage_done = (float)done / total * 100.0;
        printf("Done: %d\nYet: %d\nPercentage of Completed Tasks: %.2f%%\n\n\n", done, yet, percentage_done);
    } else {
        printf("No tasks found.\n");
    }
}
void showdeadlineforalltasks(){
    for(int i = 0; i < id;i++){
        printf("ID : %d TASK NAME : %s\n"
                "left time: %.2lf DAY(S)\n",elements[i].id,
            elements[i].title,
            elements[i].lefttime);
            printf("\n");
    }
    printf("\n");
}



