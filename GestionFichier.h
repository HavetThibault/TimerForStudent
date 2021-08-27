#ifndef GESTIONFICHIER
#define GESTIONFICHIER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "GestionPeriodes.h"
#include "FonctionsUtilitaires.h"

#define REPERTOIRE_ENREGISTREMENT "Enregistrement\\"

int AjouterPeriodeFichier(struct PeriodeEtude* PeriodeSave);
void RechercherPeriodeFichier(struct PeriodeEtude** ptrTete, int Date[3]);
void NomFichierDate(int Date[3], char* pathFichier);

#endif // GESTIONFICHIER
