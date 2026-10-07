#include <stdio.h>

#include "fichier.h"

int lire_fichier(const char *nom_de_fichier)
{
	char ligne[256];
	FILE *fichier = fopen(nom_de_fichier, "r");

	if (fichier == NULL) {
		perror(nom_de_fichier);
		return -1;
	}

	printf("Contenu du fichier %s :\n", nom_de_fichier);
	while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
		fputs(ligne, stdout);
	}

	if (ferror(fichier)) {
		perror("Erreur pendant la lecture");
		fclose(fichier);
		return -1;
	}

	if (fclose(fichier) == EOF) {
		perror("Erreur lors de la fermeture du fichier");
		return -1;
	}

	return 0;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
	FILE *fichier = fopen(nom_de_fichier, "a");

	if (fichier == NULL) {
		perror(nom_de_fichier);
		return -1;
	}

	if (fputs(message, fichier) == EOF || fputc('\n', fichier) == EOF) {
		perror("Erreur pendant l'écriture");
		fclose(fichier);
		return -1;
	}

	if (fclose(fichier) == EOF) {
		perror("Erreur lors de la fermeture du fichier");
		return -1;
	}

	return 0;
}
