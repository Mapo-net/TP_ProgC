#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    uint32_t d = UINT32_C(0x90001000);
    unsigned int bit4 = (unsigned int)((d >> 28) & 1u);
    unsigned int bit20 = (unsigned int)((d >> 12) & 1u);
    unsigned int resultat = bit4 == 1u && bit20 == 1u;

    printf("Resultat : %u\n", resultat);
    printf("Valeur de d : %" PRIu32 "\n", d);
    printf("Representation binaire de d : ");
    for (unsigned int position = 32u; position > 0u; position--) {
        printf("%u", (unsigned int)((d >> (position - 1u)) & 1u));
    }
    printf("\n");

    return 0;
}