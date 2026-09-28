#include "hash.h"

#include <cstddef>
#include <iostream>

hashin::hashin() {
  for (int i = 0; i < tableSize; ++i) {
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

void hashin::AddItem(const std::string &name, const std::string &drink) {
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
  for (int i = 0; i < tableSize; ++i) {
    std::cout << "----------------------------\n";
    std::cout << "index = " << i << '\n';
    std::cout << HashTable[i]->name << '\n';
    std::cout << HashTable[i]->drink << '\n';
    std::cout << "# of items = " << NumofItemsInIndex(i) << '\n';
  }
}

void hashin::PrintItemsInIndex(int index) const {
  if (index < 0 || index >= tableSize) {
    std::cout << "invalid index\n";
    return;
  }

  item *ptr = HashTable[index];
  if (ptr->name == "empty") {
    std::cout << "index = " << index << " is empty\n";
    return;
  }

  while (ptr != nullptr) {
    std::cout << ptr->name << ": " << ptr->drink << '\n';
    ptr = ptr->next;
  }
}

void hashin::FindDrink(const std::string &name) const {
  int index = Hash(name);

  for (item *ptr = HashTable[index]; ptr != nullptr; ptr = ptr->next) {
    if (ptr->name == name) {
      std::cout << "Favorite drink = " << ptr->drink << '\n';
      return;
    }
  }

  std::cout << name << "'s info was not found in the Hash Table\n";
}

void hashin::RemoveItem(const std::string &name) {
  int index = Hash(name);
  item *head = HashTable[index];

  if (head->name == "empty") {
    std::cout << name << " was not found in the Hash Table\n";
    return;
  }

  if (head->name == name && head->next == nullptr) {
    head->name = "empty";
    head->drink = "empty";
    return;
  }

  if (head->name == name) {
    HashTable[index] = head->next;
    delete head;
    return;
  }

  item *previous = head;
  item *current = head->next;
  while (current != nullptr && current->name != name) {
    previous = current;
    current = current->next;
  }

  if (current == nullptr) {
    std::cout << name << " was not found in the Hash Table\n";
    return;
  }

  previous->next = current->next;
  delete current;
}

int hashin::Hash(const std::string &key) const {
  std::size_t hash = 0;
  for (unsigned char znak : key) {
    hash = (hash + znak) * 17u;
  }
  return static_cast<int>(hash % tableSize);
}
