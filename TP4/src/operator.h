#ifndef OPERATOR_H
#define OPERATOR_H

typedef enum {
	CALCUL_REUSSI,
	CALCUL_OPERATEUR_INCONNU,
	CALCUL_DIVISION_PAR_ZERO
} StatutCalcul;

int somme(int num1, int num2);
int difference(int num1, int num2);
int produit(int num1, int num2);
int quotient(int num1, int num2);
int modulo(int num1, int num2);
int et_bit_a_bit(int num1, int num2);
int ou_bit_a_bit(int num1, int num2);
int negation(int num1, int num2);

StatutCalcul calculer(int num1, int num2, char op, int *resultat);

#endif
