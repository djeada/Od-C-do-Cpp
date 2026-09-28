#include <stdbool.h>
#include <stdio.h>

#define V 6

static void bfs(const int graf[V][V], int start) {
  bool odwiedzone[V] = {false};
  int kolejka[V];
  size_t poczatek = 0;
  size_t koniec = 0;

  odwiedzone[start] = true;
  kolejka[koniec++] = start;

  while (poczatek < koniec) {
    int wierzcholek = kolejka[poczatek++];
    printf("%d ", wierzcholek);

    for (int sasiad = 0; sasiad < V; ++sasiad) {
      if (graf[wierzcholek][sasiad] != 0 && !odwiedzone[sasiad]) {
        odwiedzone[sasiad] = true;
        kolejka[koniec++] = sasiad;
      }
    }
  }
}

int main(void) {
  const int graf[V][V] = {
      {0, 1, 1, 0, 0, 0},
      {1, 0, 0, 1, 1, 0},
      {1, 0, 0, 0, 1, 0},
      {0, 1, 0, 0, 0, 1},
      {0, 1, 1, 0, 0, 1},
      {0, 0, 0, 1, 1, 0},
  };

  printf("BFS od 0: ");
  bfs(graf, 0);
  printf("\n");
  return 0;
}
