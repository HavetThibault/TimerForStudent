#include "GestionPeriodes.h"

void Ajouter(struct PeriodeEtude** PtrTete, struct PeriodeEtude* newPeriode)
{
    struct PeriodeEtude* lastPeriode = LastPeriode(*PtrTete);

    if(lastPeriode == NULL) // Si la liste est vide
    {
        *PtrTete = newPeriode;
        newPeriode->Next = NULL;
    }
    else
    {
        lastPeriode->Next = newPeriode;
        newPeriode->Next = NULL;
    }
}

int ComparePeriodesEtudeDateHeure(struct PeriodeEtude* P1, struct PeriodeEtude* P2)
{
    int result = CompareDate(P1->Date,P2->Date);

    if(!result) // Result == 0 ==> Egalite de date
    {
        // Comparaison heure debut
        if(P1->HeureDebut[0] < P2->HeureDebut[0]) // Comparaison heures
            result = -1;
        else if(P1->HeureDebut[0] > P2->HeureDebut[0])
            result = 1;
        else if(P1->HeureDebut[1] < P2->HeureDebut[1]) // Comparaison minutes
            result = -1;
        else if(P1->HeureDebut[1] > P2->HeureDebut[1])
            result = 1;
    }

    return result;
}

void InitPeriode(struct PeriodeEtude* MaPeriode, char* theme)
{
    time_t TimeActuel;
    struct tm * MaTm;

    TimeActuel = time(NULL);
    MaTm = localtime(&TimeActuel);

    MaPeriode->Date[2] = MaTm->tm_year + 1900;
    MaPeriode->Date[1] = MaTm->tm_mon + 1;
    MaPeriode->Date[0] = MaTm->tm_mday;
    MaPeriode->HeureDebut[0] = MaTm->tm_hour;
    MaPeriode->HeureDebut[1] = MaTm->tm_min;
    MaPeriode->Day = MaTm->tm_wday;
    MaPeriode->Theme = (char*) malloc((strlen(theme) + 1) * sizeof(char));
    strcpy(MaPeriode->Theme, theme);
}

struct PeriodeEtude* LastPeriode(struct PeriodeEtude* PtrTete)
{
    struct PeriodeEtude* ptrCurrent = NULL, *lastPeriode;

    if(PtrTete == NULL)
    {
        lastPeriode = NULL;
    }
    else
    {
        ptrCurrent = PtrTete;
        while(ptrCurrent->Next != NULL)
        {
            ptrCurrent = ptrCurrent->Next;
        }

        lastPeriode = ptrCurrent;
    }

    return lastPeriode;
}

void PeriodeToString(struct PeriodeEtude* UnePeriode, char* TheString)
{
    char PeriodeSansdate[100];

    DateToString(UnePeriode->Date, TheString);

    PeriodeToStringSansDate(UnePeriode, PeriodeSansdate);

    strcat(TheString, " ==> ");
    strcat(TheString, PeriodeSansdate);
}

void PeriodeToStringSansDate(struct PeriodeEtude* UnePeriode, char* TheString)
{
    PeriodeToHeure(UnePeriode, TheString);

    strcat(TheString, " : ");
    strcat(TheString, UnePeriode->Theme);
}

void PeriodeToHeure(struct PeriodeEtude* UnePeriode, char* TheString)
{
    char HeureFin[20];

    IntToHeure(UnePeriode->HeureDebut, TheString);

    IntToHeure(UnePeriode->HeureFin, HeureFin);

    strcat(TheString, " - ");
    strcat(TheString, HeureFin);
}

void ActualiserPeriode(struct PeriodeEtude* MaPeriode)
{
    time_t TimeActuel;
    struct tm * MaTm;

    time(&TimeActuel);
    MaTm = localtime(&TimeActuel);

    MaPeriode->HeureFin[0] = MaTm->tm_hour;
    MaPeriode->HeureFin[1] = MaTm->tm_min;
}

void AfficherListe(struct PeriodeEtude* PtrTete, int debutLigne, int tailleLigne)
{
    struct PeriodeEtude* currentPeriode;
    char UnePeriodeString[120], dayNew[10] = "", dayOld[10] = "";

    if(PtrTete == NULL)
        printf("Liste vide !\n");
    else
    {
        IHorizontal("Affichage d'une semaine", tailleLigne + 2*debutLigne);

        currentPeriode = PtrTete;
        while(currentPeriode->Next != NULL)
        {
            strcpy(dayOld, dayNew);
            DayToString(currentPeriode->Day, dayNew);

            if(strcmp(dayOld, dayNew) != 0)
                PrintfLigne(-1, debutLigne, dayNew, tailleLigne);

            PeriodeToString(currentPeriode, UnePeriodeString);
            PrintfLigne(-1, debutLigne + 5, UnePeriodeString, tailleLigne - 10);
            currentPeriode = currentPeriode->Next;
        }

        strcpy(dayOld, dayNew);
        DayToString(currentPeriode->Day, dayNew);

        if(strcmp(dayOld, dayNew) != 0)
            PrintfLigne(-1, debutLigne, dayNew, tailleLigne);

        PeriodeToString(currentPeriode, UnePeriodeString);
        PrintfLigne(-1, debutLigne + 5, UnePeriodeString, tailleLigne - 10);
    }
}

void DesallouerListe(struct PeriodeEtude** PtrTete)
{
    struct PeriodeEtude *currentPer, *nextPer;

    if(*PtrTete != NULL)
    {
        currentPer = *PtrTete;

        while(currentPer->Next != NULL)
        {
            nextPer = currentPer->Next;

            free(currentPer->Theme);
            free(currentPer);

            currentPer = nextPer;
        }

        free(currentPer->Theme);
        free(currentPer);

        *PtrTete = NULL;
    }
}

