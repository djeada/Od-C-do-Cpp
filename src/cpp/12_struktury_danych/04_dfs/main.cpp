#include <iostream>
#include <vector>

void dfs(const std::vector<std::vector<int>> &graf, int wierzcholek,
         std::vector<bool> &odwiedzone) {
  odwiedzone[static_cast<std::size_t>(wierzcholek)] = true;
  std::cout << wierzcholek << ' ';

  for (int sasiad : graf[static_cast<std::size_t>(wierzcholek)]) {
    if (!odwiedzone[static_cast<std::size_t>(sasiad)]) {
      dfs(graf, sasiad, odwiedzone);
    }
  }
}

int main() {
  const std::vector<std::vector<int>> graf = {
      {1, 2}, {0, 3, 4}, {0, 4}, {1, 5}, {1, 2, 5}, {3, 4}};

  std::vector<bool> odwiedzone(graf.size(), false);

  std::cout << "DFS od 0: ";
  dfs(graf, 0, odwiedzone);
  std::cout << '\n';
  return 0;
}
