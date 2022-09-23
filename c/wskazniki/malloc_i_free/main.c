#include <stdio.h>
#include <stdlib.h>

#define rozmiar 10

int main() {

    int* tab = malloc(rozmiar * sizeof(int));

    for (int i =0; i < rozmiar; i++)
      tab[i] = i;
  
    int* dodatkowyWskaznik = tab;
     // free(tab); // zle mamy jeszcze inne odniesienie do wsk
  
    for (int i=0; i < rozmiar; i++) {
      printf("%d \n", *dodatkowyWskaznik);
      dodatkowyWskaznik++;
      }

        free(tab);
    //free(dodatkowyWskaznik); // zle juz zwolnilismy ta pamiec
  
    return 0;
}
  
