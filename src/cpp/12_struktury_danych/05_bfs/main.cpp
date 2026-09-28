#include <iostream>
#include <queue>
#include <vector>

void bfs(const std::vector<std::vector<int>> &graf, int start) {
  std::vector<bool> odwiedzone(graf.size(), false);
  std::queue<int> kolejka;

  odwiedzone[static_cast<std::size_t>(start)] = true;
  kolejka.push(start);

  while (!kolejka.empty()) {
    int wierzcholek = kolejka.front();
    kolejka.pop();

    std::cout << wierzcholek << ' ';

    for (int sasiad : graf[static_cast<std::size_t>(wierzcholek)]) {
      if (!odwiedzone[static_cast<std::size_t>(sasiad)]) {
        odwiedzone[static_cast<std::size_t>(sasiad)] = true;
        kolejka.push(sasiad);
      }
    }
  }
}

int main() {
  const std::vector<std::vector<int>> graf = {
      {1, 2}, {0, 3, 4}, {0, 4}, {1, 5}, {1, 2, 5}, {3, 4}};

  std::cout << "BFS od 0: ";
  bfs(graf, 0);
  std::cout << '\n';
  return 0;
}
