#include <iostream>

using namespace std;

int main() {
  int a = 8; // 00001000
  int b = 7; // 00000111

  cout << (a && !(a & (a - 1))) << endl; // 1
  cout << (b && !(b & (b - 1))) << endl; // 0

  return 0;
}
