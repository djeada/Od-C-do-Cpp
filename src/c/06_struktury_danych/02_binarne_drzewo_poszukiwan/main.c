#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Wezel {
  int wartosc;
  struct Wezel *lewy;
  struct Wezel *prawy;
};

static struct Wezel *nowy_wezel(int wartosc) {
  struct Wezel *wezel = malloc(sizeof(*wezel));
  if (wezel == NULL) {
    return NULL;
  }

  wezel->wartosc = wartosc;
  wezel->lewy = NULL;
  wezel->prawy = NULL;
  return wezel;
}

static bool wstaw(struct Wezel **korzen, int wartosc) {
  if (*korzen == NULL) {
    *korzen = nowy_wezel(wartosc);
    return *korzen != NULL;
  }

  if (wartosc < (*korzen)->wartosc) {
    return wstaw(&(*korzen)->lewy, wartosc);
  }
  if (wartosc > (*korzen)->wartosc) {
    return wstaw(&(*korzen)->prawy, wartosc);
  }

  return true;
}

static bool zawiera(const struct Wezel *korzen, int wartosc) {
  while (korzen != NULL) {
    if (wartosc == korzen->wartosc) {
      return true;
    }
    korzen = wartosc < korzen->wartosc ? korzen->lewy : korzen->prawy;
  }
  return false;
}

static void inorder(const struct Wezel *korzen) {
  if (korzen == NULL) {
    return;
  }

  inorder(korzen->lewy);
  printf("%d ", korzen->wartosc);
  inorder(korzen->prawy);
}

static void zwolnij(struct Wezel *korzen) {
  if (korzen == NULL) {
    return;
  }

  zwolnij(korzen->lewy);
  zwolnij(korzen->prawy);
  free(korzen);
}

int main(void) {
  const int dane[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
  struct Wezel *korzen = NULL;

  for (size_t i = 0; i < sizeof(dane) / sizeof(dane[0]); ++i) {
    if (!wstaw(&korzen, dane[i])) {
      fprintf(stderr, "Blad alokacji pamieci.\n");
      zwolnij(korzen);
      return EXIT_FAILURE;
    }
  }

  printf("Inorder: ");
  inorder(korzen);
  printf("\n");

  printf("Czy zawiera 7: %s\n", zawiera(korzen, 7) ? "tak" : "nie");
  printf("Czy zawiera 12: %s\n", zawiera(korzen, 12) ? "tak" : "nie");

  zwolnij(korzen);
  return EXIT_SUCCESS;
}
