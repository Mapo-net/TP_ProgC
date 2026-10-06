#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[100];
    float note_programmation;
    float note_systeme;
};

int main(void)
{
    struct Etudiant etudiants[5];

    strcpy(etudiants[0].nom, "Dupont");
    strcpy(etudiants[0].prenom, "Marie");
    strcpy(etudiants[0].adresse, "20, Boulevard Niels Bohr, Lyon");
    etudiants[0].note_programmation = 16.5f;
    etudiants[0].note_systeme = 12.1f;

    strcpy(etudiants[1].nom, "Martin");
    strcpy(etudiants[1].prenom, "Pierre");
    strcpy(etudiants[1].adresse, "22, Boulevard Niels Bohr, Lyon");
    etudiants[1].note_programmation = 14.0f;
    etudiants[1].note_systeme = 14.1f;

    strcpy(etudiants[2].nom, "Bernard");
    strcpy(etudiants[2].prenom, "Alice");
    strcpy(etudiants[2].adresse, "8 avenue Victor-Hugo, Lyon");
    etudiants[2].note_programmation = 15.0f;
    etudiants[2].note_systeme = 13.5f;

    strcpy(etudiants[3].nom, "Dubois");
    strcpy(etudiants[3].prenom, "Hugo");
    strcpy(etudiants[3].adresse, "4 rue du Port, Lyon");
    etudiants[3].note_programmation = 17.0f;
    etudiants[3].note_systeme = 16.0f;

    strcpy(etudiants[4].nom, "Robert");
    strcpy(etudiants[4].prenom, "Emma");
    strcpy(etudiants[4].adresse, "3 place du Marche, Lyon");
    etudiants[4].note_programmation = 16.0f;
    etudiants[4].note_systeme = 18.0f;

    for (int i = 0; i < 5; i++) {
        printf("Etudiant.e %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note en programmation : %.1f\n",
               etudiants[i].note_programmation);
        printf("Note en systeme d'exploitation : %.1f\n\n",
               etudiants[i].note_systeme);
    }

    return 0;
}