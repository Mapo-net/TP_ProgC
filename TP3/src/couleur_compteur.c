#include <stdint.h>
#include <stdio.h>

#define TAILLE_TABLEAU 100
#define NB_COULEURS_PALETTE 6

typedef struct {
	uint8_t rouge;
	uint8_t vert;
	uint8_t bleu;
	uint8_t alpha;
} Couleur;

typedef struct {
	Couleur couleur;
	int occurrences;
} CouleurComptee;

int couleurs_identiques(Couleur premiere, Couleur seconde)
{
	return premiere.rouge == seconde.rouge
		&& premiere.vert == seconde.vert
		&& premiere.bleu == seconde.bleu
		&& premiere.alpha == seconde.alpha;
}

int main(void)
{
	const Couleur palette[NB_COULEURS_PALETTE] = {
		{0xff, 0x23, 0x23, 0x45},
		{0xff, 0x00, 0x23, 0x12},
		{0x12, 0x34, 0x56, 0xff},
		{0x00, 0x00, 0x00, 0xff},
		{0xff, 0xff, 0xff, 0xff},
		{0x80, 0x40, 0x20, 0xff}
	};
	Couleur tableau[TAILLE_TABLEAU];
	CouleurComptee distinctes[TAILLE_TABLEAU];
	int nombre_distinctes = 0;

	for (int i = 0; i < TAILLE_TABLEAU; i++) {
		tableau[i] = palette[i % NB_COULEURS_PALETTE];
	}

	for (int i = 0; i < TAILLE_TABLEAU; i++) {
		int trouvee = 0;

		for (int j = 0; j < nombre_distinctes; j++) {
			if (couleurs_identiques(tableau[i], distinctes[j].couleur)) {
				distinctes[j].occurrences++;
				trouvee = 1;
				break;
			}
		}

		if (!trouvee) {
			distinctes[nombre_distinctes].couleur = tableau[i];
			distinctes[nombre_distinctes].occurrences = 1;
			nombre_distinctes++;
		}
	}

	for (int i = 0; i < nombre_distinctes; i++) {
		Couleur couleur = distinctes[i].couleur;

		printf("0x%02x 0x%02x 0x%02x 0x%02x : %d\n",
		       (unsigned int)couleur.rouge,
		       (unsigned int)couleur.vert,
		       (unsigned int)couleur.bleu,
		       (unsigned int)couleur.alpha,
		       distinctes[i].occurrences);
	}

	return 0;
}
