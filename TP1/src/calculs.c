
#include <stdio.h>
#include <string.h>

int main() {
	int num1 = 16;
	int num2 = 3;
	char op = '/';

	switch (op) {
		case '+':
			printf("%d + %d = %d\n", num1, num2, num1 + num2);
			break;
		case '-':
			printf("%d - %d = %d\n", num1, num2, num1 - num2);
			break;
		case '*':
			printf("%d * %d = %d\n", num1, num2, num1 * num2);
			break;
		case '/':
			if (num2 == 0) {
				printf("Erreur : division par zero impossible.\n");
			} else {
				printf("%d / %d = %d\n", num1, num2, num1 / num2);
			}
			break;
		case '%':
			if (num2 == 0) {
				printf("Erreur : modulo par zero impossible.\n");
			} else {
				printf("%d %% %d = %d\n", num1, num2, num1 % num2);
			}
			break;
		case '&':
			printf("%d & %d = %d\n", num1, num2, num1 & num2);
			break;
		case '|':
			printf("%d | %d = %d\n", num1, num2, num1 | num2);
			break;
		case '~':
			printf("~%d = %d\n", num1, ~num1);
			break;
		default:
			printf("Operateur inconnu : %c\n", op);
			return 1;
	}

	return 0;
}