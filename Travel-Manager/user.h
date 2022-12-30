#include <stdio.h>
#include <stdlib.h>
#include <String.h>
typedef struct user
{
    int id;
    char nomUtilisateur[30];
    char motDePasse[30];
    char role[30];
} user;
FILE *ficUser;
/******************Calculer le nombre d'utilisateur *****************************/
int getNombresUtilisateurs()
{
    int nbre;
    char ligne[255];
    ficUser = fopen("user.txt", "r");
    while (fgets(ligne, 254, ficUser) != NULL)
    {
        nbre++;
    }
    fclose(ficUser);
    return nbre;
}
/***********************Convertir en User***********************************/
void convertirEnUser(char ligne[254], user *user)
{
    char d[] = "|";
    char *p = strtok(ligne, d);
    int i = 0;
    while (p != NULL)
    {
        if (i == 0)
        {
            (*user).id = atoi(p);
        }
        if (i == 1)
        {
            sprintf((*user).nomUtilisateur, p);
        }
        if (i == 2)
        {
            sprintf((*user).motDePasse, p);
        }
        if (i == 3)
        {
            sprintf((*user).role, p);
        }
        p = strtok(NULL, d);
        i++;
    }
}
/************************Verifier l'existance d'un voyage*******************************************/
int existeUser(user userToAdd)
{
    ficUser = fopen("user.txt", "a+");
    user user;
    char ligne[255];
    if (ficUser == NULL)
        exit(1);
    while (fgets(ligne, 254, ficUser) != NULL)
    {
        convertirEnUser(ligne, &user);
        if (strcmp(user.nomUtilisateur, userToAdd.nomUtilisateur) == 0)
            return 1;
    }
    fclose(ficUser);
    return 0;
}
/**********************Ajouter utilisateur***************************/
void ajouterUtilisateur(user *userToAdd)
{
    int id = getNombresUtilisateurs();
    int existe;
    do
    {
        printf("\t\tAjout nouveau utilisateur\n");
        (*userToAdd).id = id + 1;
        // nom d'utilisateur
        printf("donner le nom d'utilisateur\n");
        fflush(stdin);
        gets((*userToAdd).nomUtilisateur);
        // mot de passe
        printf("Donner le mot de passe \n");
        fflush(stdin);
        gets((*userToAdd).motDePasse);
        sprintf((*userToAdd).role, "client");
        existe = existeUser((*userToAdd));

        if (existe != 1)
        {
            ficUser = fopen("user.txt", "a+");
            if (ficUser == NULL)
                exit(1);

            fprintf(ficUser, "%d|%s|%s|%s\n", (*userToAdd).id, (*userToAdd).nomUtilisateur, (*userToAdd).motDePasse, (*userToAdd).role);
            printf("---------------------------------------------------------\n");
            printf("Ajout effectuee avec succes\n");
            printf("---------------------------------------------------------\n");
        }
        else
        {
            printf("---------------------------------------------------------\n");
            printf("nom d'Utilisateur existe deja\n");
            printf("---------------------------------------------------------\n");
        }
    } while (existe == 1);
    fclose(ficUser);
}
/***********************s'authentifier**************************/
int authentifier(char username[30], char password[30])
{
    user user, userToAuth;
    char ligne[254];
    sprintf(user.nomUtilisateur, username);
    sprintf(user.motDePasse, password);
    int existe = existeUser(user);
    if (existe == 1)
    {
        ficUser = fopen("user.txt", "a+");
        if (ficUser == NULL)
            exit(1);
        while (fgets(ligne, 254, ficUser))
        {
            convertirEnUser(ligne, &userToAuth);
            if (strcmp(userToAuth.nomUtilisateur, username) == 0 && strcmp(userToAuth.motDePasse, password) == 0)
            {

                if (strcmp(userToAuth.role, "client\n") == 0)
                {
                    return 0; // client==0
                }
                else
                {
                    return 1; // Admin=1
                }
            }
        }
        fclose(ficUser);
    }
    else
    {
        printf("---------------------------------------------------------\n");
        printf("Utilisateur n'existe pas ou nom d'utlisateur incorrect\n");
        printf("---------------------------------------------------------\n");

        return -1;
    }
    return -2;
}
