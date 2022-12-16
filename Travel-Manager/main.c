#include <stdio.h>
#include <stdlib.h>

typedef struct Date
{
       int jour;
       int mois;
       int annee;
} Date;
typedef struct Vol
{
    int code ;
    Date dateDep;
    Date dateArriv;
    char aeroportDep[30];
    char aeroportArr[30];
    int numAvion;
    int nbreChaisesRest;//Pour les chaises restantes
}Vol;
int main()
{
    //ouvrir le ficher avec le mode ecriture/lecture en fin du fichier (a+)
    FILE *ficVol=fopen("vols.txt","a+");
    int lettre=0;
    if (ficVol == NULL)//tester si le ficher est ouvert
        exit (1);
   while (lettre != EOF)//EOF=End Of File
   {
        lettre =fgetc(ficVol);
        printf("%c",lettre);
   }







    //Fermer le fichier
    fclose(ficVol);
    return 0;
}
