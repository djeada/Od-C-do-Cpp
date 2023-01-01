#include <bitset>
#include <iostream>

using namespace std;

int main() {
  int a = 8; // 00001000
  int n = 3; // 00000011

  cout << bitset<8>(a &= ~(1 << n)) << endl; // 00000000

  return 0;
}
