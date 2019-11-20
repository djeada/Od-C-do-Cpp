#ifndef hash_H
#define hash_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class hashin {
private:
  static const int tableSize = 40;

  struct item {
    string name;
    string drink;
    item *next;
  };

  item *HashTable[tableSize];

public:
  hashin();
  int Hash(string key);
  void AddItem(string name, string drink);
  int NumofItemsInIndex(int index);
  void PrintTable();
  void PrintItemsInIndex(int index);
  void FindDrink(string name);
  void RemoveItem(string name);
};

#endif
