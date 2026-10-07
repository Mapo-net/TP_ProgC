#include <stdio.h>

#include "fichier.h"

#define NOMBRE_ETUDIANTS 5

struct Etudiant {
	char nom[30];
	char prenom[30];
	char adresse[100];
	float note_programmation;
	float note_systeme;
};

static void vider_fin_de_ligne(void)
{
	int caractere;

	while ((caractere = getchar()) != '\n' && caractere != EOF) {
	}
}

int main(void)
{
	struct Etudiant etudiants[NOMBRE_ETUDIANTS];
	char ligne[320];

	for (int i = 0; i < NOMBRE_ETUDIANTS; i++) {
		printf("Entrez les détails de l'étudiant.e %d :\n", i + 1);

		printf("Nom : ");
		if (scanf(" %29[^\n]", etudiants[i].nom) != 1) {
			fprintf(stderr, "Saisie du nom invalide.\n");
			return 1;
		}
		vider_fin_de_ligne();

		printf("Prénom : ");
		if (scanf(" %29[^\n]", etudiants[i].prenom) != 1) {
			fprintf(stderr, "Saisie du prénom invalide.\n");
			return 1;
		}
		vider_fin_de_ligne();

		printf("Adresse : ");
		if (scanf(" %99[^\n]", etudiants[i].adresse) != 1) {
			fprintf(stderr, "Saisie de l'adresse invalide.\n");
			return 1;
		}
		vider_fin_de_ligne();

		printf("Note 1 : ");
		if (scanf("%f", &etudiants[i].note_programmation) != 1) {
			fprintf(stderr, "Saisie de la note 1 invalide.\n");
			return 1;
		}
		vider_fin_de_ligne();

		printf("Note 2 : ");
		if (scanf("%f", &etudiants[i].note_systeme) != 1) {
			fprintf(stderr, "Saisie de la note 2 invalide.\n");
			return 1;
		}
		vider_fin_de_ligne();

		if (snprintf(ligne, sizeof(ligne), "%s;%s;%s;%.2f;%.2f",
			     etudiants[i].nom, etudiants[i].prenom,
			     etudiants[i].adresse,
			     etudiants[i].note_programmation,
			     etudiants[i].note_systeme) < 0) {
			fprintf(stderr, "Impossible de formater les données.\n");
			return 1;
		}

		if (ecrire_dans_fichier("etudiant.txt", ligne) != 0) {
			return 1;
		}
	}

	printf("Les détails des étudiants ont été enregistrés dans le fichier etudiant.txt.\n");
	return 0;
}
