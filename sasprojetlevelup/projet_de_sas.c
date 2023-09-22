#include "main.h"
extern  struct user users[20];
extern int useruniqueid ;
int id = 0;

int main() {
    system("clear");
    chekwho();
    id = import(id);
    printf("importing %d\n", id);
    sleep(1);
     system("clear");
    while (1) {
        

        printf(GREEN "                     WELCOME TO YOUR TODO                         \n\n\n" RESET
               "        " CYAN "1-Ajouter une task\n" RESET
               "        " CYAN "2-modifier une task\n" RESET
               "        " CYAN "3-Afficher la liste de toutes les tâches\n" RESET
               "        " CYAN "4-Supprimer une tâche par identifiant\n" RESET
               "        " CYAN "5-Rechercher les Tâches              \n" RESET
               "        " CYAN "6-Statistiques\n " RESET
               "        " CYAN "7-Clear screen                 \n" RESET
               "        " CYAN "8-Quitter\n" RESET
                "        " CYAN "0-disconect\n" RESET);

        char choice;
        scanf(" %c", &choice);

        if (choice == '8') 
            break;
        else if (choice == '7'){
            system("clear");
            continue;
        }else if(choice == '0'){
            system("clear");
            printf("disconecting.....\n");
            
            sleep(1);
            system("clear");
            system("./a.out");

            chekwho();
            
            }

        traiter_choix(choice);
    }

    return 0;
}

void traiter_choix(int choix) {
    int tchoix;
    switch (choix) {
        case '1':
        
            addlist();
            sleep(2);
            system("clear");
            break;
        case '2':
            modify();
            system("clear");
            break;
        case '3':
            printf(MAGENTA "1-trier par nom\n2-trier par deadline\n3-to show only 3days left tasks\n" RESET);scanf("%d",&tchoix);
            if(tchoix == 1)
                sortElementsByTitle();
            else if(tchoix == 2)
                sortbydeadline();
            else if(tchoix ==  3){
                printjust3();
                break;
            }else{
                break;
            }

            printelements();
            break;
        case '4':
            delete();
            
            
            break;
        case '5':
            printf(MAGENTA "wanna search with 1-id or 2-title\n" RESET);
            int fchoix;scanf("%d",&fchoix);
            if(fchoix == 1){
            printf("enter id\n");int sid ;scanf("%d",&sid);
            find(sid);}else if(fchoix == 2){
            printf("enter title\n");char *title =malloc(10); ;scanf("%s",title);
            findchr(title);}
            break;
        case '6':
            printf(MAGENTA "1-show stats\n2-SEE timeleft for every task\n3-show only 3days deadline tasks\n" RESET);
            int schoix;scanf("%d",&schoix);
            if(schoix == 1){
                system("clear");
                printf("            STATS\n");
                printf("TOTAL TASKS %d",id);
                split_tasks();
            }else if(schoix == 2){
                 system("clear");
                 showdeadlineforalltasks();
            }else if(schoix == 3){
                 system("clear");
                    printjust3();
            }else {
                printf(RED "sorry we dont have that yet\n"RESET);
            }
            break;
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            sleep(1);
            system("clear");
    }
}
