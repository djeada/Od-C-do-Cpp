#include <stdio.h>
#include <stdlib.h>

// Obliczanie indeksu elementu na podstawie jego współrzędnych x i y
// w dwuwymiarowej tablicy o wymiarach maxX na maxY.
int oblicz_indeks(int x, int y, int maxX) { return y * maxX + x; }

int main(void) {

  // Alokuje pamięć dla tablicy dwuwymiarowej za pomocą kolejnych malloców
  int x = 4, y = 5;

  // Dwuwymiarowa tablica za pomocą Malloc -> malloc -> malloc
  int **tablica = malloc(sizeof(*tablica) * x);
  for (int i = 0; i < x; ++i) {
    tablica[i] = malloc(sizeof(tablica[0]) * y);
  }

  // Uzupełnienie tablicy wartościami
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      tablica[i][j] = i + j;
    }
  }

  // Wyświetlenie zawartości tablicy dwuwymiarowej
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      printf("%d ", tablica[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");

  // Alokuje pamięć dla tablicy jednowymiarowej i korzystam ze wzoru na
  // indeksowanie elementów w dwuwymiarowej tablicy, aby dostać się do
  // odpowiedniego elementu. Jednowymiarowa tablica za pomocą Malloc
  int *tablica2 = malloc(sizeof(*tablica2) * x * y);

  // Uzupełnienie tablicy wartościami
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      int index = oblicz_indeks(j, i, y);
      tablica2[index] = i + j;
    }
  }

  // Wyświetlenie zawartości tablicy jednowymiarowej
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      printf("%d ", tablica2[oblicz_indeks(j, i, y)]);
    }
    printf("\n");
  }
  return 0;
}
