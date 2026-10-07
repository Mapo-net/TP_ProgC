#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "operator.h"

static int convertir_entier(const char *texte, int *nombre)
{
	char *fin;
	long valeur;

	errno = 0;
	valeur = strtol(texte, &fin, 10);
	if (texte == fin || *fin != '\0' || errno == ERANGE
	    || valeur < INT_MIN || valeur > INT_MAX) {
		return 0;
	}

	*nombre = (int)valeur;
	return 1;
}

int main(int argc, char *argv[])
{
	int num1;
	int num2;
	int resultat;
	char op;
	StatutCalcul statut;

	if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0') {
		fprintf(stderr, "Usage : %s OPERATEUR NOMBRE1 NOMBRE2\n", argv[0]);
		return 1;
	}

	if (!convertir_entier(argv[2], &num1)
	    || !convertir_entier(argv[3], &num2)) {
		fprintf(stderr, "Erreur : les deux opérandes doivent être des entiers.\n");
		return 1;
	}

	op = argv[1][0];
	statut = calculer(num1, num2, op, &resultat);
	if (statut == CALCUL_DIVISION_PAR_ZERO) {
		fprintf(stderr, "Erreur : division ou modulo par zéro.\n");
		return 1;
	}
	if (statut == CALCUL_OPERATEUR_INCONNU) {
		fprintf(stderr, "Erreur : opérateur non pris en charge : %c\n", op);
		return 1;
	}

	printf("Résultat : %d\n", resultat);
	return 0;
}
