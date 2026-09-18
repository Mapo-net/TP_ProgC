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

    printf("%ld\n",sizeof(charactere));
    printf("%ld\n",sizeof(petitNombre));
    printf("%ld\n",sizeof(nombre));
    printf("%ld\n",sizeof(grandNombre));
    printf("%ld\n",sizeof(tresGrandNombre));
    printf("%ld\n",sizeof(nombreVirgule));
    printf("%ld\n",sizeof(grandNombreVirgule));
    printf("%ld\n",sizeof(tresGrandNombreVirgule));


    return 0;
}

