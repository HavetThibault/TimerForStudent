#ifndef GESTIONPERIODES
#define GESTIONPERIODES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "FonctionsUtilitaires.h"

struct PeriodeEtude
{
    int Date[3];
    int Day;
    int HeureDebut[2];
    int HeureFin[2];
    char* Theme;
    struct PeriodeEtude* Next;
};

// Affichage

void PeriodeToStringSansDate(struct PeriodeEtude* UnePeriode, char* TheString);
void PeriodeToHeure(struct PeriodeEtude* UnePeriode, char* TheString);
void PeriodeToString(struct PeriodeEtude* UnePeriode, char* TheString);

// Gestion liste
void Ajouter(struct PeriodeEtude** PtrTete, struct PeriodeEtude* newPeriode);
struct PeriodeEtude* LastPeriode(struct PeriodeEtude* PtrTete);
void AfficherListe(struct PeriodeEtude* PtrTete, int debutLigne, int tailleLigne);
void DesallouerListe(struct PeriodeEtude** PtrTete);

// Gestion PeriodeEtude
int ComparePeriodesEtudeDateHeure(struct PeriodeEtude* P1, struct PeriodeEtude* P2);
void InitPeriode(struct PeriodeEtude* MaPeriode, char* theme);
void ActualiserPeriode(struct PeriodeEtude* MaPeriode);


#endif // GESTIONPERIODES
