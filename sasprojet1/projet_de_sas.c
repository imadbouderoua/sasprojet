#include "main.h"

int id = 0;

int main() {
    id = import(id);
    printf("%d",id);
    while (1) {
        printf("                     WELCOME TO YOUR TODO                         \n"
               "        1-Ajouter une task\n"
               "        2-modifier une task\n"
               "        3-Afficher la liste de toutes les tâches\n"
               "        4-Supprimer une tâche par identifiant\n"
               "        5-Rechercher les Tâches              \n"
               "        6-Statistiques                         \n"
               "        7-Quitter\n");

        char choice;
        scanf(" %c", &choice);

        if (choice == '7') {
            // Exit the program when the user chooses to quit
            break;
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
            break;
        case '2':
            modify();
            break;
        case '3':
            printf("1-trier par nom\n2-trier par deadline\n");scanf("%d",&tchoix);
            if(tchoix == 1)
                sortElementsByTitle();
            //else if(tchoix == 2)

            printelements();
            break;
        case '4':
            delete();
            break;
        case '5':
            printf("wanna search with 1-id or 2-title\n");
            int fchoix;scanf("%d",&fchoix);
            if(fchoix == 1){
            printf("enter id\n");int sid ;scanf("%d",&sid);
            find(sid);}else if(fchoix == 2){
            printf("enter title\n");char *title =malloc(10); ;scanf("%s",title);
            findchr(title);}
            break;
        case '6':
            
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
