#include <stdio.h>

struct Prostokat {
  int x;
  int y;
  int dlugosc;
  int szerokosc;
};

void wypiszProstokat(struct Prostokat prostokat) {
  printf("Prostokat o wspolrzednych: (%d, %d), dlugosc: %d, szerokosc: %d\n",
         prostokat.x, prostokat.y, prostokat.dlugosc, prostokat.szerokosc);
}

void utworzProstokat(struct Prostokat *prostokat, int x, int y, int dlugosc,
                     int szerokosc) {
  prostokat->x = x;
  prostokat->y = y;
  prostokat->dlugosc = dlugosc;
  prostokat->szerokosc = szerokosc;
}

int poleProstokata(struct Prostokat prostokat) {
  return prostokat.dlugosc * prostokat.szerokosc;
}

int main() {
  struct Prostokat prostokat;
  utworzProstokat(&prostokat, 10, 20, 30, 40);
  wypiszProstokat(prostokat);
  printf("Pole prostokata: %d\n", poleProstokata(prostokat));
  return 0;
}