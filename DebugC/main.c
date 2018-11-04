#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grille.h"
#include "jeu.h"

#define GRILLEMAX 16

int main()
{
	srand(time(NULL)); // Init rand avec le le nombre de secondes �coul�es depuis le premier janvier 1970 au moment du lancement
	printf("--------------------- DEMINEUR ---------------------\n");

	int nbCols;
	int nbRows;

	printf("Veuillez choisir un nombre de lignes (max : %d) :  \n",GRILLEMAX);
	scanf_s("%d", &nbRows);

	printf("Veuillez choisir un nombre de colonnes (max : %d) : \n",GRILLEMAX);
	scanf_s("%d", &nbCols);

	if (nbRows > 0 && nbRows <= GRILLEMAX)
	{
		if (nbCols > 0 && nbCols <= GRILLEMAX)
		{
			Liste *maGrille = initialisation(nbRows, nbCols); // Initialisation de la grille
			remplissageGrille(nbRows, nbCols, maGrille); // On cr�er une grille de la taille donn�e
			printf("La partie commence ! \n\n\n");
			afficherGrille(maGrille); // Affichage de la grille pour d�buter la partie
			Play(nbRows, nbCols, maGrille); // On d�marre la partie en demandant au joueur de choisir o� jouer, la m�thode est r�cursive
		}
	}
	else
	{
		printf("Erreur dans le nombre de lignes et de colonnes, au revoir !");
		exit(0);
	}
	return 0;
}
