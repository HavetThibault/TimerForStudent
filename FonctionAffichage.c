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

    for(i = 0; i < sizeEspace + 18; i++) // Car les bords font 9
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
        IHorizontal("MENU", LARGEUR_AFFICHAGE + 2*DEBUT_LIGNE);

        PrintfLigne(1, DEBUT_LIGNE, "Etudier", LARGEUR_AFFICHAGE);
        PrintfLigne(2, DEBUT_LIGNE, "Semaine", LARGEUR_AFFICHAGE);
        PrintfLigne(3, DEBUT_LIGNE, "Heures d'etudes", LARGEUR_AFFICHAGE);
        PrintfLigne(4, DEBUT_LIGNE, "Jeux", LARGEUR_AFFICHAGE);
        PrintfLigne(5, DEBUT_LIGNE, "Exit", LARGEUR_AFFICHAGE);

        IHorizontal("CHOIX", LARGEUR_AFFICHAGE + 2*DEBUT_LIGNE);

        printf("~~~~~~~~~                  CHOIX : ");

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
        IHorizontal("", LARGEUR_AFFICHAGE + 2*DEBUT_LIGNE);

        PrintfLigne(1, DEBUT_LIGNE, "Periode de 1h", LARGEUR_AFFICHAGE);
        PrintfLigne(2, DEBUT_LIGNE, "Periode de 2h", LARGEUR_AFFICHAGE);
        PrintfLigne(3, DEBUT_LIGNE, "CANCEL", LARGEUR_AFFICHAGE);

        IHorizontal("CHOIX", LARGEUR_AFFICHAGE + 2*DEBUT_LIGNE);

        printf("~~~~~~~~~                     CHOIX : ");

        fflush(stdin);
        scanf("%d", &choix);

    }while(choix < 1 || choix > 3);

    return choix;
}

void MenuTheme(char* theme)
{
        IHorizontal(NULL, LARGEUR_AFFICHAGE + 2*DEBUT_LIGNE);
        printf("~~~~~~~~~             Theme de l'etude : ");

        SaisieSansEnter(theme, 100);
}

void PrintfLigne(int num, int debutLigne, char* ligne, int longueurMaxLigne)
{
    char buffer[150];
    int i = 0, j, k, initDebutLigne = debutLigne;

    while(ligne[i] != '\0')
    {
        printf("~~~~~~~~~");

        for(j = 0; j < debutLigne; j++) // On ne compte pas les '~'
            buffer[j] = ' ';

        buffer[j] = '\0';
        printf(buffer);

        if(num > 0 && i == 0) // Si c'est la première itération
        {
            printf("%d. ", num);
            debutLigne += 3;
            longueurMaxLigne -= 3;
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
        strcat(buffer, "~~~~~~~~~\n");

        printf(buffer);
    }
}

void AfficherSemaine(int Date[3])
{
    int i;
    struct PeriodeEtude* ptrTete = NULL;

    if(IsDateValid(Date))
        RechercherPeriodeFichier(&ptrTete, Date);

    for(i = 0; i < 6; i++)
    {
        DecrementerDate(Date);

        RechercherPeriodeFichier(&ptrTete, Date);
    }

    if(ptrTete != NULL)
    {
        AfficherListe(ptrTete, DEBUT_LIGNE, LARGEUR_AFFICHAGE);

        DesallouerListe(&ptrTete);
    }
}


