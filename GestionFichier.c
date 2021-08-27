#include "GestionFichier.h"

int AjouterPeriodeFichier(struct PeriodeEtude* PeriodeSave)
{
    FILE* MyFile = NULL;
    int result, tailleTheme, ret = 111;
    char pathFichier[50];

    NomFichierDate(PeriodeSave->Date, pathFichier);

    if(access(pathFichier, F_OK) != 0) // Si le fichier n'existe pas
    {
        MyFile = fopen(pathFichier, "ab");

        if(MyFile == NULL)
        {
            result = -1;
            perror("Erreur lors de l'ouverture du fichier !\n");
        }
        else
            fwrite(&PeriodeSave->Day, sizeof(int), 1, MyFile); // Ajout du jour de la semaine
    }
    else
    {
        MyFile = fopen(pathFichier, "ab");

        if(MyFile == NULL)
        {
            result = -1;
            perror("Erreur lors de l'ouverture du fichier !\n");
        }
    }

    if(MyFile != NULL)
    {
        result = 0;

        ret = fwrite(PeriodeSave->HeureDebut, 2 * sizeof(int), 1, MyFile);
        fwrite(PeriodeSave->HeureFin, 2 * sizeof(int), 1, MyFile);
        tailleTheme = strlen(PeriodeSave->Theme) + 1;
        fwrite(&tailleTheme, sizeof(int), 1, MyFile);
        fwrite(PeriodeSave->Theme, tailleTheme, 1, MyFile);

        fclose(MyFile);
    }

    return result;
}

void RechercherPeriodeFichier(struct PeriodeEtude** ptrTete, int Date[3])
{
    FILE* MyFile = NULL;
    int tailleTheme;
    struct PeriodeEtude *newPeriode = NULL;
    char pathFichier[50], periode[100];
    int day, heureDeb[2];

    NomFichierDate(Date, pathFichier);

    MyFile = fopen(pathFichier, "rb");

    if(MyFile != NULL) // Si le fichier existe
    {
        fread(&day, sizeof(int), 1, MyFile);

        while(fread(heureDeb, 2 * sizeof(int), 1, MyFile) == 1)
        {
            newPeriode = (struct PeriodeEtude*) malloc(sizeof(struct PeriodeEtude));

            newPeriode->HeureDebut[0] = heureDeb[0];
            newPeriode->HeureDebut[1] = heureDeb[1];

            fread(newPeriode->HeureFin, 2 * sizeof(int), 1, MyFile);
            fread(&tailleTheme, sizeof(int), 1, MyFile);

            newPeriode->Theme = (char*) malloc(tailleTheme * sizeof(char));
            fread(newPeriode->Theme, tailleTheme, 1, MyFile);

            newPeriode->Date[0] = Date[0];
            newPeriode->Date[1] = Date[1];
            newPeriode->Date[2] = Date[2];

            newPeriode->Day = day;

            PeriodeToString(newPeriode, periode);
            Ajouter(ptrTete, newPeriode);
        }

        fclose(MyFile);
    }
}


void NomFichierDate(int Date[3], char* pathFichier)
{
    char buffer[70];

    strcpy(pathFichier, REPERTOIRE_ENREGISTREMENT);
    DateToString(Date, buffer);
    strcat(pathFichier,buffer);
    strcat(pathFichier, ".txt");
}








