#include <iostream>
#include <stdlib.h>

using namespace std;

class A {
  int a;

public:
  A() { a = 10; }
  void wypisz() { cout << "wartość a: " << a << endl; }
  void set_a(int x) { a = x; }
};

void wypelnij_tab(int *a, int n) {
  for (int i = 0; i < n; i++)
    cin >> a[i];
}

void wypisz_tab(int *a, int n) {
  for (int i = 0; i < n; i++)
    cout << a[i] << ", ";
  cout << endl;
}

void wypelnij_tab_A(A *a, int n) {
  int x;
  for (int i = 0; i < n; i++) {
    cin >> x;
    a[i].set_a(x);
  }
}

void wypisz_tab_A(A *a, int n) {
  for (int i = 0; i < n; i++)
    a[i].wypisz();
  cout << endl;
}

int main() {

  int *p1 = (int *)malloc(3 * sizeof(int));
  wypelnij_tab(p1, 3);

  cout << "Tablica int z mallociem, stała wielkość" << endl;
  wypisz_tab(p1, 3);

  free(p1);

  int tab1[3] = {6, 7, 9};

  cout << "Tablica int standardowa, stała wielkość" << endl;
  wypisz_tab(tab1, 3);

  cout << "Podaj ilość elementów tablicy: " << endl;
  int n;
  cin >> n;

  p1 = (int *)malloc(n * sizeof(int));
  wypelnij_tab(p1, n);

  cout << "Tablica int z mallociem, zmienna wielkość" << endl;
  wypisz_tab(p1, n);

  free(p1);

  p1 = new int(10);

  cout << "wartość wskazywana przez p1: " << *p1 << endl;

  *p1 = 15;

  cout << "wartość wskazywana przez p1: " << *p1 << endl;

  delete p1;

  p1 = new int[n];
  wypelnij_tab(p1, n);

  cout << "Tablica int z new, zmienna wielkość" << endl;
  wypisz_tab(p1, n);

  delete[] p1;

  A *p2 = (A *)malloc(n * sizeof(A));
  wypisz_tab_A(p2, n);
  wypelnij_tab_A(p2, n);

  cout << "Tablica obiektów A z mallociem, zmienna wielkość" << endl;
  wypisz_tab_A(p2, n);
  free(p2);

  p2 = new A[n];

  cout << "Tablica obiektów A z new, zmienna wielkość" << endl;
  wypisz_tab_A(p2, n);
  delete[] p2;

  return 0;
}
