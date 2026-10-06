#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

void afficher_tableau(const int tableau[])
{
	for (int i = 0; i < TAILLE; i++) {
		printf("%d ", tableau[i]);
	}
	printf("\n");
}

int main(void)
{
	int tableau[TAILLE];
	int echange;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < TAILLE; i++) {
		tableau[i] = rand() % 2001 - 1000;
	}

	printf("Tableau non trié :\n");
	afficher_tableau(tableau);

	for (int i = 0; i < TAILLE - 1; i++) {
		for (int j = 0; j < TAILLE - 1 - i; j++) {
			if (tableau[j] > tableau[j + 1]) {
				echange = tableau[j];
				tableau[j] = tableau[j + 1];
				tableau[j + 1] = echange;
			}
		}
	}

	printf("Tableau trié par ordre croissant :\n");
	afficher_tableau(tableau);

	return 0;
}
