#include <stdio.h>

#include "fichier.h"
#include "liste.h"
#include "operator.h"

static void vider_fin_de_ligne(void)
{
	int caractere;

	while ((caractere = getchar()) != '\n' && caractere != EOF) {
	}
}

static int lire_ligne(char *texte, size_t taille)
{
	int caractere;
	int i;

	if (fgets(texte, (int)taille, stdin) == NULL) {
		return 0;
	}

	for (i = 0; texte[i] != '\0' && texte[i] != '\n'; i++) {
	}
	if (texte[i] == '\n') {
		texte[i] = '\0';
	} else {
		while ((caractere = getchar()) != '\n' && caractere != EOF) {
		}
	}

	return 1;
}

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

static void exercice_4_2(void)
{
	int choix;
	char nom_de_fichier[256];
	char message[1024];

	for (;;) {
		printf("\nQue souhaitez-vous faire ?\n");
		printf("1. Lire un fichier\n");
		printf("2. Écrire dans un fichier\n");
		printf("3. Quitter\n");
		printf("Votre choix : ");

		if (scanf("%d", &choix) != 1) {
			printf("Saisie invalide.\n");
			vider_fin_de_ligne();
			continue;
		}
		vider_fin_de_ligne();

		if (choix == 3) {
			break;
		}
		if (choix != 1 && choix != 2) {
			printf("Choix invalide.\n");
			continue;
		}

		if (choix == 1) {
			printf("Entrez le nom du fichier à lire : ");
			if (!lire_ligne(nom_de_fichier, sizeof(nom_de_fichier))) {
				printf("Impossible de lire le nom du fichier.\n");
				break;
			}
			lire_fichier(nom_de_fichier);
		} else {
			printf("Entrez le nom du fichier dans lequel écrire : ");
			if (!lire_ligne(nom_de_fichier, sizeof(nom_de_fichier))) {
				printf("Impossible de lire le nom du fichier.\n");
				break;
			}

			printf("Entrez le message à écrire : ");
			if (!lire_ligne(message, sizeof(message))) {
				printf("Impossible de lire le message.\n");
				break;
			}

			if (ecrire_dans_fichier(nom_de_fichier, message) == 0) {
				printf("Le message a été écrit dans le fichier %s.\n",
				       nom_de_fichier);
			}
		}
	}
}

static void exercice_4_7(void)
{
	const struct couleur couleurs[10] = {
		{0xFF, 0x00, 0x00, 0xFF},
		{0x00, 0xFF, 0x00, 0xFF},
		{0x00, 0x00, 0xFF, 0xFF},
		{0xFF, 0xFF, 0x00, 0xFF},
		{0xFF, 0x00, 0xFF, 0xFF},
		{0x00, 0xFF, 0xFF, 0xFF},
		{0x80, 0x40, 0x20, 0xFF},
		{0x20, 0x40, 0x80, 0xFF},
		{0x10, 0x20, 0x30, 0xFF},
		{0xAA, 0x55, 0x33, 0xFF}
	};
	struct liste_couleurs ma_liste;

	init_liste(&ma_liste);
	for (int i = 0; i < 10; i++) {
		if (!insertion(&couleurs[i], &ma_liste)) {
			fprintf(stderr, "Erreur : impossible d'ajouter une couleur.\n");
			liberer_liste(&ma_liste);
			return;
		}
	}

	printf("Liste des couleurs :\n");
	parcours(&ma_liste);
	liberer_liste(&ma_liste);
}

int main(void)
{
	int choix;

	printf("Choisissez l'exercice à lancer :\n");
	printf("1. Calcul avec opérateurs\n");
	printf("2. Gestion de fichiers\n");
	printf("3. Liste de couleurs\n");
	printf("Votre choix : ");
	if (scanf("%d", &choix) != 1) {
		printf("Saisie invalide.\n");
		return 1;
	}

	switch (choix) {
	case 1:
		exercice_4_1();
		break;
	case 2:
		exercice_4_2();
		break;
	case 3:
		exercice_4_7();
		break;
	default:
		printf("Exercice non disponible.\n");
		return 1;
	}

	return 0;
}

