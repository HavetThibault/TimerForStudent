#ifndef UTILITAIRES
#define UTILITAIRES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_yr 9999
#define min_yr 1800

void SaisieSansEnter(char* ZoneARemplir, int tailleSaisie);
void IntToHeure(int Heure[2], char* TheString);
void DateToString(int Date[3], char* TheString);
int CompareDate(int D1[3], int D2[3]);
int isleap(int y) ;
int IsDateValid(int Date[3]);
void DecrementerDate(int Date[3]);
void DayToString(int day, char* dayString);
void MonthToString(int month, char* monthstring);
void MinutesToHeure(int minutes, int heure[2]);

#endif // UTILITAIRES


