#include "main.h"
int validiticonecteur;
int useruniqueid = 1; // Initialize useruniqueid to 1

struct user users;

void login() {
    readusersdoc();
    char incheked_name[40], incheked_email[100];

    printf(GREEN "Welcome to our app\n" RESET);
    printf("Please enter your full name: ");
    scanf(" %[^\n]", incheked_name);
    strcpy(users.full_name, incheked_name);

    printf("Enter your email: ");
    scanf(" %[^\n]", incheked_email);
    strcpy(users.email, incheked_email);

    users.userid = useruniqueid; // Set the user ID based on the current value of useruniqueid

    saveloger();
    useruniqueid++; // Increment useruniqueid for the next user
}

void saveloger() {
    FILE *file = fopen("users_database.txt", "a");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    fprintf(file, "%d,%s,%s\n",
            users.userid,
            users.full_name,
            users.email);

    fclose(file);
    printf(GREEN "User saved successfully.\n\n\n" RESET);
}
int paswtime = 0;
void chekwho() {
    if(paswtime == 3){
        printf(RED "3 times wrong try in 60 s\n" RESET);
        sleep(60);
        paswtime = 0;
        }
    printf(PURPLE "1 - Admin\n2 - User\n3 - quit" RESET);
    int i;
    scanf("%d", &i);
    if (i == 1){
        printf("enter password :\n");
        char password[20];scanf("%s",password);
        if(strcmp(password,"jesuisadmin") != 0){
            paswtime++;
            system("clear");
            printf(RED "password invalide\n try again\n" RESET);
            chekwho();
            }

        validiticonecteur = 1;return;}
    else if (i == 2) {
        printf(PURPLE "1 - Login\n2 - Subscribe\n" RESET);
        int j;
        scanf("%d", &j);
        if (j == 1)
            logindeja();
        else if (j == 2)
            login();
        else{

            printf(RED "Enter a valid choice.\n" RESET);
            sleep(2);
            system("./a.out");
            }
    }else if(i == 3)
        exit(0);
     else{
        printf(RED "Please choose just 1 of the following.\n" RESET);
        sleep(2);
        system("./a.out");
        }
}

void readusersdoc() {
    char usline[1024];
    FILE *file = fopen("users_database.txt", "r");
    if (file == NULL) {
        perror(RED "Error opening file\n" RESET);
        return;
    }

    int maxUserID = 0; // Initialize maxUserID to find the highest user ID

    while (fgets(usline, sizeof(usline), file)) {
        int userid;
        sscanf(usline, "%d,%*[^,],%*[^,]", &userid); // Extract only the user ID
        if (userid > maxUserID) {
            maxUserID = userid;
        }
    }

    useruniqueid = maxUserID + 1; // Set useruniqueid to the next available user ID
    fclose(file);
}

void logindeja() {
    int scanedid;
    printf("Please enter your ID: \n");
    scanf("%d", &scanedid);
    //chekwho();
    if (!checkuserpresence(scanedid)) {
        
        
        printf(RED "You are not in our servers. You can join us.\n" RESET);
        sleep(3);
        system("./a.out");
    }
    users.userid = scanedid;
    useruniqueid = scanedid + 1;
}

int checkuserpresence(int r) {
    char cline[1024];
    FILE *file = fopen("users_database.txt", "r");
    if (file == NULL) {
        perror(RED "Error opening file" RESET);
        return 0;
    }
    while (fgets(cline, sizeof(cline), file)) {
        int userid;
        sscanf(cline, "%d,%*[^,],%*[^,]", &userid); // Extract only the user ID
        if (userid == r) {
            printf(GREEN "WELCOME\n" RESET);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
