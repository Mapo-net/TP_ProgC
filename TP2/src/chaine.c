#include <stdio.h>

int main(void)
{
    char premiere[100];
    char deuxieme[100];
    char copie[100];
    char concatenee[200];
    int longueur_premiere = 0;
    int longueur_deuxieme = 0;
    int longueur_totale = 0;

    printf("Entrez la premiere chaine : ");
    if (fgets(premiere, sizeof premiere, stdin) == NULL) {
        printf("Erreur de lecture.\n");
        return 1;
    }

    while (premiere[longueur_premiere] != '\0'
           && premiere[longueur_premiere] != '\n') {
        longueur_premiere++;
    }
    if (premiere[longueur_premiere] == '\n') {
        premiere[longueur_premiere] = '\0';
    } else {
        int caractere = getchar();
        if (caractere != '\n' && caractere != EOF) {
            printf("La chaine est trop longue (maximum 99 caracteres).\n");
            return 1;
        }
    }

    printf("Entrez la deuxieme chaine : ");
    if (fgets(deuxieme, sizeof deuxieme, stdin) == NULL) {
        printf("Erreur de lecture.\n");
        return 1;
    }

    while (deuxieme[longueur_deuxieme] != '\0'
           && deuxieme[longueur_deuxieme] != '\n') {
        longueur_deuxieme++;
    }
    if (deuxieme[longueur_deuxieme] == '\n') {
        deuxieme[longueur_deuxieme] = '\0';
    } else {
        int caractere = getchar();
        if (caractere != '\n' && caractere != EOF) {
            printf("La chaine est trop longue (maximum 99 caracteres).\n");
            return 1;
        }
    }

    int i = 0;
    while (premiere[i] != '\0') {
        copie[i] = premiere[i];
        concatenee[i] = premiere[i];
        i++;
    }
    copie[i] = '\0';
    concatenee[i] = '\0';

    i = 0;
    while (deuxieme[i] != '\0') {
        concatenee[longueur_premiere + i] = deuxieme[i];
        i++;
    }
    concatenee[longueur_premiere + i] = '\0';

    while (concatenee[longueur_totale] != '\0') {
        longueur_totale++;
    }

    printf("Longueur totale : %d\n", longueur_totale);
    printf("Copie de la premiere chaine : %s\n", copie);
    printf("Concatenation : %s\n", concatenee);

    return 0;
}