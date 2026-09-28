#include "hash.h"

#include <cstddef>
#include <iostream>

using namespace std;

hashin::hashin() {
  for (int i = 0; i < tableSize; i++) {
    HashTable[i] = new item{"empty", "empty", nullptr};
  }
}

hashin::~hashin() {
  for (int i = 0; i < tableSize; ++i) {
    item *ptr = HashTable[i];
    while (ptr != nullptr) {
      item *next = ptr->next;
      delete ptr;
      ptr = next;
    }
  }
}

void hashin::AddItem(const string &name, const string &drink) {
  int index = Hash(name);

  if (HashTable[index]->name == "empty") {
    HashTable[index]->name = name;
    HashTable[index]->drink = drink;
    return;
  }

  item *ptr = HashTable[index];
  while (ptr->next != nullptr) {
    ptr = ptr->next;
  }
  ptr->next = new item{name, drink, nullptr};
}

int hashin::NumofItemsInIndex(int index) const {
  if (index < 0 || index >= tableSize || HashTable[index]->name == "empty") {
    return 0;
  }

  int count = 0;
  for (item *ptr = HashTable[index]; ptr != nullptr; ptr = ptr->next) {
    ++count;
  }
  return count;
}

void hashin::PrintTable() const {
  for (int i = 0; i < tableSize; i++) {
    cout << "----------------------------\n";
    cout << "index = " << i << endl;
    cout << HashTable[i]->name << endl;
    cout << HashTable[i]->drink << endl;
    cout << "# of items = " << NumofItemsInIndex(i) << endl;
    cout << "----------------------------\n";
  }
}

void hashin::PrintItemsInIndex(int index) const {
  if (index < 0 || index >= tableSize) {
    cout << "invalid index" << endl;
    return;
  }

  item *ptr = HashTable[index];
  if (ptr->name == "empty") {
    cout << "index = " << index << " is empty" << endl;
    return;
  }

  cout << "index = " << index << " contains the following items" << endl;
  while (ptr != nullptr) {
    cout << "-------------\n";
    cout << ptr->name << endl;
    cout << ptr->drink << endl;
    cout << "-------------\n";
    ptr = ptr->next;
  }
}

void hashin::FindDrink(const string &name) const {
  int index = Hash(name);

  for (item *ptr = HashTable[index]; ptr != nullptr; ptr = ptr->next) {
    if (ptr->name == name) {
      cout << "Favorite drink = " << ptr->drink << endl;
      return;
    }
  }

  cout << name << "'s info was not found in the Hash Table" << endl;
}

void hashin::RemoveItem(const string &name) {
  int index = Hash(name);
  item *head = HashTable[index];

  if (head->name == "empty") {
    cout << name << " was not found in the Hash Table" << endl;
    return;
  }

  if (head->name == name && head->next == nullptr) {
    head->name = "empty";
    head->drink = "empty";
    cout << name << " was removed from the Hash Table" << endl;
    return;
  }

  if (head->name == name) {
    HashTable[index] = head->next;
    delete head;
    cout << name << " was removed from the Hash Table" << endl;
    return;
  }

  item *previous = head;
  item *current = head->next;
  while (current != nullptr && current->name != name) {
    previous = current;
    current = current->next;
  }

  if (current == nullptr) {
    cout << name << " was not found in the Hash Table" << endl;
    return;
  }

  previous->next = current->next;
  delete current;
  cout << name << " was removed from the Hash Table" << endl;
}

int hashin::Hash(const string &key) const {
  std::size_t hash = 0;
  for (unsigned char znak : key) {
    hash = (hash + znak) * 17u;
  }
  return static_cast<int>(hash % tableSize);
}
