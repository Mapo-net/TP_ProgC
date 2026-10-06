#include <stdio.h>

#include "operator.h"

static void exercice_4_1(void)
{
	int num1;
	int num2;
	int resultat;
	char op;
	StatutCalcul statut;

	printf("Entrez num1 : ");
	if (scanf("%d", &num1) != 1) {
		printf("Saisie invalide.\n");
		return;
	}

	printf("Entrez num2 : ");
	if (scanf("%d", &num2) != 1) {
		printf("Saisie invalide.\n");
		return;
	}

	printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
	if (scanf(" %c", &op) != 1) {
		printf("Saisie invalide.\n");
		return;
	}

	statut = calculer(num1, num2, op, &resultat);
	if (statut == CALCUL_DIVISION_PAR_ZERO) {
		printf("Erreur : division ou modulo par zéro.\n");
	} else if (statut == CALCUL_OPERATEUR_INCONNU) {
		printf("Opérateur non pris en charge.\n");
	} else {
		printf("Résultat : %d\n", resultat);
	}
}

int main(void)
{
	int choix;

	printf("Choisissez l'exercice à lancer :\n");
	printf("1. Calcul avec opérateurs\n");
	printf("Votre choix : ");
	if (scanf("%d", &choix) != 1) {
		printf("Saisie invalide.\n");
		return 1;
	}

	switch (choix) {
	case 1:
		exercice_4_1();
		break;
	default:
		printf("Exercice non disponible.\n");
		return 1;
	}

	return 0;
}

