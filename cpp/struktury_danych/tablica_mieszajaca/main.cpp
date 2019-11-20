
#include "hash.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

  hashin MyHash;

  string name, drink = "empty";

  for (int i = 0; i < 10; i++) {
    cout << "\nGive your name, and drink " << endl;
    cin >> name;
    cin >> drink;
    MyHash.AddItem(name, drink);
  }

  MyHash.PrintTable();

  system("pause");

  return 0;
}