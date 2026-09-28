#ifndef STOS_H
#define STOS_H

#include <iosfwd>

class Stos {
private:
  int *tablica;
  int rozmiar;
  int indeksGorny;

public:
  Stos();
  explicit Stos(int r);
  Stos(const Stos &innyStos);
  Stos &operator=(const Stos &innyStos);
  ~Stos();

  bool odlozNaStos(int dana);
  int sciagnijZeStosu();
  bool czyPusty() const;
  bool czyPelny() const;

  friend void operator++(Stos &nasz_stos);
  friend void operator--(Stos &nasz_stos);
  friend std::ostream &operator<<(std::ostream &out, const Stos &nasz_stos);
};

#endif
