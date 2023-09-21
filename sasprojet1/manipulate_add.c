#include "main.h"

extern task elements[MAX_TASKS]; // Declare elements as extern
extern int id; 

void addlist() {
    if (id >= MAX_TASKS) {
        printf(RED "Max number of tasks reached.\n" RESET);
        return;
    }

    if (id >= MAX_TASKS) {
        printf(RED "Max number of tasks reached.\n" RESET);
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
        printf("Enter task deadline (" YELLOW "DD/M/Y/H/MIN/S" RESET "): ");

        char tester[40];
        scanf(" %99[^\n]", tester);
        char *p ;p = strdup(tester);
        if(!isValidDeadlineFormat(p)) continue;
        if(checkwe9t(tester)){
            strcpy(elements[id].deadline, tester);
            break;
        } //first check dl mochkil 1
    }
    
    while(1){
        printf("choose status:\n"
                "   " GREEN "do\n" RESET
                "   " YELLOW "doing\n" RESET
                "   " BLUE "done\n" RESET);

        scanf(" %[^\n]", elements[id].status);   
        if(strcmp("do", elements[id].status) != 0 &&
            strcmp("done", elements[id].status) != 0 &&
            strcmp("doing", elements[id].status) != 0)
        {
            printf(RED "invalid status\n" RESET);
            continue;
        }
        else break;
    }
    id++;
    save(id);
}

void modify() {
    printf("Enter the person id: ");
    int id;
    scanf("%d", &id);
    sleep(1);
    system("clear");
    int i = find(id);
    if (i == -1) {
        printf(RED "Person with ID %d not found.\n" RESET, id);
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
                    printf("choose status:\n"
                            "   " GREEN "do\n" RESET
                            "   " YELLOW "doing\n" RESET
                            "   " BLUE "done\n" RESET);

                    scanf(" %[^\n]", elements[i].status);   
                    if(strcmp("do", elements[i].status) != 0 &&
                        strcmp("done", elements[i].status) != 0 &&
                        strcmp("doing", elements[i].status) != 0)
                    {
                        printf(RED "invalid status\n" RESET);
                        continue;
                    }
                    else break;
                }
                val =1;
                break;
            case 3:
                printf("Enter new deadline (" YELLOW "DD/M/Y/H/MIN/S" RESET "): ");
                char tester[40];
                scanf(" %99[^\n]", tester);
                char *p ;p = strdup(tester);
                if(!isValidDeadlineFormat(p)){ 
                    system("clear");
                    printf(RED "not a valid date\n" RESET); 
                    continue;
                }
                if(checkwe9t(tester)){
                    strcpy(elements[i].deadline, tester);
                    val = 1;
                    break;
                }
                else{
                    system("clear");
                    printf(RED "not a valid date\n" RESET);
                    continue;
                }
            default:
                printf("Sorry, but we don't have that modification option yet.\n");
                break;
        }
        if(val == 1)
            break;
    }
 
    int length = calcLength();
    printf(GREEN "Modified person %d information successfully.\n" RESET, id);
    sleep(3);
    save(length);
}

void save(int id) {
    FILE *file = fopen("todo_database.txt", "w");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    if (id > 0) {
        for (int i = 0; i < id; i++) {
            fprintf(file, "%d,%s,%s,%s,%s,%.2lf left\n",
                    elements[i].id,
                    elements[i].title,
                    elements[i].description,
                    elements[i].deadline,
                    elements[i].status, elements[i].lefttime);
        }
    }

    fclose(file);
    printf(GREEN "Tasks saved successfully.\n\n\n" RESET);
}

int import() {
    char line[1024];
    FILE *file = fopen("todo_database.txt", "r");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
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

void printjust3() {
    int valid = 0;
    for (int i = 0; i < id; i++) {
        if (elements[i].lefttime > 3) continue;
        valid = 1;
        printf("ID : %d TASK NAME : %s\n"
               "description :\n%s\n"
               "deadline : %s\n"
               "status %s\nleft time: %.2lf DAY(S)\n", elements[i].id,
               elements[i].title,
               elements[i].description,
               elements[i].deadline,
               elements[i].status, elements[i].lefttime);
        printf("\n");
    }
    printf("\n");
    if (valid == 0) printf(RED "no tasks under 3\n" RESET);
}
