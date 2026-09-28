#include <stdio.h>
#include <stdlib.h>

typedef struct wezel {
  int dane;
  struct wezel *strzalka_na_nastepny;
} wezel;

void dodaj_nowe_pudelko(wezel **lista);
void polacz_z_reszta_listy(wezel **lista, wezel *nowe_pudelko);
void wyswietl_liste(const wezel *lista);
void uwolnij_pamiec(wezel **lista);

int main(void) {
  wezel *moja_lista = NULL;

  for (int i = 0; i < 3; i++) {
    dodaj_nowe_pudelko(&moja_lista);
  }

  wyswietl_liste(moja_lista);
  uwolnij_pamiec(&moja_lista);
  wyswietl_liste(moja_lista);

  return EXIT_SUCCESS;
}

void dodaj_nowe_pudelko(wezel **lista) {
  printf("Podaj liczbe:\n");
  int dana;
  if (scanf("%d", &dana) != 1) {
    fprintf(stderr, "Nieprawidlowa liczba.\n");
    return;
  }

  wezel *nowe_pudelko = malloc(sizeof(*nowe_pudelko));
  if (nowe_pudelko == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    return;
  }

  nowe_pudelko->dane = dana;
  nowe_pudelko->strzalka_na_nastepny = NULL;
  polacz_z_reszta_listy(lista, nowe_pudelko);
}

void polacz_z_reszta_listy(wezel **lista, wezel *nowe_pudelko) {
  if (*lista == NULL) {
    *lista = nowe_pudelko;
    return;
  }

  wezel *licznik = *lista;
  while (licznik->strzalka_na_nastepny != NULL) {
    licznik = licznik->strzalka_na_nastepny;
  }
  licznik->strzalka_na_nastepny = nowe_pudelko;
}

void wyswietl_liste(const wezel *lista) {
  printf("Twoja lista\n");
  for (const wezel *licznik = lista; licznik != NULL;
       licznik = licznik->strzalka_na_nastepny) {
    printf("%d\n", licznik->dane);
  }
}

void uwolnij_pamiec(wezel **lista) {
  while (*lista != NULL) {
    wezel *nastepny = (*lista)->strzalka_na_nastepny;
    free(*lista);
    *lista = nastepny;
  }
}
