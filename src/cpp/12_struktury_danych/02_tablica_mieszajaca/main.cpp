#include "hash.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  hashin MyHash;
  string name;
  string drink;

  for (int i = 0; i < 10; i++) {
    cout << "\nGive your name, and drink " << endl;
    if (!(cin >> name >> drink)) {
      cerr << "Nie udalo sie odczytac danych." << endl;
      return 1;
    }
    MyHash.AddItem(name, drink);
  }

  MyHash.PrintTable();
  return 0;
}
