
## Liczby losowe

```c++
#include <random>

int losowa_z_przedzialu(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(start, end);
  return dist(gen);
}

bool orzel_lub_reszka() { return (losowa_z_przedzialu(-10001, 10000)); }
```