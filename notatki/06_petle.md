## Pętle

### Pętla for

Po słowie kluczowym <code>for</code> w nawiasach okrągłych mamy do dyspozycji trzy miejsca oddzielone średnikami. Na pierwszym miejscu wstawiamy kod, który ma się wykonać przed pętlą. Najczęściej będzie to inicjalizacja licznika. Na drugim miejscu wstawiamy warunek, który będzie sprawdzany w każdej iteracji pętli. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>for</code>. W przeciwnym razie pętla zostanie zakończona. Na trzecim miejscu wstawiamy kod, który ma się wykonać po każdej iteracji pętli.

```
  for (inicjalizacja; warunek; inkrementacja) {
    kod;
  }
```

### Pętla while

Pętla <code>while</code> jest podobna do pętli <code>for</code>, z tym, że nie musi mieć inicjalizacji, ani inkrementacji. Warunek jest również sprawdzany przed każdą iteracją pętli.

```
  while (warunek) {
    kod;
  }
```

### Pętla do while

Pętla <code>do while</code> jest niemalże identyczna jak pętla <code>while</code>, z tym, że kod wykonywany jest przed sprawdzeniem warunku. Z tej przyczyny ciało pętli będzie zawsze wykonane conajmniej raz, nawet jeśli warunek jest już na samym początku fałszywy.

```
  do {
    kod;
  } while (warunek);
```

### Continue

Słowo kluczowe <code>continue</code> pozwala przerwać aktualną iterację pętli i wrócić do początku pętli. Jeśli warunek pętli jest dalej spełniony, to ciało pętli zostanie ponownie wykonane.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbę: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      continue;
    std::cout << i << std::endl;
  }

  return 0;
}
```

### Break

Podobnie jak <code>continue</code>, <code>break</code> przerywa aktualną iterację pętli. Różnica polega na tym, że po wywołaniu <code>break</code> pętla zostanie całkowicie przerwana i program przejdzie do kodu znajdującego się pod pętlą.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbę: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      break;
    std::cout << i << std::endl;
  }

  return 0;
}
```
