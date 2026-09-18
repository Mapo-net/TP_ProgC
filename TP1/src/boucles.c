#include <stdio.h>
#include <string.h>

int main() {
	int compteur = 5;

	if (compteur >= 10) {
		printf("La valeur de compteur doit etre strictement inferieure a 10.\n");
		return 1;
	}

	for (int ligne = 1; ligne <= compteur; ligne++) {
		for (int colonne = 1; colonne <= ligne; colonne++) {
			if (ligne == 1 || ligne == compteur || colonne == 1 || colonne == ligne) {
				printf("* ");
			} else {
				printf("# ");
			}
		}
		printf("\n");
	}

	return 0;
}