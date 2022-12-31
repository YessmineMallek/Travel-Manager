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
    char ch;
    int choix1, auth;
    user newUser;
    int res, idVoy;
    int nbreVoyages = idVoyage();
    do
    {
        do
        {
            printf("----------------------------------------------------------------------\n");
            printf("\t\t\tBienvenue\n");
            printf("----------------------------------------------------------------------\n");
            printf("* 1 *:Se connecter !\t\t* 2 *:S'inscrire !\n");
            printf("Saisir votre choix : ");
            scanf("%d", &choix1);
        } while (choix1 != 1 && choix1 != 2);

        do
        {
            if (choix1 == 2)
            {

                ajouterUtilisateur(&newUser);
                sprintf(username, newUser.nomUtilisateur);
                sprintf(password, newUser.motDePasse);
            }
            if (choix1 == 1)
            {

                printf("\n-------------------------------------------\n");
                printf("\t\t\tSe connectez ! \n");
                printf("\n-------------------------------------------\n");

                printf("Entrez votre Nom d'utilisateur :");
                fflush(stdin);
                scanf("%s", username);
                // printf("Entrez votre mot de passe :");
                int index = 0;
                printf("Entrez votre mot de passe : ");
                fflush(stdin);
                while ((ch = _getch()) != 13)
                {
                    password[index] = ch;
                    index++;
                }
                password[index] = '\0';
            }

            auth = authentifier(username, password);

            if (auth == 1) // admin
            {
                while (choix != 6)
                {

                    do
                    {
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\n\t\tVous etes un administrateur.\n");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\n* 1 *\tAjouter une Voyage");
                        printf("\n* 2 *\tModifier les coordonnees d'une Voyage");
                        printf("\n* 3 *\tSupprimer une Voyage");
                        printf("\n* 4 *\tAfficher les reservations disponibles");
                        printf("\n* 5 *\tAfficher la description des Voyages");
                        printf("\n* 6 *\tSe deconnecter");
                        printf("\n\nSaisissez votre choix : ");
                        fflush(stdin);
                        scanf("%d", &choix);
                    } while ((choix < 1) || (choix > 6));
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
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\tModifier Voyage!");
                        getDescriptionVoyages();
                        do
                        {
                            printf("\n----------------------------------------------------------------------\n");

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
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\tSupprimer Voyage!");
                        supprimerVoyage();
                        break;
                    case 4:
                        system("cls");
                        afficherReservations();
                        break;
                    case 5:
                        system("cls");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\tNos meilleurs offres pour les vacances\n");

                        getDescriptionVoyages();
                        break;
                    case 6:
                        system("cls");

                        break;
                    }
                }
            }
            if (auth == 0)
            {

                while (choix != 6)
                {
                    printf("\n----------------------------------------------------------------------\n");
                    printf("\n\t\t\tVotre voyage commence maintenant.\n");
                    printf("----------------------------------------------------------------------\n");
                    do
                    {
                        printf("\n* 1 *\tAfficher toutes les Voyages");
                        printf("\n* 2 *\tRechercher des Voyages par dates de depart ,date d'arrivee");
                        printf("\n* 3 *\tChercher par ville depart");
                        printf("\n* 4 *\tChercher par ville Arrivee");
                        printf("\n* 5 *\tChercher par mois ,jour,annee");
                        printf("\n* 6 *\tSe deconnecter");
                        printf("\n\nSaisissez votre choix : ");
                        fflush(stdin);
                        scanf("%d", &choix);
                    } while ((choix < 1) || (choix > 6));
                    switch (choix)
                    {

                    case 1:
                        system("cls");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\tNos meilleurs offres pour les vacances\n");
                        printf("\n----------------------------------------------------------------------\n");

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
                            } while (!(idVoy <= nbreVoyages));
                            ajouterReservation(username, idVoy);
                        }

                        break;
                    case 2:
                        system("cls");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\t\tChercher par les dates\n");
                        printf("\n----------------------------------------------------------------------\n");
                        getByDates(username);

                        break;
                    case 3:
                        system("cls");
                        char depart[30];
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\t\tChercher par ville de depart\n");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("Veuiller saisir la ville de depart : ");

                        fflush(stdin);
                        gets(depart);
                        getByVilleDepart(depart);
                        break;
                    case 4:
                        system("cls");
                        char arrivee[30];
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\t\tChercher par ville d'arrivee\n");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("Veuiller saisir la ville d'arrivee : ");

                        fflush(stdin);
                        gets(arrivee);
                        getByVilleArrivee(arrivee);
                        break;

                    case 5:
                        system("cls");
                        int critere;
                        printf("\n----------------------------------------------------------------------\n");
                        printf("\t\t\tChercher Voyage\n");
                        printf("\n----------------------------------------------------------------------\n");
                        printf("* 1 *:Date depart\n* 2 *:Date Arrivee\n");
                        printf("----------------------------------------------------------------------\n");
                        printf("Saisir votre choix : ");
                        scanf("%d", &critere);
                        switch (critere)
                        {
                        case 1:
                            system("cls");
                            int choice11;
                            printf("\n-----------------------------Date Depart-----------------------------------------\n");
                            printf("* 1 *:Par jour\n* 2 *:Par mois\n* 3 *:Par annee\n* 4 *:Annuler\n ");
                            printf("\n----------------------------------------------------------------------\n");
                            printf("Votre choix : ");
                            scanf("%d", &choice11);
                            switch (choice11)
                            {
                            case 1:
                                int j;
                                printf("Saisir le numero du jour : ");
                                scanf("%d", &j);
                                getDepartByJour(j);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }

                                break;
                            case 2:
                                int m;
                                printf("Saisir le numero du mois : ");
                                scanf("%d", &m);
                                getDepartByMois(m);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }
                                break;
                            case 3:
                                int a;
                                printf("Saisir l'annee : ");
                                scanf("%d", &a);
                                getDepartByAnnee(a);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }
                                break;

                            default:
                                break;
                            }
                            break;

                        case 2:
                            system("cls");
                            int choice12;
                            printf("\n-----------------------------Date Arrivee-----------------------------------------\n");
                            printf("* 1 *:Par jour\n* 2 *:Par mois\n* 3 *:Par annee\n* 4 *:Annuler\n ");
                            printf("\n----------------------------------------------------------------------\n");
                            printf("Votre choix : ");
                            scanf("%d", &choice12);
                            switch (choice12)
                            {
                            case 1:
                                int j;
                                printf("Saisir le numero du jour : ");
                                scanf("%d", &j);
                                getArriveeByJour(j);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }
                                break;
                            case 2:
                                int m;
                                printf("Saisir le numero du mois : ");
                                scanf("%d", &m);
                                getArriveeByMois(m);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }
                                break;
                            case 3:
                                int a;
                                printf("Saisir l'annee : ");
                                scanf("%d", &a);
                                getArriveeByAnnee(a);
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
                                    } while (!(idVoy <= nbreVoyages));
                                    ajouterReservation(username, idVoy);
                                }
                                break;
                            }

                            break;
                        }

                    case 6:
                        system("cls");

                        break;
                    }
                }
            }
            if (auth == -2)
            {
                printf("\nMot de passe incorrect!!\n");
            }

        } while (auth == -1 || auth == -2);

    } while (choix1 == 1 || choix1 == 2);
    return 0;
}
