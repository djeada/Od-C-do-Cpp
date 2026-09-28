#include <stdio.h>

struct Foo {
  int liczba;
  char znak;
};

union Bar {
  int liczba;
  char znak;
};

int main(void) {
  struct Foo foo = {.liczba = 1, .znak = 'a'};
  union Bar bar;

  printf("Struktura zawiera jednocześnie: %d oraz %c\n", foo.liczba, foo.znak);

  bar.liczba = 1;
  printf("Unia - aktywne pole liczba: %d\n", bar.liczba);
  bar.znak = 'a';
  printf("Unia - aktywne pole znak: %c\n", bar.znak);

  printf("Rozmiar struktury foo: %zu\n", sizeof(foo));
  printf("Rozmiar unii bar: %zu\n", sizeof(bar));

  printf("Adresy pól struktury foo: %p %p\n", (void *)&foo.liczba,
         (void *)&foo.znak);
  printf("Adresy pól unii bar: %p %p\n", (void *)&bar.liczba,
         (void *)&bar.znak);

  return 0;
}
