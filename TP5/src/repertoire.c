#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "repertoire.h"

static void parcourir_dossier(const char *chemin)
{
    DIR *repertoire = opendir(chemin);
    struct dirent *entree;

    if (repertoire == NULL) {
        perror(chemin);
        return;
    }

    while ((entree = readdir(repertoire)) != NULL) {
        struct stat informations;
        size_t longueur_chemin;
        size_t longueur_nom;
        int separateur;
        char *chemin_entree;

        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }

        longueur_chemin = strlen(chemin);
        longueur_nom = strlen(entree->d_name);
        separateur = longueur_chemin > 0 && chemin[longueur_chemin - 1] != '/';
        chemin_entree = malloc(longueur_chemin + separateur + longueur_nom + 1);
        if (chemin_entree == NULL) {
            perror("malloc");
            break;
        }

        strcpy(chemin_entree, chemin);
        if (separateur) {
            chemin_entree[longueur_chemin] = '/';
            chemin_entree[longueur_chemin + 1] = '\0';
        }
        strcat(chemin_entree, entree->d_name);
        printf("%s\n", chemin_entree);

        if (lstat(chemin_entree, &informations) == 0 && S_ISDIR(informations.st_mode)) {
            parcourir_dossier(chemin_entree);
        }

        free(chemin_entree);
    }

    closedir(repertoire);
}

void lire_dossier_recursif(const char *nom_du_repertoire)
{
    parcourir_dossier(nom_du_repertoire);
}

void lire_dossier_iteratif(const char *nom_du_repertoire)
{
    size_t capacite = 16;
    size_t nombre_chemins = 0;
    int erreur_memoire = 0;
    char **pile = malloc(capacite * sizeof(*pile));

    if (pile == NULL) {
        perror("malloc");
        return;
    }

    pile[nombre_chemins] = malloc(strlen(nom_du_repertoire) + 1);
    if (pile[nombre_chemins] == NULL) {
        perror("malloc");
        free(pile);
        return;
    }
    strcpy(pile[nombre_chemins], nom_du_repertoire);
    nombre_chemins++;

    while (nombre_chemins > 0 && !erreur_memoire) {
        char *chemin = pile[--nombre_chemins];
        DIR *repertoire = opendir(chemin);
        struct dirent *entree;

        if (repertoire == NULL) {
            perror(chemin);
            free(chemin);
            continue;
        }

        while ((entree = readdir(repertoire)) != NULL) {
            struct stat informations;
            size_t longueur_chemin;
            size_t longueur_nom;
            int separateur;
            char *chemin_entree;

            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
                continue;
            }

            longueur_chemin = strlen(chemin);
            longueur_nom = strlen(entree->d_name);
            separateur = longueur_chemin > 0 && chemin[longueur_chemin - 1] != '/';
            chemin_entree = malloc(longueur_chemin + separateur + longueur_nom + 1);
            if (chemin_entree == NULL) {
                perror("malloc");
                erreur_memoire = 1;
                break;
            }

            strcpy(chemin_entree, chemin);
            if (separateur) {
                chemin_entree[longueur_chemin] = '/';
                chemin_entree[longueur_chemin + 1] = '\0';
            }
            strcat(chemin_entree, entree->d_name);
            printf("%s\n", chemin_entree);

            if (lstat(chemin_entree, &informations) == 0 && S_ISDIR(informations.st_mode)) {
                if (nombre_chemins == capacite) {
                    size_t nouvelle_capacite = capacite * 2;
                    char **nouvelle_pile = realloc(pile, nouvelle_capacite * sizeof(*pile));

                    if (nouvelle_pile == NULL) {
                        perror("realloc");
                        free(chemin_entree);
                        erreur_memoire = 1;
                        break;
                    }
                    pile = nouvelle_pile;
                    capacite = nouvelle_capacite;
                }
                pile[nombre_chemins++] = chemin_entree;
            } else {
                free(chemin_entree);
            }
        }

        closedir(repertoire);
        free(chemin);
    }

    while (nombre_chemins > 0) {
        free(pile[--nombre_chemins]);
    }
    free(pile);
}

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
