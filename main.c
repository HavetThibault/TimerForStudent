#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>
#include <signal.h>
#include <pthread.h>

#include "FonctionsAffichage.h"
#include "GestionPeriodes.h"
#include "GestionFichier.h"
#include "FonctionsUtilitaires.h"

void FctAffichagePourcent(int * Wait);
COORD GetCursorPosition() ;
void SetCursorPosition(int XPos, int YPos) ;
void HandlerSIGINT(int);

COORD CoordPourcent;
COORD CoordScanf;

pthread_t threadAffichagePourcent;
pthread_t threadPrincipal;

pthread_mutex_t mutexInputUtilisateur;

int InputUtilisateur;
int ChoixUniquementThreadAffichage;



int main()
{
    int wait, choix, sousChoix, Date[3];
    float wait1Pourcent;
    char Buffer1[100], Buffer2[100], theme[100];
    struct PeriodeEtude UnePeriode;
    time_t TimeActuel;
    struct tm * MaTm;
    struct timespec Temps;

    pthread_mutex_init(&mutexInputUtilisateur, NULL);

    threadPrincipal = pthread_self();

    signal(SIGINT, HandlerSIGINT);

    system("color 8F");

    for(choix = -1 ; choix != EXIT;)
    {
        switch(choix = Menu())
        {
            case ETUDIER:

                sousChoix = MenuEtude();

                if(sousChoix == 1 || sousChoix == 2) // S'il vaut 3 alors CANCEl
                {
                    MenuTheme(theme);

                    IHorizontal(NULL, 2*DEBUT_LIGNE + LARGEUR_AFFICHAGE);

                    InitPeriode(&UnePeriode, theme);

                    srand(time(0));

                    if(sousChoix == 1)
                        wait = rand() % 26 + 45;
                    else if(sousChoix == 2)
                        wait = rand() % 26 + 105;
                    if(wait >= 60)
                    {
                        strcpy(Buffer1, "------------------ Travail pendant ");
                        itoa((int)wait/60, Buffer2, 10);
                        strcat(Buffer1, Buffer2);

                        if(((int)wait/60) == 1)
                            strcat(Buffer1,  " heure et ");
                        else
                            strcat(Buffer1,  " heures et ");

                        itoa(wait % 60, Buffer2, 10);
                        strcat(Buffer1, Buffer2);
                        strcat(Buffer1,  " minutes ------------------");
                    }
                    else
                    {
                        strcpy(Buffer1, "------------------ Travail pendant ");
                        itoa(wait % 60, Buffer2, 10);
                        strcat(Buffer1, Buffer2);
                        strcat(Buffer1,  " minutes ------------------");
                    }
                    PrintfLigne(-1, DEBUT_LIGNE, Buffer1, LARGEUR_AFFICHAGE);
                    PrintfLigne(-1, DEBUT_LIGNE, " ", LARGEUR_AFFICHAGE);
                    CoordPourcent = GetCursorPosition();

                    CoordPourcent.X += 50; // Pour avoir la ligne du '-' ci-dessous pour que le thread sache ou ecrire
                    PrintfLigne(-1, DEBUT_LIGNE + 29, "-   -", LARGEUR_AFFICHAGE - 58);

                    IHorizontal(NULL, 2*DEBUT_LIGNE + LARGEUR_AFFICHAGE);

                    PrintfLigne(1, DEBUT_LIGNE, "Interrompre et sauvegarder", LARGEUR_AFFICHAGE);
                    PrintfLigne(2, DEBUT_LIGNE, "Interrompre et supprimer", LARGEUR_AFFICHAGE);
                    PrintfLigne(-1, DEBUT_LIGNE, NULL, LARGEUR_AFFICHAGE);
                    CoordScanf = GetCursorPosition();
                    CoordScanf.X += 38;
                    PrintfLigne(-1, DEBUT_LIGNE+10, "CHOIX : ", LARGEUR_AFFICHAGE-20);

                    IHorizontal(NULL, 2*DEBUT_LIGNE + LARGEUR_AFFICHAGE);

                    pthread_create(&threadAffichagePourcent, NULL, (void * (*) (void *)) FctAffichagePourcent, NULL);

                    pthread_mutex_lock(&mutexInputUtilisateur);
                    InputUtilisateur = -1;
                    pthread_mutex_unlock(&mutexInputUtilisateur);

                    SetCursorPosition(CoordScanf.X, CoordScanf.Y);

                    // Calcul du temps pris pour faire 1 %
                    wait1Pourcent = wait * 60 * 0.01 ;
                    Temps.tv_sec = (int) (wait1Pourcent / 100);
                    Temps.tv_nsec = (wait1Pourcent - Temps.tv_sec) * 1000 * 1000 * 10; // car on fait 100 nanosleep

                    SetCursorPosition(CoordPourcent.X, CoordPourcent.Y);
                    printf("0%% -");
                    SetCursorPosition(CoordScanf.X, CoordScanf.Y);

                    pthread_mutex_lock(&mutexInputUtilisateur);
                    for(int i = 1; i < 101 && InputUtilisateur == -1; i++)
                    {
                        for(int j = 0; j < 100 && InputUtilisateur == -1; j++)
                        {
                            pthread_mutex_unlock(&mutexInputUtilisateur);
                            nanosleep(&Temps,NULL);
                            pthread_mutex_lock(&mutexInputUtilisateur);
                        }
                        pthread_mutex_unlock(&mutexInputUtilisateur);


                        SetCursorPosition(CoordPourcent.X, CoordPourcent.Y);
                        printf("%d%% -", i);
                        SetCursorPosition(CoordScanf.X, CoordScanf.Y);

                        pthread_mutex_lock(&mutexInputUtilisateur);
                    }

                    printf("\n");

                    if(InputUtilisateur == -1)
                    {
                        pthread_mutex_unlock(&mutexInputUtilisateur);

                        ActualiserPeriode(&UnePeriode);
                        AjouterPeriodeFichier(&UnePeriode);

                        pthread_cancel(threadAffichagePourcent);
                        ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
                    }
                    else
                    {
                        switch(InputUtilisateur)
                        {
                            case 1 :
                                ActualiserPeriode(&UnePeriode);
                                AjouterPeriodeFichier(&UnePeriode);

                                break;

                            case 2 :    // on ne veut pas enregistrer
                                break;
                        }
                        pthread_mutex_unlock(&mutexInputUtilisateur);
                    }
                }
                break;

            case SEMAINE:

                TimeActuel = time(NULL);
                MaTm = localtime(&TimeActuel);

                Date[0] = MaTm->tm_mday;
                Date[1] = MaTm->tm_mon + 1;
                Date[2] = MaTm->tm_year + 1900;

                AfficherSemaine(Date);

                break;

            case EXIT:

                break;
        }
    }

    return 0;
}

void FctAffichagePourcent(int * Wait)
{
    int ChoixUniquementThreadAffichage = -1;

    // Autorisation de mourrir sur demande et instantanément

    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    do
    {
        scanf("%d", &ChoixUniquementThreadAffichage);
    }while(ChoixUniquementThreadAffichage != 1 && ChoixUniquementThreadAffichage != 2);

    pthread_mutex_lock(&mutexInputUtilisateur);
    InputUtilisateur = ChoixUniquementThreadAffichage;
    pthread_mutex_unlock(&mutexInputUtilisateur);
}

COORD GetCursorPosition()
{
   HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
   PCONSOLE_SCREEN_BUFFER_INFO bufferInfo = malloc(sizeof(PCONSOLE_SCREEN_BUFFER_INFO));
   GetConsoleScreenBufferInfo(h,bufferInfo);
   return bufferInfo->dwCursorPosition;
}

void SetCursorPosition(int XPos, int YPos)
{
   COORD coord;
   coord.X = XPos; coord.Y = YPos;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void HandlerSIGINT(int signal)
{
    ChoixUniquementThreadAffichage = 2;
}
