#include <bitset>
#include <iostream>

using namespace std;

int main() {
  int a = 14; // 00001110
  int n = 2;  // 00000010

  a ^= 1 << n;

  cout << bitset<8>(a) << endl; // 00001010

  return 0;
}
