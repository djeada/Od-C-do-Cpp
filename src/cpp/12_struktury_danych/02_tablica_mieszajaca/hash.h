#ifndef hash_H
#define hash_H

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
  ~hashin();

  hashin(const hashin &) = delete;
  hashin &operator=(const hashin &) = delete;

  int Hash(const string &key) const;
  void AddItem(const string &name, const string &drink);
  int NumofItemsInIndex(int index) const;
  void PrintTable() const;
  void PrintItemsInIndex(int index) const;
  void FindDrink(const string &name) const;
  void RemoveItem(const string &name);
};

#endif
