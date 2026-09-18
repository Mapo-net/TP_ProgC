#include <stdio.h>

int main() {
	int nombres[] = {0, 4096, 65536, 65535, 1024};
	int nombreDeNombres = sizeof(nombres) / sizeof(nombres[0]);

	for (int index = 0; index < nombreDeNombres; index++) {
		int valeur = nombres[index];
		int bits[32];
		int nombreDeBits = 0;

		if (valeur == 0) {
			bits[nombreDeBits++] = 0;
		} else {
			for (; valeur > 0; valeur /= 2) {
				bits[nombreDeBits++] = valeur % 2;
			}
		}

		printf("%d en binaire : ", nombres[index]);
		for (int bit = nombreDeBits - 1; bit >= 0; bit--) {
			printf("%d", bits[bit]);
		}
		printf("\n");
	}

	return 0;
}