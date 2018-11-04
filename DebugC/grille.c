#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

Liste *initialisation(int _nbRow, int _nbCol)
{
	Liste *grille = malloc(sizeof(*grille));
	Element *element = malloc(sizeof(*element));

	if (grille == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}

	element->row = 0;
	element->col = 0;
	element->statut = 'c';
	element->mine = isMined();
	element->numCase = 1;
	element->suivant = NULL;

	grille->premier = element; // le premier element de la grille est element que l'on vient de cr�er
	grille->dernier = element; // le dernier element de la grille est element que l'on vient de cr�er
	grille->nbRow = _nbRow;    // On r�cup�re le nombre de ligne que l'utilisateur � choisi et on l'insert dans les infos de la Grille
	grille->nbCol = _nbCol;    // On r�cup�re le nombre de colonnes que l'utilisateur � choisi et on l'insert dans les infos de la Grille
	grille->nbCases = 1;       // On met le nombre de case de la grille �gale � 1 car on vient de cr�er une case

	return grille;
}

int isMined()
{
	int random = rand() % 100; // al�atoire entre 0 et 100;
	if (random > 50)           // si > � 50 on dit qu'il y a une mine
	{
		return 1;
	}
	return 0; // sinon on retroune qu'il n'y a pas de mine dans cette case
}

void insertionFin(Liste *grille, int _row, int _col, char _statut, int _mine)
{
	Element *nouvelleCase = malloc(sizeof(*nouvelleCase));

	if (grille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	// On initialise notre nouvelle case
	nouvelleCase->row = _row;
	nouvelleCase->col = _col;
	nouvelleCase->statut = _statut;
	nouvelleCase->mine = _mine;
	nouvelleCase->numCase = grille->nbCases + 1;
	nouvelleCase->suivant = NULL;

	
	grille->dernier->suivant = nouvelleCase; // On change le NULL du dernier �lement de la liste et on le fait pointer sur notre �lement
	grille->dernier = nouvelleCase; // Le dernier �l�ment est �gal � notre �lement
	grille->nbCases++; // augmente le compteur d'�lement de la liste de 1
}

void insertionDebut(Liste *grille, int _row, int _col, char _statut, int _mine) // Insertion d'un �l�ment au d�but de la grille
{
	/* Cr�ation du nouvelle case */
	Element *nouvelleCase = malloc(sizeof(*nouvelleCase));
	if (grille == NULL || nouvelleCase == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouvelleCase->row = _row;
	nouvelleCase->col = _col;
	nouvelleCase->statut = _statut;
	nouvelleCase->mine = _mine;
	nouvelleCase->numCase = grille->nbCases + 1;

	/* Insertion de l'�lement au d�but de la liste */
	nouvelleCase->suivant = grille->premier;
	grille->premier = nouvelleCase;
	grille->nbCases++; // augmente le compteur d'�lement de la liste de 1
}

void afficherGrille(Liste *grille) // G�re l'affichage de la grille
{
	if (grille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = grille->premier;

	while (actuel != NULL)
	{
		switch (actuel->statut)
		{
		case 'c':
			if (actuel->suivant != NULL)
			{
				if (actuel->row < actuel->suivant->row) // Si la case d'apr�s est sur une autre ligne on fait un retour � la ligne
				{
					printf("|%d|\n", actuel->mine); // permet de tester le message de victoire en affichant o� sont les mines [A mettre en commentaire]
					//printf("|%d|\n", actuel->numCase);
				}
				else
				{
					//printf("|%d|", actuel->numCase);
					printf("|%d|", actuel->mine); // permet de tester le message de victoire en affichant o� sont les mines [A mettre en commentaire]
				}
			}	
			else
			{
				printf("|%d|\n", actuel->numCase);
			}
			break;
		case 'f':
			if (actuel->suivant != NULL)
			{
				if (actuel->row < actuel->suivant->row) // Si la case d'apr�s est sur une autre ligne on fait un retour � la ligne
				{
					printf("|F|\n", actuel->mine); // permet de tester le message de victoire en affichant o� sont les mines [A mettre en commentaire]
					//printf("|F|\n");
				}
				else
				{
					printf("|F|", actuel->mine); // permet de tester le message de victoire en affichant o� sont les mines [A mettre en commentaire]
					//printf("|F|");
				}
			}
			else
			{
				printf("|F|\n");
			}			
			break;
		case 'o':
			if (actuel->mine == 1) // Si la case ouverte est min�
			{
				printf("|X|");
			}
			else
			{
				int nbBombes = checkForBombes(grille, actuel->row, actuel->col);
				if (actuel->suivant != NULL)
				{
					if (actuel->row < actuel->suivant->row) // Si la case d'apr�s est sur une autre ligne on fait un retour � la ligne
					{
						printf("[-%d-]\n", nbBombes);
					}
					else
					{
						printf("[-%d-]", nbBombes);
					}
				}
				else
				{
					printf("[-%d-]\n", nbBombes);
				}				
			}
			break;
		default:
			break;
		}
		actuel = actuel->suivant;
	}
}

Element *findCase(Liste *maGrille, int _numCase)
{
	if (maGrille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *actuel = maGrille->premier;
	while (actuel != NULL)
	{
		if (actuel->numCase == _numCase)
		{
			return actuel;
		}
		actuel = actuel->suivant;
	}
	if (actuel = maGrille->premier)
	{
		actuel = NULL;
		return actuel;
	}
	return actuel;
}

void remplissageGrille(int nbRows, int nbCols, Liste *maGrille)
{
	int r;
	int c;
	for (r = 0; r < nbRows; r++)
	{
		for (c = 0; c < nbCols; c++)
		{
			if (r == 0 && c == 0)
			{
				c++;
				insertionFin(maGrille, r, c, 'c', isMined());
			}
			else
				insertionFin(maGrille, r, c, 'c', isMined());
		}
	}
}



// -------------------------------------------------- TEST --------------------------------------
void testAffichage(Liste *grille)
{
	if (grille == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Element *elem = grille->premier;

	while (elem != NULL)
	{
		printf("|row : %d // col : %d // statut : %c // mined : %d // numCase : %d |\n", elem->row, elem->col, elem->statut, elem->mine, elem->numCase);
		elem = elem->suivant;
	}
	printf("-Fin-\n");
}

