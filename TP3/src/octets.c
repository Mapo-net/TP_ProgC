#include <stdio.h>

void afficher_octets(const char *type, const void *variable, size_t taille)
{
	const unsigned char *octets = (const unsigned char *)variable;

	printf("Octets de %s :\n ", type);
	for (size_t i = 0; i < taille; i++) {
		printf("%02x ", (unsigned int)*(octets + i));
	}
	printf("\n\n");
}

int main(void)
{
	short valeur_short = 0x0203;
	int valeur_int = 0x01020304;
	long int valeur_long = 0x01020304L;
	float valeur_float = 1.0f;
	double valeur_double = 1.0;
	long double valeur_long_double = 1.0L;
	unsigned int test_ordre = 1;
	const unsigned char *octets_test = (const unsigned char *)&test_ordre;

	if (*octets_test == 1) {
		printf("Ordre des octets : petit-boutiste\n\n");
	} else if (*(octets_test + sizeof(test_ordre) - 1) == 1) {
		printf("Ordre des octets : gros-boutiste\n\n");
	} else {
		printf("Ordre des octets : non standard\n\n");
	}

	afficher_octets("short", &valeur_short, sizeof(valeur_short));
	afficher_octets("int", &valeur_int, sizeof(valeur_int));
	afficher_octets("long int", &valeur_long, sizeof(valeur_long));
	afficher_octets("float", &valeur_float, sizeof(valeur_float));
	afficher_octets("double", &valeur_double, sizeof(valeur_double));
	afficher_octets("long double", &valeur_long_double,
			 sizeof(valeur_long_double));

	return 0;
}
