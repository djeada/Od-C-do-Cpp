#include <stdbool.h>
#include <stdio.h>

#define V 6

static void dfs_rekurencyjnie(const int graf[V][V], int wierzcholek,
                              bool odwiedzone[V]) {
  odwiedzone[wierzcholek] = true;
  printf("%d ", wierzcholek);

  for (int sasiad = 0; sasiad < V; ++sasiad) {
    if (graf[wierzcholek][sasiad] != 0 && !odwiedzone[sasiad]) {
      dfs_rekurencyjnie(graf, sasiad, odwiedzone);
    }
  }
}

static void dfs(const int graf[V][V], int start) {
  bool odwiedzone[V] = {false};
  dfs_rekurencyjnie(graf, start, odwiedzone);
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

  printf("DFS od 0: ");
  dfs(graf, 0);
  printf("\n");
  return 0;
}
