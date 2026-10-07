#include <stdio.h>
#include <string.h>

#define TAILLE_NOM_FICHIER 256
#define TAILLE_PHRASE 256
#define TAILLE_LIGNE 4096

static int lire_saisie(const char *invite, char *texte, size_t taille)
{
	int caractere;
	size_t longueur;

	printf("%s", invite);
	if (fgets(texte, (int)taille, stdin) == NULL) {
		return 0;
	}

	longueur = strcspn(texte, "\n");
	if (texte[longueur] == '\n') {
		texte[longueur] = '\0';
	} else if (!feof(stdin)) {
		while ((caractere = getchar()) != '\n' && caractere != EOF) {
		}
		fprintf(stderr, "Saisie trop longue.\n");
		return 0;
	}

	return 1;
}

static size_t compter_occurrences(const char *ligne, const char *phrase)
{
	const char *position = ligne;
	size_t occurrences = 0;

	while ((position = strstr(position, phrase)) != NULL) {
		occurrences++;
		position++;
	}

	return occurrences;
}

int main(int argc, char *argv[])
{
	char nom_fichier[TAILLE_NOM_FICHIER];
	char phrase[TAILLE_PHRASE];
	char ligne[TAILLE_LIGNE];
	const char *chemin;
	FILE *fichier;
	size_t numero_ligne = 0;
	int resultat = 0;
	int occurrences_trouvees = 0;

	if (argc == 2) {
		chemin = argv[1];
	} else if (argc == 1) {
		if (!lire_saisie("Entrez le nom du fichier : ", nom_fichier,
				 sizeof(nom_fichier))) {
			return 1;
		}
		chemin = nom_fichier;
	} else {
		fprintf(stderr, "Usage : %s [nom_du_fichier]\n", argv[0]);
		return 1;
	}

	if (chemin[0] == '\0') {
		fprintf(stderr, "Le nom du fichier ne peut pas être vide.\n");
		return 1;
	}

	if (!lire_saisie("Entrez la phrase que vous souhaitez rechercher : ",
			 phrase, sizeof(phrase))) {
		return 1;
	}
	if (phrase[0] == '\0') {
		fprintf(stderr, "La phrase recherchée ne peut pas être vide.\n");
		return 1;
	}

	fichier = fopen(chemin, "r");
	if (fichier == NULL) {
		perror(chemin);
		return 1;
	}

	printf("\nRésultats de la recherche :\n");
	while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
		size_t occurrences;

		numero_ligne++;
		occurrences = compter_occurrences(ligne, phrase);
		if (occurrences > 0) {
			printf("Ligne %zu, %zu fois\n", numero_ligne, occurrences);
			occurrences_trouvees = 1;
		}
	}

	if (ferror(fichier)) {
		perror("Erreur pendant la lecture du fichier");
		resultat = 1;
	} else if (!occurrences_trouvees) {
		printf("Phrase absente du fichier.\n");
	}

	if (fclose(fichier) == EOF) {
		perror("Erreur lors de la fermeture du fichier");
		resultat = 1;
	}

	return resultat;
}
