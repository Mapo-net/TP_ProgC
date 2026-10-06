#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void)
{
	int tableau[TAILLE];
	int recherche;
	int present = 0;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < TAILLE; i++) {
		tableau[i] = rand() % 2001 - 1000;
	}

	printf("Tableau :\n");
	for (int i = 0; i < TAILLE; i++) {
		printf("%d ", tableau[i]);
	}
	printf("\n\nEntrez l'entier que vous souhaitez chercher : ");

	if (scanf("%d", &recherche) != 1) {
		fprintf(stderr, "Saisie invalide.\n");
		return 1;
	}

	for (int i = 0; i < TAILLE; i++) {
		if (tableau[i] == recherche) {
			present = 1;
			break;
		}
	}

	if (present) {
		printf("\nRésultat : entier présent\n");
	} else {
		printf("\nRésultat : entier absent\n");
	}

	return 0;
}
