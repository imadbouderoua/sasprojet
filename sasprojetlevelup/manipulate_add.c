#include "main.h"
extern  struct user users[20];
extern int useruniqueid ;
extern task elements[MAX_TASKS]; // Declare elements as extern
extern int id; 
extern int validiticonecteur;
struct user arrayusers[20];
struct task tmpforfetch[MAX_TASKS];
struct task finalData[MAX_TASKS];
int maxID = 0;
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
    

    elements[id].id = maxID;
    maxID++;
    
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
    FILE *file;
    if(validiticonecteur == 0){
        fetchdata();
        file = fopen("todo_database.txt", "a");
    }
    else
        file = fopen("todo_database.txt", "w");
    
    
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }
    if (id > 0) {
        for (int i = 0; i < id; i++) {
            elements[id-1].forenkey = users->userid;
            fprintf(file, "%d,%s,%s,%s,%s,%.2lf left,%d\n",
                    elements[i].id,
                    elements[i].title,
                    elements[i].description,
                    elements[i].deadline,
                    elements[i].status,
                    elements[i].lefttime,
                    elements[i].forenkey); // Save the foreign key (user ID)
        }
    }

    fclose(file);
    filterdata();
    filterdata();
    printf(GREEN "Tasks saved successfully & filtreeedd.\n\n\n" RESET);
}

int import() {
    printf("%d\n",useruniqueid);
    char line[1024];
    FILE *file = fopen("todo_database.txt", "r");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return 0;
    }
    
    int importedTasks = 0; // Initialize a variable to keep track of the number of imported tasks

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%99[^,],%99[^,],%19[^,],%lf left,%d", // Updated sscanf format
                   &elements[id].id,
                   elements[id].title,
                   elements[id].description,
                   elements[id].deadline,
                   elements[id].status,
                   &elements[id].lefttime,
                   &elements[id].forenkey) == 7) { 
                    if(validiticonecteur == 0){
                    if(elements[id].forenkey != useruniqueid - 1){
                    continue; }
            }
            id++; // Increment id for each successfully imported task
            importedTasks++;
        }
    }
    
    maxID = getLastID() + 1;
    fclose(file);
    return importedTasks; // Return the number of imported tasks
}
int getLastID() {
    int lastID = -1; // Initialize lastID to an invalid value

    FILE *file = fopen("todo_database.txt", "r");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return lastID;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        int currentID;
        if (sscanf(line, "%d,", &currentID) == 1) {
            if (currentID > lastID) {
                lastID = currentID;
            }
        }
    }

    fclose(file);

    return lastID;
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
void fetchdata() {
    char line[1024];
    FILE *file = fopen("todo_database.txt", "r");

    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    int importedTasks = 0; // Initialize a variable to keep track of the number of imported tasks

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%99[^,],%99[^,],%19[^,],%lf left,%d", // Updated sscanf format
                   &tmpforfetch[id].id,
                   tmpforfetch[id].title,
                   tmpforfetch[id].description,
                   tmpforfetch[id].deadline,
                   tmpforfetch[id].status,
                   &tmpforfetch[id].lefttime,
                   &tmpforfetch[id].forenkey) == 7) {
            
            id++;
            importedTasks++;
        }
    }

    fclose(file);
    // filterdata();

    // Now, print all the scanned data back to the file
    file = fopen("todo_database.txt", "w"); // Open the file in append mode

    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    for (int i = 0; i < id; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%.2lf left,%d\n",
                tmpforfetch[i].id,
                tmpforfetch[i].title,
                tmpforfetch[i].description,
                tmpforfetch[i].deadline,
                tmpforfetch[i].status,
                tmpforfetch[i].lefttime,
                tmpforfetch[i].forenkey); // Save the foreign key (user ID)
    }
    printf("ended\n");
    fclose(file);
}
void filterdata() {
    // Create a temporary array to store all tasks from the file
    task scan_all[MAX_TASKS];
    int scannedCount = 0;

    // Read all tasks from the file and store them in scan_all
    char line[1024];
    FILE *file = fopen("todo_database.txt", "r");

    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%29[^,],%99[^,],%99[^,],%19[^,],%lf left,%d", 
                   &scan_all[scannedCount].id,
                   scan_all[scannedCount].title,
                   scan_all[scannedCount].description,
                   scan_all[scannedCount].deadline,
                   scan_all[scannedCount].status,
                   &scan_all[scannedCount].lefttime,
                   &scan_all[scannedCount].forenkey) == 7) {
            scannedCount++;
        }
    }

    fclose(file);

    // Create a temporary array to store filtered data
    task filteredData[MAX_TASKS];
    int filteredCount = 0;

    // Compare each task with all previous tasks to check for duplicates
    for (int i = 0; i < scannedCount; i++) {
        int isDuplicate = 0;

        // Check if the ID is 0
        if (scan_all[i].id == 0) {
            continue; // Skip lines with ID = 0
        }

        for (int j = 0; j < filteredCount; j++) {
            if (scan_all[i].id == filteredData[j].id ) {
                isDuplicate = 1; // Found a duplicate
                break;
            }
        }

        if (!isDuplicate) {
            // If not a duplicate, add it to the filtered data
            filteredData[filteredCount] = scan_all[i];
            filteredCount++;
        }
    }

    // Rewrite the filtered data to the file
    file = fopen("todo_database.txt", "w");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    for (int i = 0; i < filteredCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%.2lf left,%d\n",
                filteredData[i].id,
                filteredData[i].title,
                filteredData[i].description,
                filteredData[i].deadline,
                filteredData[i].status,
                filteredData[i].lefttime,
                filteredData[i].forenkey);
    }

    fclose(file);
}









