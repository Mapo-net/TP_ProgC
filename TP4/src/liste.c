#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

void init_liste(struct liste_couleurs *liste)
{
	if (liste != NULL) {
		liste->tete = NULL;
	}
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
	struct noeud_couleur *nouveau;
	struct noeud_couleur **position;

	if (couleur == NULL || liste == NULL) {
		return 0;
	}

	nouveau = malloc(sizeof(*nouveau));
	if (nouveau == NULL) {
		return 0;
	}

	nouveau->couleur = *couleur;
	nouveau->suivant = NULL;

	position = &liste->tete;
	while (*position != NULL) {
		position = &(*position)->suivant;
	}
	*position = nouveau;

	return 1;
}

void parcours(const struct liste_couleurs *liste)
{
	const struct noeud_couleur *courant;

	if (liste == NULL) {
		return;
	}

	for (courant = liste->tete; courant != NULL; courant = courant->suivant) {
		printf("0x%02X 0x%02X 0x%02X 0x%02X\n",
		       (unsigned int)courant->couleur.rouge,
		       (unsigned int)courant->couleur.vert,
		       (unsigned int)courant->couleur.bleu,
		       (unsigned int)courant->couleur.alpha);
	}
}

void liberer_liste(struct liste_couleurs *liste)
{
	struct noeud_couleur *courant;

	if (liste == NULL) {
		return;
	}

	while (liste->tete != NULL) {
		courant = liste->tete;
		liste->tete = courant->suivant;
		free(courant);
	}
}
