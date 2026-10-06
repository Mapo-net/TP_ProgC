#include <stdio.h>

int main(void)
{
    int n;

    printf("Entrez n (entre 0 et 46) : ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 46) {
        printf("Veuillez saisir un entier entre 0 et 46.\n");
        return 1;
    }

    int precedent = 0;
    int courant = 1;

    printf("Suite jusqu'a U%d : 0", n);
    if (n >= 1) {
        printf(", 1");
    }

    for (int i = 2; i <= n; i++) {
        int suivant = precedent + courant;
        printf(", %d", suivant);
        precedent = courant;
        courant = suivant;
    }

    printf("\n");
    return 0;
}