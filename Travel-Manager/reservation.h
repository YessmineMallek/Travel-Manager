#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <windows.h>
FILE *ficRes;
typedef struct reservation
{
    int id;
    int codeVoyage;
    char nomUtilisateurRes[30];
    SYSTEMTIME Time;
} reservation;

/***********************Convertir en Reservation***********************************/
void convertirEnReservation(char ligne[254], reservation *reservation)
{
    char d[] = "|";
    char *p = strtok(ligne, d);
    char *pRes;

    int i = 0;
    while (p != NULL)
    {
        if (i == 0)
        {
            (*reservation).id = atoi(p);
        }
        if (i == 1)
        {
            (*reservation).codeVoyage = atoi(p);
        }
        if (i == 2)
        {
            sprintf((*reservation).nomUtilisateurRes, p);
        }
        if (i == 3)
        {
            pRes = p;
        }
        p = strtok(NULL, d);
        i++;
    }
    // date de reservation (du String en entier )
    char *dateRes = strtok(pRes, "/");
    int j = 0;
    while (dateRes != NULL)
    {
        if (j == 0)
        {
            (*reservation).Time.wDay = atoi(dateRes);
        }
        if (j == 1)
        {
            (*reservation).Time.wMonth = atoi(dateRes);
        }
        if (j == 2)
        {
            (*reservation).Time.wYear = atoi(dateRes);
        }
        j++;
        dateRes = strtok(NULL, "/");
    }
}

/*******************afficher le nombre de reservation *************************/
int getNombreReservation()
{
    int nbre;
    char ligne[255];
    ficRes = fopen("reservation.txt", "r");
    if (ficRes == NULL)
        exit(1);
    while (fgets(ligne, 254, ficRes) != NULL)
    {
        nbre++;
    }
    fclose(ficRes);
    return nbre;
}

/******************Afficher les reservations*******************************************/
void afficherReservations()
{
    reservation reservation;
    char ligne[255];
    ficRes = fopen("reservation.txt", "r");
    if (ficRes == NULL)
        exit(1);
    printf("code Reservation | code Voyage |Client |Date de reservation\n");
    while (fgets(ligne, 254, ficRes) != NULL)
    {
        convertirEnReservation(ligne, &reservation);
        printf("%d |%d |%s |%d/%d/%d\n", reservation.id, reservation.codeVoyage, reservation.nomUtilisateurRes, reservation.Time.wDay, reservation.Time.wMonth, reservation.Time.wYear);
        printf("---------------------------------------------------------------------------------\n");
    }
    fclose(ficRes);
}
/**************Ajout reservation*************/
void ajouterReservation(char idClient[30], int idVoyage)
{
    reservation reservationToAdd;
    int code = getNombreReservation() + 1;
    // verifier s'il existe de places
    int nbrePlace = getNombresPlaces(idVoyage);

    ficRes = fopen("reservation.txt", "a+");
    if (ficRes == NULL)
        exit(1);
    if (nbrePlace > 0)
    {
        int nvNombrePlaces = nbrePlace - 1;
        // dimunier le nombre des places
        modifiderNombrePlaces(idVoyage, nvNombrePlaces);
        reservationToAdd.id = code;
        reservationToAdd.codeVoyage = idVoyage;
        sprintf(reservationToAdd.nomUtilisateurRes, idClient);
        GetLocalTime(&reservationToAdd.Time);

        if (fprintf(ficRes, "%d|%d|%s|%d/%d/%d\n", reservationToAdd.id, reservationToAdd.codeVoyage, reservationToAdd.nomUtilisateurRes, reservationToAdd.Time.wDay, reservationToAdd.Time.wMonth, reservationToAdd.Time.wYear) != -1)
            printf("---------------Reservation effectuee avec succes--------------------------\n");

        fclose(ficRes);
    }
    else
    {
        printf("\n----------------------------------------\n");
        printf("\t\t Le voyage est complet! \n ");
        printf("\n----------------------------------------\n");
    }
}