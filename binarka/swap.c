#include <stdio.h>

void swap(int *a, int *b)
{
	// podmiana przy pomocy operatora xor
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int main() {   
	int liczbaA;
	int liczbaB;

	printf("Podaj dwie liczby: ");
	scanf("%d %d", &liczbaA, &liczbaB);

	printf("Przed zamiana: %d %d\n", liczbaA, liczbaB);
	swap(&liczbaA, &liczbaB);
	printf("Po zamianie: %d %d\n", liczbaA, liczbaB);

	return 0;
}



