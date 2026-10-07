#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "repertoire.h"

void lire_dossier(const char *nom_du_repertoire)
{
    DIR *repertoire;
    struct dirent *entree;

    repertoire = opendir(nom_du_repertoire);
    if (repertoire == NULL) {
        perror(nom_du_repertoire);
        return;
    }

    printf("Contenu du dossier %s :\n", nom_du_repertoire);
    while ((entree = readdir(repertoire)) != NULL) {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", entree->d_name);
    }

    closedir(repertoire);
}
