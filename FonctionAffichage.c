#include "FonctionsAffichage.h"

void MyPrintf(char* chaineAAfficher)
{
    int size = strlen(chaineAAfficher);
    for(int i = 0; i < size; i++)
    {
        printf("%c", chaineAAfficher[i]);
        Sleep(10);
    }
}

void IHorizontal(char* Message, int sizeEspace)
{
    char buffer[200];
    int i, offsetDebutMessage;

    printf("~~~~~~~~~");
    for(i = 0; i < sizeEspace; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~\n");

    printf("~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 4; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 12; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 24; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~~~~~~~~~~~\n");

    for(i = 0; i < sizeEspace + 18; i++)
        buffer[i] = '~';
    buffer[i] = '\n';
    buffer[i+1] = '\0';

    printf(buffer);

    if(Message != NULL)
    {
        offsetDebutMessage = (sizeEspace + 18 - strlen(Message) - 2)/2;
        for(i = 0; i < offsetDebutMessage; i++)
            buffer[i] = '~';
        buffer[i] = ' ';
        buffer[i + 1] = '\0';

        printf(buffer);
        printf(Message);

        buffer[0] = ' ';
        buffer[i] = '~';
        if(strlen(Message) % 2 == 1)
            buffer[++i] = '~';
        buffer[i+1] = '\n';
        buffer[i+2] = '\0';
        printf(buffer);
    }
    else
    {
        for(i = 0; i < sizeEspace + 18; i++)
            buffer[i] = '~';
        buffer[i] = '\n';
        buffer[i+1] = '\0';

        printf(buffer);
    }

    for(i = 0; i < sizeEspace + 18; i++)
        buffer[i] = '~';
    buffer[i] = '\n';
    buffer[i+1] = '\0';

    printf(buffer);

    printf("~~~~~~~~~~~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 24; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 12; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~~~~~\n");

    printf("~~~~~~~~~~~");
    for(i = 0; i < sizeEspace - 4; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~~~\n");

    printf("~~~~~~~~~");
    for(i = 0; i < sizeEspace; i++)
        buffer[i] = ' ';

    buffer[i] = '\0';
    printf(buffer);
    printf("~~~~~~~~~\n");
}

int Menu()
{
    int choix;

    do
    {
        printf("~~~                                              ~~~\n");
        printf("~~~~                                            ~~~~\n");
        printf("~~~~~~~                                      ~~~~~~~\n");
        printf("~~~~~~~~~~~~~                          ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                          ~~~~~~~~~~~~~\n");
        printf("~~~~~~~                                      ~~~~~~~\n");
        printf("~~~~                                            ~~~~\n");
        printf("~~~                1. Etudier                    ~~~\n");
        printf("~~                 2. Semaine                     ~~\n");
        printf("~~                 3. Heures d'etudes             ~~\n");
        printf("~~                 4. Jeux                        ~~\n");
        printf("~~~                5. Exit                       ~~~\n");
        printf("~~~~                                            ~~~~\n");
        printf("~~~~~~~                                      ~~~~~~~\n");
        printf("~~~~~~~~~~~~~                          ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                          ~~~~~~~~~~~~~\n");
        printf("~~~~~~~                                      ~~~~~~~\n");
        printf("~~~~                                            ~~~~\n");
        printf("~~~                                              ~~~\n");
        printf("                     CHOIX : ");

        fflush(stdin);
        scanf("%d", &choix);

    }while(choix < 0 || choix > 5);

    return choix;
}

int MenuEtude()
{
    int choix;

    do
    {
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("~~~~~~~~~~~                                                    ~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~                                                      ~~~~~~~~~~\n");
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("~~~~~~~~~                 1. Periode de 1h                       ~~~~~~~~~\n");
        printf("~~~~~~~~~                 2. Periode de 2h                       ~~~~~~~~~\n");
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("~~~~~~~~~~                                                      ~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~                                                    ~~~~~~~~~~~\n");
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("                         CHOIX : ");

        fflush(stdin);
        scanf("%d", &choix);

    }while(choix < 1 || choix > 2);

    return choix;
}

void MenuTheme(char* theme)
{
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("~~~~~~~~~~~                                                    ~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~                                    ~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~                                                ~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~                                                    ~~~~~~~~~~~\n");
        printf("~~~~~~~~~                                                        ~~~~~~~~~\n");
        printf("               Theme de l'etude : ");

        SaisieSansEnter(theme, 100);
}

void PrintfLigne(int num, int debutLigne, char* ligne, int longueurMaxLigne)
{
    char buffer[150];
    int i = 0, j, k, initDebutLigne = debutLigne;

    while(ligne[i] != '\0')
    {
        printf("~~~~~~~~");

        for(j = 0; j < debutLigne; j++) // On ne compte pas les '~'
            buffer[j] = ' ';

        buffer[j] = '\0';
        printf(buffer);

        if(num > 0 && i == 0) // Si c'est la première itération
        {
            printf("%d. ", num);
            debutLigne += 3;
        }

        for(j = 0; j < longueurMaxLigne && ligne[i] != '\0'; j++, i++)
            buffer[j] = ligne[i];

        if(ligne[i] == '\0') // Alors il faut remplir de ' '
        {
            while(j < longueurMaxLigne)
            {
                buffer[j] = ' ';
                j++;
            }
        }

        for(k = 0; k < initDebutLigne; k++, j++)
            buffer[j] = ' ';

        buffer[j] = '\0';
        strcat(buffer, "~~~~~~~~\n");

        printf(buffer);
    }
}

void AfficherSemaine(int Date[3])
{
    int i;
    struct PeriodeEtude* ptrTete = NULL;

    if(IsDateValid(Date))
    {
        RechercherPeriodeFichier(&ptrTete, Date);

        if(ptrTete != NULL)
        {
            AfficherListe(ptrTete, 10, 50);

            DesallouerListe(&ptrTete);
        }
    }

    for(i = 0; i < 6; i++)
    {
        DecrementerDate(Date);

        RechercherPeriodeFichier(&ptrTete, Date);

        if(ptrTete != NULL)
        {
            AfficherListe(ptrTete, 10, 50);

            DesallouerListe(&ptrTete);
        }
    }
}


