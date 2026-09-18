#include <stdio.h>
#include <string.h>

int main() {

    char charactere = 'A';

    short petitNombre = 25;

    int nombre = 163;

    long int grandNombre = 4866329;

    long long int tresGrandNombre = 6595322221863;

    float nombreVirgule = 3.9;

    double grandNombreVirgule = 923.846;

    long double tresGrandNombreVirgule = 8452542.84966841;

    printf("Charactère : %c\n", charactere);
    printf("Petit nombre (short) : %hd\n", petitNombre);
    printf("Nombre (int) : %d\n", nombre);
    printf("Grand nombre (long int) : %ld\n", grandNombre);
    printf("Très grand nombre (long long int) : %lld\n", tresGrandNombre);
    printf("Nombre à virgule (float) : %f\n", nombreVirgule);
    printf("Grand nombre à virgule (double) : %lf\n", grandNombreVirgule);
    printf("Très grand nombre à virgule (long double) : %Lf\n", tresGrandNombreVirgule);

    return 0;
}