#include <stdio.h>
#include <stdlib.h>
#include "Voyage.h"
#include <String.h>

int main()
{

    int choix = 0;
    char username[30];
    char password[30];

    printf("\t\tBienvenue\n");
    printf("Veuillez se connectez !\n");
    printf("Entrez votre Nom d'utilisateur :");
    fflush(stdin);
    scanf("%s", username);
    printf("Entrez votre mot de passe :");
    fflush(stdin);
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        system("cls");

        while (choix != 6)
        {

            do
            {

                printf("\t\tVous etes un administrateur.\n");
                printf("\nGESTION DES Voyages\n");
                printf("\n* 1 *\tAjouter une Voyage");
                printf("\n* 2 *\tModifier les coordonnees d'une Voyage");
                printf("\n* 3 *\tSupprimer une Voyage");
                printf("\n* 4 *\tRechercher une Voyage");
                printf("\n* 5 *\tAfficher toutes les Voyages");
                printf("\n* 6 *\tQuitter le programme");
                printf("\n\nSaisissez votre choix : ");
                fflush(stdin);
                scanf("%d", &choix);
            } while ((choix < 1) || (choix > 6));
            printf("votree choix est egale a %d", choix);
            switch (choix)
            {
            case 1:
                system("cls");
                ajoutVoyage(ficVoyage);
                break;
            case 5:
                system("cls");
                getAllVoyage();
                break;
            }
        }
    }
    else
    {
        while (choix != 6)
        {
            system("cls");
            printf("\v\vVotre voyage commence maintenant.\n");
            do
            {
                printf("\n* 1 *\tRechercher une Voyage");
                printf("\n* 2 *\tAfficher toutes les Voyages");
                printf("\n* 3 *\tQuitter le programme");
                printf("\n\nSaisissez votre choix : ");
                fflush(stdin);
                scanf("%d", &choix);
            } while ((choix < 1) || (choix > 3));
            switch (choix)
            {
            case 1:
                system("cls");
                getAllVoyage();
                break;
            }
        }
    }

    return 0;
}
