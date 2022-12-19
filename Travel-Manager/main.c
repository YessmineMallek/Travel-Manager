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

        while (choix != 7)
        {

            do
            {
                printf("\n\t\tVous etes un administrateur.\n");
                printf("\nGESTION DES Voyages\n");
                printf("\n* 1 *\tAjouter une Voyage");
                printf("\n* 2 *\tModifier les coordonnees d'une Voyage");
                printf("\n* 3 *\tSupprimer une Voyage");
                printf("\n* 4 *\tRechercher une Voyage");
                printf("\n* 5 *\tAfficher toutes les Voyages");
                printf("\n* 6 *\tAfficher la description des Voyages");
                printf("\n* 7 *\tQuitter le programme");
                printf("\n\nSaisissez votre choix : ");
                fflush(stdin);
                scanf("%d", &choix);
            } while ((choix < 1) || (choix > 7));
            switch (choix)
            {
            case 1:
                system("cls");
                ajoutVoyage(ficVoyage);
                break;
            case 2:
                system("cls");
                int nbre = nbreVoyages();
                int choix;
                getAll();
                do
                {
                    printf("Saisir le code de voyage a modifier : ");
                    scanf("%d", &choix);
                    modifiderVoyage(choix);
                } while (choix<=0 ||choix>nbre );
               

                break;
            case 3:
                system("cls");
                supprimerVoyage();
                break;

            case 5:
                system("cls");
                getAll();
                break;
            case 6:
                system("cls");
                printf("\t\tNos meilleurs offres pour les vacances\n");
                getDescriptionVoyages();
                break;
            }
        }
    }
    else
    {
        while (choix != 3)
        {
            printf("\v\vVotre voyage commence maintenant.\n");
            do
            {
                printf("\n* 1 *\tRechercher des Voyages par dates de depart ,date d'arrivee");
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
                getByDates();

            case 2:
                printf("\t\tNos meilleurs offres pour les vacances\n");
                getDescriptionVoyages();
                break;
            }
        }
    }

    return 0;
}
