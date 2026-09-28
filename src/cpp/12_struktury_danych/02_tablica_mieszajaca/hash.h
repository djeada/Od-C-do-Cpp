#ifndef HASH_H
#define HASH_H

#include <string>

class hashin {
private:
  static const int tableSize = 40;

  struct item {
    std::string name;
    std::string drink;
    item *next;
  };

  item *HashTable[tableSize];

public:
  hashin();
  ~hashin();

  hashin(const hashin &) = delete;
  hashin &operator=(const hashin &) = delete;

  int Hash(const std::string &key) const;
  void AddItem(const std::string &name, const std::string &drink);
  int NumofItemsInIndex(int index) const;
  void PrintTable() const;
  void PrintItemsInIndex(int index) const;
  void FindDrink(const std::string &name) const;
  void RemoveItem(const std::string &name);
};

#endif
