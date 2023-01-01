#include <iostream>

using namespace std;

int main() {
  int a = 14; // 00001110
  int n = 2;  // 00000010

  cout << (a >> n & 1) << endl; // 1

  return 0;
}
