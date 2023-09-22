#include "main.h"
extern  struct user users[20];
extern int useruniqueid ;
extern int id;
task elements[MAX_TASKS];

int calcLength() {
    return id;
}

void delete() {
    printf("Enter the task ID: ");
    int td;
    scanf("%d", &td);
    system("clear");
    int index = find(td);

    if (index < 0 || index >= id) {
        printf(RED "Invalid index for deletion.\n" RESET);
        sleep(1);
        return;
    }

    for (int i = index; i < id - 1; i++) {
        elements[i] = elements[i + 1];
    }

    id--;
    printf(GREEN "TASK DELETED & OTHER " RESET);
    sleep(2);
    system("clear");
    save(id);
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

void sortbydeadline() {
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

void split_tasks() {
    int done = 0;
    int yet = 0;
    for (int i = 0; i < id; i++) {
        if (strcmp(elements[i].status, "done") == 0)
            done++;
        else
            yet++;
    }
    int total = done + yet;

    if (total > 0) {
        float percentage_done = (float)done / total * 100.0;
        printf("\nDone: " GREEN "%d\n" RESET "Yet: " BLUE "%d\n" RESET "Percentage of Completed Tasks: " YELLOW "%.2f%%\n\n\n" RESET, done, yet, percentage_done);
    } else {
        printf(RED "No tasks found.\n" RESET);
    }
}

void showdeadlineforalltasks() {
    for (int i = 0; i < id; i++) {
        printf("ID : %d TASK NAME : %s\n"
               "left time: %.2lf DAY(S)\n", elements[i].id,
               elements[i].title,
               elements[i].lefttime);
        printf("\n");
    }
    printf("\n");
}

int isValidDeadlineFormat(const char *input) {
    int count = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '/') {
            count++;
        }
    }
    if (count != 5) {
        return 0;
    }

    char *tokens[6];
    char *token = strtok((char *)input, "/");
    int i = 0;
    while (token != NULL && i < 6) {
        tokens[i++] = token;
        token = strtok(NULL, "/");
    }

    for (i = 0; i < 6; i++) {
        if (tokens[i] == NULL) {
            return 0;
        }
        char *endptr;
        strtol(tokens[i], &endptr, 10);
        if (*endptr != '\0') {
            return 0; // Not a valid integer
        }
    }
    return 1;
}
