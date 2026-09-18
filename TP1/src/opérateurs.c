#include <stdio.h>
#include <string.h>

int main() {
    int a = 16;
    int b = 3;
    
    int addition = a + b;
    int soustraction = a - b;
    int multiplication = a * b;
    float division = (float) a / b;
    int modulo = a % b;
    int comparaisonEgal = a == b;
    int comparaisonSup = a > b;

    printf("addition : %d\n", addition);
    printf("soustraction : %d\n", soustraction);
    printf("multiplication : %d\n", multiplication);
    printf("division : %f\n", division);
    printf("modulo : %d\n", modulo);
    printf("a est egal a b : %d\n", comparaisonEgal);
    printf("a est superieur a b : %d\n", comparaisonSup);

    return 0;
}