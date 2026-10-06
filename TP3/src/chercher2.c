#include <stdio.h>

#define NOMBRE_PHRASES 10
#define TAILLE_ENTREE 256

int phrases_identiques(const char *premiere, const char *seconde)
{
	while (*premiere != '\0' && *seconde != '\0' && *premiere == *seconde) {
		premiere++;
		seconde++;
	}

	return *premiere == *seconde;
}

int main(void)
{
	const char *phrases[NOMBRE_PHRASES] = {
		"Bonjour, comment ça va ?",
		"Le temps est magnifique aujourd'hui.",
		"C'est une belle journée.",
		"La programmation en C est amusante.",
		"Les tableaux en C sont puissants.",
		"Les pointeurs en C peuvent être déroutants.",
		"Il fait beau dehors.",
		"La recherche dans un tableau est intéressante.",
		"Les structures de données sont importantes.",
		"Programmer en C, c'est génial."
	};
	char recherche[TAILLE_ENTREE];
	int trouvee = 0;

	printf("Entrez une phrase à chercher : ");
	if (fgets(recherche, TAILLE_ENTREE, stdin) == NULL) {
		fprintf(stderr, "Impossible de lire la phrase.\n");
		return 1;
	}

	for (int i = 0; recherche[i] != '\0'; i++) {
		if (recherche[i] == '\n') {
			recherche[i] = '\0';
			break;
		}
	}

	for (int i = 0; i < NOMBRE_PHRASES; i++) {
		if (phrases_identiques(recherche, phrases[i])) {
			trouvee = 1;
			break;
		}
	}

	if (trouvee) {
		printf("Phrase trouvée\n");
	} else {
		printf("Phrase non trouvée\n");
	}

	return 0;
}
