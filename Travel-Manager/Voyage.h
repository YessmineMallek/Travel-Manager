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
    char description[100];
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
    fclose(ficVoyage);

    return nbre;
}
/*********************DuChaine en Voyage***************************************/
void convertirEnVoyage(char *ligne, Voyage *voyage)
{
    char d[] = "|";
    char *pDdep;
    char *pDarr;
    char *p = strtok(ligne, d);
    int i = 0;
    while (p != NULL)
    {

        if (i == 0)
        {
            (*voyage).code = atoi(p);
        }
        if (i == 1)
        {
            sprintf((*voyage).description, p);
        }
        if (i == 2)
        {
            (*voyage).prix = (float)strtod(p, NULL);
        }
        if (i == 3)
        {
            pDdep = p;
        }
        if (i == 4)
        {
            pDarr = p;
        }
        if (i == 5)
        {
            sprintf((*voyage).aeroportDep, p);
        }
        if (i == 6)
        {
            sprintf((*voyage).aeroportArr, p);
        }
        if (i == 7)
        {
            sprintf((*voyage).compagnieAerienne, p);
        }
        if (i == 8)
        {
            (*voyage).nbrePlacesRest = atoi(p);
        }
        p = strtok(NULL, d);
        i++;
    }
    // date de debut (du String en entier )
    char *nvDateDep = strtok(pDdep, "/");
    int j = 0;

    while (nvDateDep != NULL)
    {
        if (j == 0)
        {
            (*voyage).dateDep.jour = atoi(nvDateDep);
        }
        if (j == 1)
        {
            (*voyage).dateDep.mois = atoi(nvDateDep);
        }
        if (j == 2)
        {
            (*voyage).dateDep.annee = atoi(nvDateDep);
        }
        j++;
        nvDateDep = strtok(NULL, "/");
    }

    // date d'arrivee (du String en entier )
    char *nvDateArr = strtok(pDarr, "/");
    int c = 0;
    while (nvDateArr != NULL)
    {
        if (c == 0)
        {
            (*voyage).dateArriv.jour = atoi(nvDateArr);
        }
        if (c == 1)
        {
            (*voyage).dateArriv.mois = atoi(nvDateArr);
        }
        if (c == 2)
        {
            (*voyage).dateArriv.annee = atoi(nvDateArr);
        }
        c++;
        nvDateArr = strtok(NULL, "/");
    }
}
/*************************GetVoyageById**********************************/
int getVoyageById(int code, Voyage *voyage)
{
    char ligne[255];
    int nbre = nbreVoyages();
    int trouve = 0;
    printf("LE NOMBREEE %d\n\n", nbre);
    ficVoyage = fopen("Voyages.txt", "a+");
    for (int i = 0; i < nbre; i++)
    {
        fgets(ligne, 254, ficVoyage);
        convertirEnVoyage(ligne, voyage);
        if ((*voyage).code == code)
            trouve = 1;
        printf("%s\n", ligne);
        system("pause");
    }

    printf("HRLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
    return trouve;
}

/***************Verifier si le voyage existe ou non (meme date ,meme depart ,meme compagnie)*******************/
int voyageExiste(Voyage voyageAverif)
{
    ficVoyage = fopen("Voyages.txt", "a+");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);

    char jourStr[30], code[50], moisStr[30], anneeStr[30], ligne[255], codeVoy[30];
    Voyage voyage;
    itoa(voyageAverif.dateDep.jour, jourStr, 10);
    itoa(voyageAverif.dateDep.mois, moisStr, 10);
    itoa(voyageAverif.dateDep.annee, anneeStr, 10);
    sprintf(code, strcat(strcat(strcat(strcat(strcat(strcat(jourStr, "/"), moisStr), "/"), anneeStr), voyageAverif.aeroportDep), voyageAverif.compagnieAerienne));
    while (fgets(ligne, 254, ficVoyage) != NULL)
    {

        convertirEnVoyage(ligne, &voyage);
        itoa(voyage.dateDep.jour, jourStr, 10);
        itoa(voyage.dateDep.mois, moisStr, 10);
        itoa(voyage.dateDep.annee, anneeStr, 10);
        sprintf(codeVoy, strcat(strcat(strcat(strcat(strcat(strcat(jourStr, "/"), moisStr), "/"), anneeStr), voyage.aeroportDep), voyage.compagnieAerienne));
        if (strcmp(codeVoy, code) == 0)
            return 1;
    }
    fclose(ficVoyage);
    printf("-------%s\n", code);
    printf("----****---%s\n", codeVoy);
    return 0;
}

/******************************Fonction pour generer l'id********************************/
int idVoyage()
{
    int nbreFicVoya = nbreVoyages();
    int nbre = 0;
    char line[255];
    ficArchive = fopen("archiveVoyage.txt", "r");
    if (ficArchive == NULL) // tester si le ficher est ouvert
        exit(1);
    while (fgets(line, 254, ficArchive) != NULL)
    {
        nbre++;
    }
    fclose(ficArchive);

    return nbre + nbreFicVoya;
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
    char ligne[255];

    int nbreVoy = nbreVoyages();
    // ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    ficVoyage = fopen("Voyages.txt", "a+");
    if (ficVoyage == NULL) // tester si le ficher est ouvert
        exit(1);
    if (nbreVoy > 0)
    {
        while (fgets(ligne, 254, ficVoyage) != NULL)
        {

            convertirEnVoyage(ligne, &voyage);
            int duree = calculerDuree(voyage.dateDep, voyage.dateArriv);
            printf("\nVoyage du %d jours a %s \n%s\nA partir de : %d/%d/%d \nJusqu'a : %d/%d/%d\nNombre places restantes : %d", duree, voyage.aeroportArr, voyage.description,
                   voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                   voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);

            printf("\n---------------------------------------------------------\n");
        }
    }

    fclose(ficVoyage);
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

/*************************Recherche des voyages disponibles par dates*****************/
void getByDates()
{
    Voyage voyage;
    int nbreVoy = nbreVoyages();
    int duree;
    getAll();
    Date dateDep;
    Date dateArr;
    char ligne[255];

    if (nbreVoy != 0)
    {
        ficVoyage = fopen("Voyages.txt", "r");

        printf("Entrez la date de depart (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &dateDep.jour, &dateDep.mois, &dateDep.annee);
        printf("Entrez la date d'arrivee (jj/mm/aaaa) : ");
        scanf("%d/%d/%d", &dateArr.jour, &dateArr.mois, &dateArr.annee);

        printf("-------------------------%d/%d/%d\n", dateDep.jour, dateDep.mois, dateDep.mois);
        printf("*************************%d/%d/%d\n", dateArr.jour, dateArr.mois, dateArr.mois);

        if (dateDep.jour != 0 && dateDep.mois != 0 && dateDep.annee != 0 && dateArr.jour != 0 && dateArr.mois != 0 && dateArr.annee != 0)
        {
            printf("\t\tLes voyages disponibles a partir : %d / %d / %d \n\t\tJusqu'a : %d/%d/%d \n", dateDep.jour, dateDep.mois, dateDep.annee, dateArr.jour, dateArr.mois, dateArr.annee);
            while (fgets(ligne, 254, ficVoyage) != NULL)
            {
                convertirEnVoyage(ligne, &voyage);
                duree = calculerDuree(voyage.dateDep, voyage.dateArriv);
                if (voyage.dateDep.jour == dateDep.jour && voyage.dateDep.mois == dateDep.mois && voyage.dateDep.annee == dateDep.annee &&
                    voyage.dateArriv.jour == dateArr.jour && voyage.dateArriv.mois == dateArr.mois && voyage.dateArriv.annee == dateArr.annee)
                {
                    printf("\nVoyage :%d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", duree, voyage.aeroportArr, voyage.description,
                           voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                           voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                }
            }
        }

        if (dateDep.jour != 0 && dateDep.mois != 0 && dateDep.annee != 0)
        {
            printf("\t\tLes voyages disponibles a partir : %d / %d / %d \n", dateDep.jour, dateDep.mois, dateDep.annee);
            while (fgets(ligne, 254, ficVoyage) != NULL)
            {
                convertirEnVoyage(ligne, &voyage);
                duree = calculerDuree(voyage.dateDep, voyage.dateArriv);

                if (voyage.dateDep.jour == dateDep.jour && voyage.dateDep.mois == dateDep.mois && voyage.dateDep.annee == dateDep.annee)
                {
                    printf("\nVoyage : %d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", duree, voyage.aeroportArr, voyage.description,
                           voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                           voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                }
            }
        }
        if (dateArr.jour != 0 && dateArr.mois != 0 && dateArr.annee != 0)
        {
            printf("\t\tLes voyages disponibles date d'arrivee : %d / %d / %d \n", dateArr.jour, dateArr.mois, dateArr.annee);
            while (fgets(ligne, 254, ficVoyage) != NULL)
            {
                convertirEnVoyage(ligne, &voyage);
                duree = calculerDuree(voyage.dateDep, voyage.dateArriv);

                if (voyage.dateArriv.jour == dateArr.jour && voyage.dateArriv.mois == dateArr.mois && voyage.dateArriv.annee == dateArr.annee)
                {
                    printf("\nVoyage : %d jours a %s\n%s\nA partir de : %d/%d/%d\nJusqu'a : %d/%d/%d\nNombre places restantes : %d", duree, voyage.aeroportArr, voyage.description,
                           voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee,
                           voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.nbrePlacesRest);
                }
            }
        }
    }
    fclose(ficVoyage);
}

/**********************Ajouter un voyage**********************/
void ajoutVoyage()
{
    Voyage Voyage;
    int existe;

    do
    {
        printf("\t\t\t\tAjout d'un voyage\n");
        int duree;
        Voyage.code = idVoyage() + 1;

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
        existe = voyageExiste(Voyage);
        if (existe != 1)
        {
            ficVoyage = fopen("Voyages.txt", "a+");
            if (ficVoyage == NULL) // tester si le ficher est ouvert
                exit(1);

            if (fprintf(ficVoyage, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", Voyage.code, Voyage.description, Voyage.prix, Voyage.dateDep.jour, Voyage.dateDep.mois, Voyage.dateDep.annee, Voyage.dateArriv.jour, Voyage.dateArriv.mois, Voyage.dateArriv.annee,
                        Voyage.aeroportDep, Voyage.aeroportArr,
                        Voyage.compagnieAerienne, Voyage.nbrePlacesRest) != -1)
            {
                printf("\n**************** Ajout effectuee avec succees ************************\n");
                fclose(ficVoyage);
                // Fermer le fichier
            }
        }
        else
        {
            printf("\n**************** \tLe Voyage existe deja \t************************\n ");
        }
    } while (existe == 1);
}
/**************************Modifier Voyage*******************************************/
void modifiderVoyage(int code, int choix)
{
    char ligne2[255], ligne[255];
    int aerp;
    Voyage voyage;
    Date nvDateDep;
    Date nvDateArr;
    char nvAeropDep[30];
    char nvAeropArr[30];
    char nvCompaAerien[30];
    nv = fopen("nv.txt", "w+");
    ficVoyage = fopen("Voyages.txt", "r");

    if (ficVoyage == NULL || nv == NULL) // tester si le ficher est ouvert
        exit(1);
    while (fgets(ligne, 254, ficVoyage) != NULL)
    {
        convertirEnVoyage(ligne, &voyage);
        if (code == voyage.code)
        {
            switch (choix)
            {
            case 1:
                printf("La nouvelle description du voyage %d :  \n", code);
                fflush(stdin);
                gets(voyage.description);
                break;
            case 2:
                do
                {
                    printf("Saisir la nouvelle date de depart du voyage %d : ", code);
                    fflush(stdin);
                    scanf("%d/%d/%d", &nvDateDep.jour, &nvDateDep.mois, &nvDateDep.annee);
                    if (nvDateDep.jour > 0 && nvDateDep.mois > 0 && nvDateDep.annee > 0)
                    {
                        voyage.dateDep = nvDateDep;
                    }
                    printf("Saisir la nouvelle date d'arrivee du voyage %d : ", code);
                    fflush(stdin);
                    scanf("%d/%d/%d", &nvDateArr.jour, &nvDateArr.mois, &nvDateArr.annee);

                    if (nvDateArr.jour > 0 && nvDateArr.mois > 0 && nvDateArr.annee > 0)
                    {
                        voyage.dateArriv = nvDateArr;
                    }

                } while (calculerDuree(voyage.dateDep, voyage.dateArriv) < -1);
                break;
            case 3:

                do
                {
                    printf("* Voulez-vous modifier quelle aeroport ?*\n");
                    printf("\t* 1 *:Depart\n");
                    printf("\t* 2 *:Arrivee\n");
                    printf("\t* 3 *:Depart et Arrivee \n");
                    scanf("%d", &aerp);
                } while (aerp != 1 && aerp != 2 && aerp != 3);
                if (aerp == 1)
                {
                    printf("Saisir le nouvelle aeroport de depart :");
                    scanf("%s", nvAeropDep);
                    sprintf(voyage.aeroportDep, nvAeropDep);
                }
                else if (aerp == 2)
                {
                    printf("Saisir le nouvelle aeroport d'arrivee :");
                    scanf("%s", nvAeropArr);
                    sprintf(voyage.aeroportArr, nvAeropArr);
                }
                else
                {
                    printf("Saisir le nouvelle aeroport de depart :");
                    scanf("%s", nvAeropDep);
                    sprintf(voyage.aeroportDep, nvAeropDep);
                    printf("Saisir le nouvelle aeroport d'arrivee :");
                    scanf("%s", nvAeropArr);
                    sprintf(voyage.aeroportArr, nvAeropArr);
                }
                break;
            case 4:
                printf("Saisir la nouvelle compagnie aerienne :");
                scanf("%s", nvCompaAerien);
                sprintf(voyage.compagnieAerienne, nvCompaAerien);
                break;
            case 5:
                printf("Saisir le nouveau prix :");
                scanf("%f", &voyage.prix);
                break;
            case 6:
                printf("Saisir le nombre des places restantes :");
                scanf("%d", &voyage.nbrePlacesRest);
                break;
            }
            choix = 0;
        }
        fprintf(nv, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
    }
    fclose(nv);
    fclose(ficVoyage);
    nv = fopen("nv.txt", "r");
    ficVoyage = fopen("Voyages.txt", "w+");
    while (fgets(ligne2, 254, nv) != NULL)
    {
        convertirEnVoyage(ligne2, &voyage);
        fprintf(ficVoyage, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
    }
    fclose(nv);
    fclose(ficVoyage);
    printf("\n*****************\t\tModification effectuee avec succee****************\n");
}

/*************************Suppression*************************************/
void supprimerVoyage()
{
    Voyage voyage;
    int validation;
    char ligne[255];
    int nbreVoy = idVoyage();
    getAll();
    int code = 0;
    if (nbreVoy != 0)
    {
        do
        {
            printf("--------------%d\n", nbreVoy);

            printf("Donner le numero du voyage a supprimer : ");
            scanf("%d", &code);

        } while (code < 0 || code > nbreVoy);
        ficVoyage = fopen("Voyages.txt", "r");
        ficArchive = fopen("archiveVoyage.txt", "w");
        nv = fopen("nv.txt", "w");
        do
        {
            printf("Etes vous sur de supprimer ce voyage \n* 1 *:oui\n* 2 *:non\n");
            scanf("%d", &validation);
        } while (validation != 1 && validation != 2);
        if (validation == 1)
        {
            while (fgets(ligne, 254, ficVoyage) != NULL)
            {
                convertirEnVoyage(ligne, &voyage);

                if (voyage.code != code)
                {
                    fprintf(nv, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
                }
                else
                {
                    fprintf(ficArchive, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
                }
            }
            fclose(nv);
            fclose(ficArchive);
            fclose(ficVoyage);

            ficVoyage = fopen("Voyages.txt", "w+");
            nv = fopen("nv.txt", "r");
            while (fgets(ligne, 254, nv) != NULL)
            {
                convertirEnVoyage(ligne, &voyage);
                fprintf(ficVoyage, "%d|%s|%f|%d/%d/%d|%d/%d/%d|%s|%s|%s|%d\n", voyage.code, voyage.description, voyage.prix, voyage.dateDep.jour, voyage.dateDep.mois, voyage.dateDep.annee, voyage.dateArriv.jour, voyage.dateArriv.mois, voyage.dateArriv.annee, voyage.aeroportDep, voyage.aeroportArr, voyage.compagnieAerienne, voyage.nbrePlacesRest);
            }
            printf("\n*****************************Suppression effectuée avec succées*********************************\n");
        }
    }
    else
    {
        printf("Aucun voyage n'est disponible");
    }

    fclose(nv);
    fclose(ficVoyage);
}