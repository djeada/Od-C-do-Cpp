#include <stdio.h>
#include <stdlib.h>

typedef struct wezel {
  int dane;
  struct wezel *strzalka_na_nastepny;
} wezel;

/*
1. Dodawanie elementów do listy.
2. Wyświetlanie aktualnej listy.
*/

// tworzymy nowy wezel i wypelniamy danymi od uzytkownika
void dodaj_nowe_pudelko(wezel **lista);

// stworzony wezel laczymy z reszta listy
void polacz_z_reszta_listy(wezel **lista, wezel *nowe_pudelko);

// wyswietl aktualny stan listy
void wyswietl_liste(wezel *lista);

// rezerwowalismy pamiec mallociem wiec musimy ja uwolnic
void uwolnij_pamiec(wezel **lista);

int main() {

  wezel *moja_lista = NULL;

  for (int i = 0; i < 3; i++)
    dodaj_nowe_pudelko(&moja_lista);

  wyswietl_liste(moja_lista);
  wyswietl_liste(moja_lista);
  uwolnij_pamiec(&moja_lista);
  wyswietl_liste(moja_lista);

  return 0;
}

void dodaj_nowe_pudelko(wezel **lista) {
  printf("Podaj liczbe: \n");
  int dana;
  scanf("%d", &dana);
  wezel *nowe_pudelko = (wezel *)malloc(sizeof(wezel));
  nowe_pudelko->dane = dana;
  nowe_pudelko->strzalka_na_nastepny = NULL;
  polacz_z_reszta_listy(lista, nowe_pudelko);
}

void polacz_z_reszta_listy(wezel **lista, wezel *nowe_pudelko) {

  // lista jest pusta, więc nowe pudełko jest całą listą
  if (*lista == NULL) {
    *lista = nowe_pudelko;
  }

  // coś w liście już jest, przechodzimy na sam koniec i dostawiamy nowe pudełko
  else {

    for (wezel *licznik = *lista; licznik != NULL;
         licznik = licznik->strzalka_na_nastepny) {
      if (licznik->strzalka_na_nastepny == NULL) {
        licznik->strzalka_na_nastepny = nowe_pudelko;
        break;
      }
    }
  }
}

void wyswietl_liste(wezel *lista) {
  printf("Twoja lista \n");
  for (wezel *licznik = lista; licznik != NULL;
       licznik = licznik->strzalka_na_nastepny) {
    printf("%d \n", licznik->dane);
  }
}

void uwolnij_pamiec(wezel **lista) {
  for (wezel *licznik = *lista; licznik != NULL;
       licznik = licznik->strzalka_na_nastepny) {
    free(licznik);
  }
}
