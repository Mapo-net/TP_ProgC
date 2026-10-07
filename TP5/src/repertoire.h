#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <stdio.h>

void lire_dossier(const char *nom_du_repertoire);
void lire_dossier_recursif(const char *nom_du_repertoire);
void lire_dossier_iteratif(const char *nom_du_repertoire);
void lire_dossier_iteratif_vers(FILE *sortie, const char *nom_du_repertoire);

#endif
