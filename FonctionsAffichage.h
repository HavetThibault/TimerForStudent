#ifndef AFFICHAGE
#define AFFICHAGE

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "FonctionsUtilitaires.h"
#include "GestionPeriodes.h"
#include "FonctionsUtilitaires.h"
#include "GestionFichier.h"

#define ETUDIER 1
#define SEMAINE 2
#define HEURE_ETUDES 3
#define JEUX 4
#define EXIT 5

void MyPrintf(char* chaineAAfficher);
int Menu();
int MenuEtude();
void MenuTheme(char* theme);
void PrintfLigne(int num, int debutLigne, char* ligne, int longueurMaxLigne);
void AfficherSemaine(int Date[3]); // Affiche les 7j précédent
void IHorizontal(char* Message, int sizeEspace);

#endif // AFFICHAGE
