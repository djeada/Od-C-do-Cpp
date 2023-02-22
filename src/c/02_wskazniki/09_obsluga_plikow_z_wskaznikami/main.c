#include <stdio.h>
#include <stdlib.h>

// Funkcja zapisująca tekst do pliku
void zapiszDoPliku(char *nazwa_pliku, char *tekst) {
  FILE *plik = fopen(nazwa_pliku, "w"); // otwarcie pliku do zapisu

  if (plik == NULL) { // sprawdzenie czy otwarcie pliku się powiodło
    printf("Blad otwarcia pliku!");
    return;
  }

  fprintf(plik, "%s", tekst); // zapis tekstu do pliku
  fclose(plik);               // zamknięcie pliku
}

// Funkcja odczytująca tekst z pliku
void wyswietlPlik(char *nazwa_pliku) {
  FILE *plik = fopen(nazwa_pliku, "r"); // otwarcie pliku do odczytu

  if (plik == NULL) { // sprawdzenie czy otwarcie pliku się powiodło
    printf("Blad otwarcia pliku!");
    return;
  }

  char ch;
  while ((ch = fgetc(plik)) != EOF) { // odczyt znak po znaku do końca pliku
    printf("%c", ch);
  }

  fclose(plik); // zamknięcie pliku
}

int main() {
  char *tekst = "To jest tekst, ktory zapiszemy do pliku.\nMoze byc w nim "
                "kilka linijek.\n";

  zapiszDoPliku("plik.txt", tekst); // zapis tekstu do pliku

  wyswietlPlik("plik.txt"); // wyświetlenie zawartości pliku

  return 0;
}
