#include <stdio.h>

int main(void)
{
    char noms[5][30] = {
        "Martin", "Bernard", "Dubois", "Thomas", "Robert"
    };
    char prenoms[5][30] = {
        "Alice", "Hugo", "Lea", "Adam", "Emma"
    };
    char adresses[5][60] = {
        "12 rue des Lilas", "8 avenue Victor-Hugo", "4 rue du Port",
        "25 boulevard de la Gare", "3 place du Marche"
    };
    float notes_programmation[5] = {15.5f, 12.0f, 17.0f, 14.5f, 16.0f};
    float notes_systeme[5] = {14.0f, 13.5f, 16.0f, 11.0f, 18.0f};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d\n", i + 1);
        printf("Nom : %s\n", noms[i]);
        printf("Prenom : %s\n", prenoms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Note en programmation : %.1f\n", notes_programmation[i]);
        printf("Note en systeme d'exploitation : %.1f\n\n",
               notes_systeme[i]);
    }

    return 0;
}