#include <stdio.h>
#include <stdlib.h>
#include <String.h>

FILE *ficVoyage;
FILE *ficArchive;
FILE *nv;

typedef struct Date
{
    int jour;
    int mois;
    int annee;

} Date;
typedef struct Voyage
{
    int code;
    char description[255];
    Date dateDep;
    Date dateArriv;
    char aeroportDep[30];
    char aeroportArr[30];
    char compagnieAerienne[30];
    float prix;
    int nbrePlacesRest; // Pour les chaises restantes
} Voyage;
int calculerDuree(Date dateDep, Date dateArriv)
{
    int duree = -1;
    int dateDepJour;
    int dateArrJour;
    dateDepJour = dateDep.annee * 365 + dateDep.mois * 30 + dateDep.jour;
    dateArrJour = dateArriv.annee * 365 + dateArriv.mois * 30 + dateArriv.jour;
    duree = dateArrJour - dateDepJour;
    return duree;
}
int nbreVoyages()
{
    int nbre = 0;
    char line[255];
    ficVoyage = fopen("Voyages.txt", "r");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    while (fgets(line, 254, ficVoyage) != NULL)
    {
        nbre++;
    }
    return nbre;
    fclose(ficVoyage);
}
int testSiFichierVide()
{
    int caracterePremier = 0;
    ficVoyage = fopen("Voyages.txt", "r");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    // On lit le prmeier caractère du fichier
    caracterePremier = fgetc(ficVoyage);
    if (caracterePremier == EOF)
    {
        return 1; // le fichier est vide donc on retourne 1
    }
    return 0; // le fichier n'est pas vide donc on retourne 0
    fclose(ficVoyage);
}

/**********************Afficher tous les voyages formatées **********************/
void getDescriptionVoyages()
{
    Voyage voyage;

    int nbreVoy = nbreVoyages();

    // ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    ficVoyage = fopen("Voyages.txt", "r");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    if (nbreVoy > 0)
    {
        while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &voyage.code, voyage.description,
                      &voyage.prix, &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee,
                      &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee,
                      voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
        {

            int duree = calculerDuree(voyage.dateDep, voyage.dateArriv);
            printf("\nVoyage : %d \n%d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", voyage.code, duree, voyage.aeroportArr, voyage.description,
                   voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                   voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
            printf("\n---------------------------------------------------------\n");
        }
    }

    fclose(ficVoyage);
}

/**********************Ajouter un voyage**********************/
void ajoutVoyage()
{
    Voyage Voyage;
    int duree;
    Voyage.code = nbreVoyages() + 1;

    // ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    ficVoyage = fopen("Voyages.txt", "a+");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);

    // description
    printf("Donner la description du Voyage : ");
    fflush(stdin);
    gets(Voyage.description);
    do
    {
        // dateDepart
        printf("Donner la date de depart sous la forme (jj/mm/aaaa) : ");
        fflush(stdin);
        scanf("%d/%d/%d", &Voyage.dateDep.jour, &Voyage.dateDep.mois, &Voyage.dateDep.annee);
        // dateArrivee
        printf("Donner la date d'arrivee sous la forme (jj/mm/aaaa) : ");
        fflush(stdin);
        scanf("%d/%d/%d", &Voyage.dateArriv.jour, &Voyage.dateArriv.mois, &Voyage.dateArriv.annee);
        duree = calculerDuree(Voyage.dateDep, Voyage.dateArriv);
    } while (duree < -1);
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
    if (fprintf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d\n", Voyage.code, Voyage.description, Voyage.prix, Voyage.dateDep.jour, Voyage.dateDep.mois, Voyage.dateDep.annee, Voyage.dateArriv.jour, Voyage.dateArriv.mois, Voyage.dateArriv.annee,
                Voyage.aeroportDep, Voyage.aeroportArr,
                Voyage.compagnieAerienne, Voyage.nbrePlacesRest) != -1)
    {
        printf("\n**************** Ajout effectuee avec succees ************************\n");
        fclose(ficVoyage);
        // Fermer le fichier
    }
}
/******************** Afficher tous les voyages****************/
void getAll()
{
    char line[255];
    ficVoyage = fopen("Voyages.txt", "r");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    while (fgets(line, 254, ficVoyage) != NULL)
    {
        printf("%s", line);
    }
    fclose(ficVoyage);
}
/*************************GetVoyageById**********************************/
int getVoyageById(int code, Voyage *voyage)
{
    int estVide = testSiFichierVide();
    ficVoyage = fopen("Voyages.txt", "r");
    if (estVide != 1)
    {
        while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &(*voyage).code, (*voyage).description, &(*voyage).prix, &(*voyage).dateDep.jour, &(*voyage).dateDep.mois, &(*voyage).dateDep.annee, &(*voyage).dateArriv.jour, &(*voyage).dateArriv.mois, &(*voyage).dateArriv.annee, (*voyage).aeroportDep, (*voyage).aeroportArr, (*voyage).compagnieAerienne, &(*voyage).nbrePlacesRest) != EOF)
        {
            if ((*voyage).code == code)
                return 1;
        }
    }
    else
    {
        printf("Aucun voyage n'est disponible");
    }
    return 0;
}
/*************************Suppression*************************************/
void supprimerVoyage()
{
    Voyage voyage;
    int nbreVoy = nbreVoyages();
    getAll();
    int code = 0;
    if (nbreVoy != 0)
    {
        do
        {
            printf("Donner le numero du voyage a supprimer : ");
            scanf("%d", &code);

        } while (!(code > 0 && code <= nbreVoy));
        ficVoyage = fopen("Voyages.txt", "r");
        ficArchive = fopen("archiveVoyage.txt", "w");
        nv = fopen("nv.txt", "w");
        while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d",
                      &voyage.code, voyage.description, &voyage.prix, &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee,
                      &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee,
                      voyage.aeroportDep,
                      voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
        {

            if (voyage.code != code)
            {
                fprintf(nv, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
            }
            else
            {
                fprintf(ficArchive, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
            }
        }
        fclose(nv);
        fclose(ficArchive);
        fclose(ficVoyage);

        ficVoyage = fopen("Voyages.txt", "w+");
        nv = fopen("nv.txt", "r");
        while (fscanf(nv, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &voyage.code, voyage.description, &voyage.prix, &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee, &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
        {
            fprintf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d \n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
        }
        printf("\n*****************************Suppression effectuée avec succées*********************************\n");
    }
    else
    {
        printf("Aucun voyage n'est disponible");
    }
    fclose(nv);
    fclose(ficVoyage);
}

/*************************Recherche des voyages disponibles par dates*****************/
void getByDates()
{
    Voyage voyage;
    int nbreVoy = nbreVoyages();
    int duree;
    getAll();
    Date dateDep;
    Date dateArr;

    if (nbreVoy != 0)
    {
        ficVoyage = fopen("Voyages.txt", "r");

        printf("Entrez la date de depart (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &dateDep.jour, &dateDep.mois, &dateDep.annee);
        printf("Entrez la date d'arrivee (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &dateArr.jour, &dateArr.mois, &dateArr.annee);
        duree = calculerDuree(dateDep, dateArr);

        printf("-------------------------%d/%d/%d\n", dateDep.jour, dateDep.mois, dateDep.mois);
        printf("*************************%d/%d/%d\n", dateArr.jour, dateArr.mois, dateArr.mois);

        if (dateDep.jour != 0 && dateDep.mois != 0 && dateDep.annee != 0 && dateArr.jour != 0 && dateArr.mois != 0 && dateArr.annee != 0)
        {
            printf("\t\tLes voyages disponibles a partir : %d / %d / %d \n\t\tJusqu'a : %d/%d/%d \n", dateDep.jour, dateDep.mois, dateDep.annee, dateArr.jour, dateArr.mois, dateArr.annee);
            while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &voyage.code, voyage.description, &voyage.prix,
                          &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee,
                          &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee,
                          voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
            {
                if (voyage.dateDep.jour == dateDep.jour && voyage.dateDep.mois == dateDep.mois && voyage.dateDep.annee == dateDep.annee)
                {
                    printf("\nVoyage : %d \n%d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", voyage.code, duree, voyage.aeroportArr, voyage.description,
                           voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                           voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                }
            }
        }
        else
        {
            if (dateDep.jour != 0 && dateDep.mois != 0 && dateDep.annee != 0)
            {
                printf("\t\tLes voyages disponibles a partir : %d / %d / %d \n", dateDep.jour, dateDep.mois, dateDep.annee);
                while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &voyage.code, voyage.description, &voyage.prix,
                              &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee,
                              &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee,
                              voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
                {
                    if (voyage.dateDep.jour == dateDep.jour && voyage.dateDep.mois == dateDep.mois && voyage.dateDep.annee == dateDep.annee)
                    {
                        printf("\n*********************Voyage : %d \n%d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", voyage.code, duree, voyage.aeroportArr, voyage.description,
                               voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                               voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                    }
                }
            }
            else
            {
                printf("\t\tLes voyages disponibles date d'arrivee : %d / %d / %d \n", dateArr.jour, dateArr.mois, dateArr.annee);
                while (fscanf(ficVoyage, "%d   %s   %f   %d/%d/%d   %d/%d/%d   %s   %s   %s   %d", &voyage.code, voyage.description, &voyage.prix,
                              &voyage.dateDep.jour, &voyage.dateDep.mois, &voyage.dateDep.annee,
                              &voyage.dateArriv.jour, &voyage.dateArriv.mois, &voyage.dateArriv.annee,
                              voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, &voyage.nbrePlacesRest) != EOF)
                {
                    if (voyage.dateArriv.jour == dateArr.jour && voyage.dateArriv.mois == dateArr.mois && voyage.dateArriv.annee == dateArr.annee)
                    {
                        printf("\nVoyage : %d \n%d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", voyage.code, duree, voyage.aeroportArr, voyage.description,
                               voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                               voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                    }
                }
            }
        }
        fclose(ficVoyage);
    }
}
