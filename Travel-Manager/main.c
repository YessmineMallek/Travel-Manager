#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "user.h"
#include "Voyage.h"
#include "reservation.h"

int main(int argc, char **argv)
{

    int choix = 0;
    char username[30] = "";
    char password[30] = "";
    int choix1, auth;
    user newUser;
    int res, idVoy;
    int nbreVoyages = idVoyage();
    do
    {
        printf("\t\tBienvenue\n");
        printf("* 1 *:Se connecter !\n");
        printf("* 2 *:S'inscrire !\n");
        scanf("%d", &choix1);
    } while (choix1 != 1 && choix1 != 2);

    do
    {
        system("cls");
        if (choix1 == 2)
        {

            ajouterUtilisateur(&newUser);
            sprintf(username, newUser.nomUtilisateur);
            sprintf(password, newUser.motDePasse);
        }
        if (choix1 == 1)
        {
            printf("-------------------------------------------\n");
            printf("\t\t\tSe connectez ! \n");
            printf("-------------------------------------------\n");

            printf("Entrez votre Nom d'utilisateur :");
            fflush(stdin);
            scanf("%s", username);
            printf("Entrez votre mot de passe :");
            fflush(stdin);
            scanf("%s", password);
        }

        auth = authentifier(username, password);

        if (auth == 1) // admin
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
                    printf("\n* 4 *\tAfficher les reservations disponibles");
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
                    int nbre = idVoyage();
                    Voyage voyage;
                    int codeAmodifier, choixAmodifier;
                    getAll();
                    printf("--------------------------------%d", nbre);
                    do
                    {
                        printf("Saisir le code de voyage a modifier : ");
                        scanf("%d", &codeAmodifier);
                    } while (codeAmodifier <= 0 || codeAmodifier > nbre);

                    int existe = getVoyageById(codeAmodifier, &voyage);

                    if (existe == 1)
                    {
                        do
                        {
                            printf("\nModification d'un voyage\n");
                            printf("\n* 1 *\tModifier du description");
                            printf("\n* 2 *\tModifier les dates du Voyage");
                            printf("\n* 3 *\tModifier l'aeroport du depart ou l'aeroport d'arrivee");
                            printf("\n* 4 *\tModifier la compagnie aerienne");
                            printf("\n* 5 *\tModifier le prix du voyage");
                            printf("\n* 6 *\tModifier le nombre des places restantes");
                            printf("\n\nSaisissez votre choix : ");
                            fflush(stdin);
                            scanf("%d", &choixAmodifier);

                        } while ((choixAmodifier < 1) || (choixAmodifier > 6));
                        modifiderVoyage(codeAmodifier, choixAmodifier);
                    }
                    else
                    {
                        printf("Ce voyage n'existe pas \n");
                    }

                    break;
                case 3:
                    system("cls");
                    supprimerVoyage();
                    break;
                case 4:
                    system("cls");
                    afficherReservations();
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
        if (auth == 0)
        {
            system("cls");

            while (choix != 3)
            {
                printf("\n\t\tVotre voyage commence maintenant.\n");
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
                    do
                    {
                        printf("\t\tVoulez-vous reserver?\n* 1 *:oui\n* 2 *:non\n");
                        printf("Votre reponse : ");
                        scanf("%d", &res);
                    } while (res != 1 && res != 2);
                    if (res == 1)
                    {
                        do
                        {
                            printf("Entrer le numero de voyage : ");
                            scanf("%d", &idVoy);
                        } while (idVoy > nbreVoyages);
                        ajouterReservation(username, idVoy);
                    }
                    break;

                case 2:
                    system("cls");
                    printf("\t\tNos meilleurs offres pour les vacances\n");
                    getDescriptionVoyages();
                    do
                    {
                        printf("\t\tVoulez-vous reserver?\n* 1 *:oui\n* 2 *:non\n");
                        printf("Votre reponse : ");
                        scanf("%d", &res);
                    } while (res != 1 && res != 2);
                    if (res == 1)
                    {
                        do
                        {
                            printf("Entrer le numero de voyage : ");
                            scanf("%d", &idVoy);
                        } while (idVoy > nbreVoyages);
                        ajouterReservation(username, idVoy);
                    }

                    break;
                }
            }
        }
        if (auth == -2)
        {
            printf("Mot de passe incorrect!!\n");
        }
    } while (auth == -1 || auth == -2);

    return 0;
}
