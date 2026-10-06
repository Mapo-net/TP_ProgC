#include <stdio.h>

static void afficher_adresse_et_octets(const char *nom, const void *variable,
                                       size_t taille)
{
    const unsigned char *octets = variable;

    printf("Adresse de %s : %p, Valeur en hexadecimal : 0x", nom,
           (void *)variable);
    for (size_t i = 0; i < taille; i++) {
        printf("%02X", (unsigned int)octets[i]);
    }
    printf("\n");
}

int main(void)
{
    char charactere = 'A';
    short petitNombre = 25;
    int nombre = 163;
    long int grandNombre = 4866329L;
    long long int tresGrandNombre = 6595322221863LL;
    float nombreVirgule = 3.9f;
    double grandNombreVirgule = 923.846;
    long double tresGrandNombreVirgule = 8452542.84966841L;

    char *pCharactere = &charactere;
    short *pPetitNombre = &petitNombre;
    int *pNombre = &nombre;
    long int *pGrandNombre = &grandNombre;
    long long int *pTresGrandNombre = &tresGrandNombre;
    float *pNombreVirgule = &nombreVirgule;
    double *pGrandNombreVirgule = &grandNombreVirgule;
    long double *pTresGrandNombreVirgule = &tresGrandNombreVirgule;

    printf("Avant la manipulation :\n");
    afficher_adresse_et_octets("charactere", &charactere,
                               sizeof charactere);
    afficher_adresse_et_octets("petitNombre", &petitNombre,
                               sizeof petitNombre);
    afficher_adresse_et_octets("nombre", &nombre, sizeof nombre);
    afficher_adresse_et_octets("grandNombre", &grandNombre,
                               sizeof grandNombre);
    afficher_adresse_et_octets("tresGrandNombre", &tresGrandNombre,
                               sizeof tresGrandNombre);
    afficher_adresse_et_octets("nombreVirgule", &nombreVirgule,
                               sizeof nombreVirgule);
    afficher_adresse_et_octets("grandNombreVirgule", &grandNombreVirgule,
                               sizeof grandNombreVirgule);
    afficher_adresse_et_octets("tresGrandNombreVirgule",
                               &tresGrandNombreVirgule,
                               sizeof tresGrandNombreVirgule);

    (*pCharactere)++;
    (*pPetitNombre)++;
    (*pNombre)++;
    (*pGrandNombre)++;
    (*pTresGrandNombre)++;
    (*pNombreVirgule) += 1.0f;
    (*pGrandNombreVirgule) += 1.0;
    (*pTresGrandNombreVirgule) += 1.0L;

    printf("\nApres la manipulation par les pointeurs :\n");
    afficher_adresse_et_octets("charactere", &charactere,
                               sizeof charactere);
    afficher_adresse_et_octets("petitNombre", &petitNombre,
                               sizeof petitNombre);
    afficher_adresse_et_octets("nombre", &nombre, sizeof nombre);
    afficher_adresse_et_octets("grandNombre", &grandNombre,
                               sizeof grandNombre);
    afficher_adresse_et_octets("tresGrandNombre", &tresGrandNombre,
                               sizeof tresGrandNombre);
    afficher_adresse_et_octets("nombreVirgule", &nombreVirgule,
                               sizeof nombreVirgule);
    afficher_adresse_et_octets("grandNombreVirgule", &grandNombreVirgule,
                               sizeof grandNombreVirgule);
    afficher_adresse_et_octets("tresGrandNombreVirgule",
                               &tresGrandNombreVirgule,
                               sizeof tresGrandNombreVirgule);

    return 0;
}