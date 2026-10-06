#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int entiers[11];
    float reels[11];
    int *p_entier = entiers;
    float *p_reel = reels;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 11; i++) {
        *p_entier = rand() % 100;
        *p_reel = (float)(rand() % 1000) / 100.0f;
        p_entier++;
        p_reel++;
    }

    printf("Tableau d'entiers avant multiplication par 3 :\n");
    p_entier = entiers;
    for (int i = 0; i < 11; i++) {
        printf("%d%s", *p_entier, i < 10 ? ", " : "\n");
        p_entier++;
    }

    printf("Tableau de reels avant multiplication par 3 :\n");
    p_reel = reels;
    for (int i = 0; i < 11; i++) {
        printf("%.2f%s", (double)*p_reel, i < 10 ? ", " : "\n");
        p_reel++;
    }

    p_entier = entiers;
    p_reel = reels;
    for (int i = 0; i < 11; i++) {
        if (i % 2 == 0) {
            *p_entier *= 3;
            *p_reel *= 3.0f;
        }
        p_entier++;
        p_reel++;
    }

    printf("Tableau d'entiers apres multiplication par 3 :\n");
    p_entier = entiers;
    for (int i = 0; i < 11; i++) {
        printf("%d%s", *p_entier, i < 10 ? ", " : "\n");
        p_entier++;
    }

    printf("Tableau de reels apres multiplication par 3 :\n");
    p_reel = reels;
    for (int i = 0; i < 11; i++) {
        printf("%.2f%s", (double)*p_reel, i < 10 ? ", " : "\n");
        p_reel++;
    }

    return 0;
}