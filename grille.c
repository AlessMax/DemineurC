#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grille.h"

Liste *initialisation(int _nbRow, int _nbCol)
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if(liste == NULL || element == NULL)
    {
       exit(EXIT_FAILURE);
    }

    element->row = 0;
    element->col = 0;
    element->statut = 'n';
    element->mine = 0;
    element->suivant = NULL;
    liste->premier = element;
    liste->nbRow = _nbRow;
    liste->nbCol = _nbCol;
    liste->nbCases = 1;

    return liste;
}

int isMined(int nb)
{
    
    int random = rand()%nb;

    if (random>0)
    {
        return 0 ; //vide
    }
    else
    {
    return 1; //bombe 
    }
}

void insertion(Liste *liste, int _row, int _col, char _statut, int _mine)
{
    /* Création du nouvelle case */
    Element *nouvelleCase = malloc(sizeof(*nouvelleCase));
    if(liste == NULL || nouvelleCase == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouvelleCase->row = _row;
    nouvelleCase->col = _col;
    nouvelleCase->statut = _statut;
    nouvelleCase->mine = _mine;

    /* Insertion de l'élement au début de la liste */
    nouvelleCase->suivant = liste->premier;
    liste->premier = nouvelleCase;
    liste->nbCases++;
}

void insertionMines(Liste *liste, int nbmines)
{ 
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *tmp = liste->premier; //premier element 

    while(tmp != NULL)
    {
        if(nbmines > 0)
        {
            tmp->mine = rand()%(liste->nbRow);
            nbmines--;
        }
        tmp = tmp-> suivant;
    }
    
}

void suppression(Liste *liste)
{
   
    if(liste->premier != NULL)
    {
        Element *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherGrille(Liste *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->premier;
    int compteur = liste->nbCases;
    while(actuel != NULL)
    {
        printf("case %d , ligne : %d // col : %d // statut : %c // isMined : %d\n \n", compteur, actuel->row, actuel->col, actuel->statut, actuel->mine);
        actuel = actuel->suivant;
        compteur--;
    }
    printf("NULL \n");
}