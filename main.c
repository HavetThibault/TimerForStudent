#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>
#include <signal.h>

#include "FonctionsAffichage.h"
#include "GestionPeriodes.h"
#include "GestionFichier.h"
#include "FonctionsUtilitaires.h"


int main()
{
    int wait, i, choix, sousChoix, Date[3];
    char Buffer1[100], Buffer2[100], theme[100];
    struct PeriodeEtude UnePeriode;
    time_t TimeActuel;
    struct tm * MaTm;

    for(choix = -1 ; choix != EXIT;)
    {
        switch(choix = Menu())
        {
            case ETUDIER:

                sousChoix = MenuEtude();

                MenuTheme(theme);

                InitPeriode(&UnePeriode, theme);

                srand(time(0));
                if(sousChoix == 1)
                    wait = rand() % 26 + 45;
                else
                    wait = rand() % 26 + 105;

                if(wait >= 60)
                {
                    strcpy(Buffer1, "\n\n------ Travail pendant ");
                    itoa((int)wait/60, Buffer2, 10);
                    strcat(Buffer1, Buffer2);

                    if(((int)wait/60) == 1)
                        strcat(Buffer1,  " heure et ");
                    else
                        strcat(Buffer1,  " heures et ");

                    itoa(wait % 60, Buffer2, 10);
                    strcat(Buffer1, Buffer2);
                    strcat(Buffer1,  " minutes ------\n");
                }
                else
                {
                    strcpy(Buffer1, "------ Travail pendant ");
                    itoa(wait % 60, Buffer2, 10);
                    strcat(Buffer1, Buffer2);
                    strcat(Buffer1,  " minutes ------\n");
                }
                MyPrintf(Buffer1);

                for(i = 1; i < 100; i++)
                {
                    Sleep(wait*60*10);
                    printf("%d%% \n", i);
                }
                ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

                Sleep(1000);
                printf("100%% \n");

                ActualiserPeriode(&UnePeriode);
                AjouterPeriodeFichier(&UnePeriode);

                wait = rand()%6 + 10;
                sprintf(Buffer1,"Travail termine ! On passe a la pause bien meritee de %d minutes ! \n", wait);
                MyPrintf(Buffer1);

                Sleep(wait*60*1000);

                ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
                MyPrintf("Pause terminee !\n");

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
