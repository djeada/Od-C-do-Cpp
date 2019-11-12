#include <bitset>
#include <iostream>

using namespace std;

int main() {
  int a = 14;

  cout << bitset<8>(a) << endl; // 00001110

  a = -1; // zamienia wszystkie bity na 1

  cout << bitset<8>(a) << endl; // 11111111

  a = 14;

  // inny sposob
  cout << bitset<8>(a).set() << endl; // 11111111

  return 0;
}
