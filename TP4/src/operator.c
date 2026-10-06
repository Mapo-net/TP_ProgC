#include "operator.h"

int somme(int num1, int num2)
{
	return num1 + num2;
}

int difference(int num1, int num2)
{
	return num1 - num2;
}

int produit(int num1, int num2)
{
	return num1 * num2;
}

int quotient(int num1, int num2)
{
	return num1 / num2;
}

int modulo(int num1, int num2)
{
	return num1 % num2;
}

int et_bit_a_bit(int num1, int num2)
{
	return num1 & num2;
}

int ou_bit_a_bit(int num1, int num2)
{
	return num1 | num2;
}

int negation(int num1, int num2)
{
	(void)num2;
	return ~num1;
}

StatutCalcul calculer(int num1, int num2, char op, int *resultat)
{
	switch (op) {
	case '+':
		*resultat = somme(num1, num2);
		break;
	case '-':
		*resultat = difference(num1, num2);
		break;
	case '*':
		*resultat = produit(num1, num2);
		break;
	case '/':
		if (num2 == 0) {
			return CALCUL_DIVISION_PAR_ZERO;
		}
		*resultat = quotient(num1, num2);
		break;
	case '%':
		if (num2 == 0) {
			return CALCUL_DIVISION_PAR_ZERO;
		}
		*resultat = modulo(num1, num2);
		break;
	case '&':
		*resultat = et_bit_a_bit(num1, num2);
		break;
	case '|':
		*resultat = ou_bit_a_bit(num1, num2);
		break;
	case '~':
		*resultat = negation(num1, num2);
		break;
	default:
		return CALCUL_OPERATEUR_INCONNU;
	}

	return CALCUL_REUSSI;
}
