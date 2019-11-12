#include <bitset>
#include <iostream>

using namespace std;

int main() {
  int a = 8; // 00001000
  int n = 2; // 00000010

  cout << bitset<8>(a |= 1 << n) << endl; // 00001100

  return 0;
}
