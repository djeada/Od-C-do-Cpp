#include <stdio.h>
#include <stdlib.h>

/*
maska: liczba z bitami ustawiony (1) i wylaczonymi (0)
uzywana aby odczytac, ustawic, wylaczyc, odwrocic bity innej liczby 
przy pomocy pojedynczej operacji bitowej

0000 0010 Maska
1001 0110 Flaga
flaga & maska
maska zaslania bity
*/

const char* decNaBin(int liczba){
    char* wynik = malloc(sizeof(char) * 8);

    for(int i = 0; i < 8; i++){
        if(liczba & (1 << i)){
        wynik[7 - i] = '1';
        }
        else{
            wynik[7 - i] = '0';
        }
    }

  return wynik;
}

int main() {
  unsigned int flaga = 17;  
  unsigned int maska = 182;
  const char* flagaNapis = decNaBin(flaga); // 0001 0001
  const char* maskaNapis = decNaBin(maska); // 1011 0110

  // 1 gdy przynajmniej jeden z odpowiadajacych bitow jest ustawiony
  const char* orNapis = decNaBin(flaga & maska); // 1011 0110
  printf("%s\n|\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, orNapis);
  free((char*)orNapis);

  // 1 gdy oba odpowiadajace bity sa ustawione
  const char* andNapis = decNaBin(flaga & maska); // 1011 0110
  printf("%s\n&\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, andNapis);
  free((char*)andNapis);

  // 1 gdy odpowiadajace bity sa rozne
  const char* xorNapis = decNaBin(flaga ^ maska); // 0001 0001
  printf("%s\n^\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, xorNapis);
  free((char*)xorNapis);

  // sprawdz czy 3 (od konca) bit jest ustawiony
  int n = 3;
  int nowaMaska = 1 << (n-1);
  const char* nowaMaskaNapis = decNaBin(nowaMaska);
  const char* statusBituNapis =  decNaBin(flaga & nowaMaska);
  printf("%s\n&\n%s\n=\n%s\n\n", flagaNapis, nowaMaskaNapis, statusBituNapis);
  free((char*)nowaMaskaNapis);
  free((char*)statusBituNapis);

  free((char*)flagaNapis);
  free((char*)maskaNapis);

  return 0;

}
