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
    char UnePeriodeString[120], JourMois[40] = "", AncienJourMois[40] = "";

    if(PtrTete == NULL)
        IHorizontal("Aucune plage de travail ces 7 derniers jours", tailleLigne + 2*debutLigne);
    else
    {
        IHorizontal("Affichage d'une semaine", tailleLigne + 2*debutLigne);

        currentPeriode = PtrTete;
        while(currentPeriode->Next != NULL)
        {
            strcpy(AncienJourMois, JourMois);
            PeriodeToJourMois(currentPeriode, JourMois);

            if(strcmp(AncienJourMois, JourMois) != 0)
                PrintfLigne(-1, debutLigne, JourMois, tailleLigne);

            PeriodeToStringSansDate(currentPeriode, UnePeriodeString);
            PrintfLigne(-1, debutLigne + 5, UnePeriodeString, tailleLigne - 10);
            currentPeriode = currentPeriode->Next;
        }

        strcpy(AncienJourMois, JourMois);
        PeriodeToJourMois(currentPeriode, JourMois);

        if(strcmp(AncienJourMois, JourMois) != 0)
            PrintfLigne(-1, debutLigne, JourMois, tailleLigne);

        PeriodeToStringSansDate(currentPeriode, UnePeriodeString);
        PrintfLigne(-1, debutLigne + 5, UnePeriodeString, tailleLigne - 10);
    }
}


void AfficherHeureJournaliere(struct PeriodeEtude* PtrTete, int debutLigne, int tailleLigne)
{
    struct PeriodeEtude* currentPeriode;
    char heureTravail[40], JourMois[40] = "", AncienJourMois[40] = "";
    int heures[2];
    int totalDayWorkMinutes = 0;

    if(PtrTete == NULL)
        IHorizontal("Aucune plage de travail ces 7 derniers jours", tailleLigne + 2*debutLigne);
    else
    {
        IHorizontal("Affichage des heures de la semaine", tailleLigne + 2*debutLigne);

        currentPeriode = PtrTete;
        while(currentPeriode != NULL)
        {
            strcpy(AncienJourMois, JourMois);
            PeriodeToJourMois(currentPeriode, JourMois);

            if(strcmp(AncienJourMois, JourMois) != 0)
            {
                if(totalDayWorkMinutes != 0)
                {
                    MinutesToHeure(totalDayWorkMinutes, heures);
                    sprintf(heureTravail, "%d heure(s) et %d minutes", heures[0], heures[1]);
                    PrintfLigne(-1, debutLigne + 5, heureTravail, tailleLigne - 10);
                    totalDayWorkMinutes = 0;
                }

                PrintfLigne(-1, debutLigne, JourMois, tailleLigne);
            }

            totalDayWorkMinutes += GetMinutesOfWork(currentPeriode);
            currentPeriode = currentPeriode->Next;
        }

        if(totalDayWorkMinutes != 0)
        {
            MinutesToHeure(totalDayWorkMinutes, heures);
            sprintf(heureTravail, "%d heure(s) et %d minutes", heures[0], heures[1]);
            PrintfLigne(-1, debutLigne + 5, heureTravail, tailleLigne - 10);
        }
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


void PeriodeToJourMois(struct PeriodeEtude* UnePeriode, char* TheString)
{
    char month[12], dayNumber[3];

    DayToString(UnePeriode->Day, TheString);

    MonthToString(UnePeriode->Date[1], month);

    strcat(TheString, " ");

    itoa(UnePeriode->Date[0], dayNumber, 10);

    strcat(TheString, dayNumber);

    strcat(TheString, " ");

    strcat(TheString, month);
}

void CopyDate(struct PeriodeEtude* periodeEtude, int* copiedDate)
{
    copiedDate[0] = periodeEtude->Date[0];
    copiedDate[1] = periodeEtude->Date[1];
    copiedDate[2] = periodeEtude->Date[2];
}

int GetMinutesOfWork(struct PeriodeEtude* periodeEtude)
{
    int minutesOfWork = 0;
    if(periodeEtude->HeureFin[0] < periodeEtude->HeureDebut[0]) // Si jamais on etudie entre 23h et 1h du mat
    {
        minutesOfWork += (23 - periodeEtude->HeureDebut[0]) * 60;
        minutesOfWork += 60 - periodeEtude->HeureDebut[1];

        minutesOfWork += periodeEtude->HeureFin[0] * 60;
        minutesOfWork += periodeEtude->HeureFin[1];
    }
    else
    {
        minutesOfWork += (60 * periodeEtude->HeureFin[0] + periodeEtude->HeureFin[1]) - (60 * periodeEtude->HeureDebut[0] + periodeEtude->HeureDebut[1]);
    }

    return minutesOfWork;
}
