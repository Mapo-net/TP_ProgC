#include <stdio.h>

unsigned long long factorielle(unsigned int nombre)
{
	if (nombre == 0) {
		return 1;
	}

	return nombre * factorielle(nombre - 1);
}

int main(void)
{
	const unsigned int valeurs[] = {0, 1, 5, 10, 20};
	const unsigned int nombre_valeurs =
		(unsigned int)(sizeof(valeurs) / sizeof(valeurs[0]));

	for (unsigned int i = 0; i < nombre_valeurs; i++) {
		printf("%u! = %llu\n", valeurs[i], factorielle(valeurs[i]));
	}

	return 0;
}
