#include "FonctionsUtilitaires.h"

void SaisieSansEnter(char* ZoneARemplir, int tailleSaisie)
{
    int i;
    fflush(stdin);
    fgets(ZoneARemplir, tailleSaisie, stdin);

    for(i = 0; i < tailleSaisie && ZoneARemplir[i] != '\n' && ZoneARemplir[i] != '\0'; i++);

    ZoneARemplir[i] = '\0';

    fflush(stdin);
}

void DateToString(int Date[3], char* TheString)
{
    char Entier[5];

    itoa(Date[0], Entier, 10); // Jour
    if(Date[0] < 10)
    {
        strcpy(TheString, "0");
        strcat(TheString, Entier);
    }
    else
        strcpy(TheString, Entier);

    strcat(TheString, "-");

    itoa(Date[1], Entier, 10); // Mois
    if(Date[1] < 10)
        strcat(TheString, "0");

    strcat(TheString, Entier);

    strcat(TheString, "-");

    itoa(Date[2], Entier, 10); // Annee
    strcat(TheString, Entier);
}

void IntToHeure(int Heure[2], char* TheString)
{
    char Entier[5];

    itoa(Heure[0], Entier,10);
    strcpy(TheString, Entier);
    strcat(TheString, "h");
    itoa(Heure[1], Entier,10);

    if(Heure[1] < 10) // Si le nombre de minutes ne contient qu'un chiffre
        strcat(TheString, "0");
    strcat(TheString, Entier);
}

int CompareDate(int D1[3], int D2[3])
{
    int result;

    if(D1[2] < D2[2]) // Comparaison année
        result = -1;
    else if(D1[2] > D2[2])
        result = 1;
    else if(D1[1] < D2[1]) // Comparaison mois
        result = -1;
    else if(D1[1] > D2[1])
        result = 1;
    else if(D1[0] < D2[0]) // Comparaison jour
        result = -1;
    else if(D1[0] > D2[0])
        result = 1;
    else
        result = 0;

    return result;
}

//to check the year is leap or not
//if the year is a leap year return 1
int isleap(int y)
{
   if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
      return 1;
   else
      return 0;
}

//Function to check the date is valid or not
int IsDateValid(int Date[3])
{
    int d = Date[0], m = Date[1], y = Date[2];
    if(y < min_yr || y > max_yr)
        return 0;
    if(m < 1 || m > 12)
        return 0;
    if(d < 1 || d > 31)
        return 0;

    //Now we will check date according to month
    if( m == 2 )
    {
        if(isleap(y))
        {
            if(d <= 29)
                return 1;
            else
                return 0;
        }
    }

    //April, June, September and November are with 30 days
    if ( m == 4 || m == 6 || m == 9 || m == 11 )
    {
        if(d <= 30)
            return 1;
        else
            return 0;
    }

    return 1;
}

int DecrementerDate(int Date[3])
{
    do
    {
        Date[0]--;
        if(Date[0] <= 0)
        {
            Date[0] = 31;
            Date[1]--;
            if(Date[1] <= 0)
            {
                Date[1] = 12;
                Date[2]--;
            }
        }
    }while(IsDateValid(Date) == 0);
}

void DayToString(int day, char* dayString)
{
    switch(day)
    {
        case 1:
            strcpy(dayString, "Lundi");
            break;
        case 2:
            strcpy(dayString, "Mardi");
            break;
        case 3:
            strcpy(dayString, "Mercredi");
            break;
        case 4:
            strcpy(dayString, "Jeudi");
            break;
        case 5:
            strcpy(dayString, "Vendredi");
            break;
        case 6:
            strcpy(dayString, "Samedi");
            break;
        case 0:
            strcpy(dayString, "Dimanche");
            break;
        default:
            strcpy(dayString, "Probleme de date ?");
            break;
    }
}

void MonthToString(int month, char* monthstring)
{
    switch(month)
    {
        case 1:
            strcpy(monthstring, "Janvier");
            break;
        case 2:
            strcpy(monthstring, "Fevrier");
            break;
        case 3:
            strcpy(monthstring, "Mars");
            break;
        case 4:
            strcpy(monthstring, "Avril");
            break;
        case 5:
            strcpy(monthstring, "Mai");
            break;
        case 6:
            strcpy(monthstring, "Juin");
            break;
        case 7:
            strcpy(monthstring, "Juillet");
            break;
        case 8:
            strcpy(monthstring, "Aout");
            break;
        case 9:
            strcpy(monthstring, "Septembre");
            break;
        case 10:
            strcpy(monthstring, "Octobre");
            break;
        case 11:
            strcpy(monthstring, "Novembre");
            break;
        case 12:
            strcpy(monthstring, "Decembre");
            break;
        default:
            printf("Month = %d\n", month);
            strcpy(monthstring, "Probleme de mois ?");
    }
}
