#include <stdio.h>
#include <stdlib.h>
#include <String.h>

FILE *ficVoyage;

typedef struct Date
{
    int jour;
    int mois;
    int annee;

} Date;
typedef struct Voyage
{
    char code[30];
    char description[30];
    Date dateDep;
    Date dateArriv;
    char aeroportDep[30];
    char aeroportArr[30];
    char compagnieAerienne[30];
    float prix;
    int nbrePlacesRest; // Pour les chaises restantes
} Voyage;

/**********************Ajouter un voyage**********************/
void ajoutVoyage()
{
    Voyage Voyage;
    // ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    ficVoyage = fopen("Voyages.txt", "a+");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);

    // description
    printf("Donner la description du Voyage : ");
    fflush(stdin);
    gets(Voyage.description);

    // dateDepart
    printf("Donner la date de depart sous la forme (jj/mm/aaaa) : ");
    fflush(stdin);
    scanf("%d/%d/%d", &Voyage.dateDep.jour, &Voyage.dateDep.mois, &Voyage.dateDep.annee);
    // dateArrivee
    printf("Donner la date d'arrivee sous la forme (jj/mm/aaaa) : ");
    fflush(stdin);
    scanf("%d/%d/%d||%d:%d", &Voyage.dateArriv.jour, &Voyage.dateArriv.mois, &Voyage.dateArriv.annee);

    // Aeroport Depart
    printf("Donner l'aeroport depart : ");
    fflush(stdin);
    gets(Voyage.aeroportDep);

    // Aeroport Arrivee
    printf("Donner l'aeroport d'arrive : ");
    fflush(stdin);
    gets(Voyage.aeroportArr);

    // compagnie Aerienne
    printf("Donner le nom du compagnie Aerienne : ");
    fflush(stdin);
    gets(Voyage.compagnieAerienne);

    // Prix
    printf("Donner le prix du voyage : ");
    fflush(stdin);
    scanf("%f", &Voyage.prix);

    // nombres places restantes
    printf("Donner nombre des places restantes : ");
    scanf("%d", &Voyage.nbrePlacesRest);
    char jourStr[30];
    itoa(Voyage.dateDep.jour, jourStr, 10);
    char moisStr[30];
    itoa(Voyage.dateDep.mois, moisStr, 10);
    char anneeStr[30];
    itoa(Voyage.dateDep.annee, anneeStr, 10);

    // code
    char dateStr[30];
    sprintf(dateStr, strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(jourStr, "/"), moisStr), "/"), anneeStr))))));
    sprintf(Voyage.code, strcat(strcat(dateStr, Voyage.compagnieAerienne), Voyage.aeroportDep));

    if (fprintf(ficVoyage, "%s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d\n",
                Voyage.description, Voyage.prix,
                Voyage.dateDep.jour, Voyage.dateDep.mois, Voyage.dateDep.annee,
                Voyage.dateArriv.jour, Voyage.dateArriv.mois, Voyage.dateArriv.annee,
                Voyage.aeroportDep, Voyage.aeroportArr,
                Voyage.compagnieAerienne, Voyage.nbrePlacesRest) != -1)
    {
        printf("**************** Ajout effectuee avec succees ************************\n");
        // Fermer le fichier
        fclose(ficVoyage);
    }
}
/**********************Afficher tous les voyages**********************/
void getAllVoyage()
{
    Voyage Voyage;
    // ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    ficVoyage = fopen("Voyages.txt", "a+");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    while (fscanf(ficVoyage, "%s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d",
                  Voyage.description, &Voyage.prix,
                  &Voyage.dateDep.jour, &Voyage.dateDep.mois, &Voyage.dateDep.annee, 
                  &Voyage.dateArriv.jour, &Voyage.dateArriv.mois, &Voyage.dateArriv.annee,
                  Voyage.aeroportDep, Voyage.aeroportArr,
                  Voyage.compagnieAerienne, &Voyage.nbrePlacesRest) != -1)
    {

        printf("%s\n", Voyage.description);
    }
    fclose(ficVoyage);
}
