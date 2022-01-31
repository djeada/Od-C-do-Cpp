#include "Lista.h"
#include "Student.h"
#include <iostream>

using namespace std;

int main() {
  Student s1;
  Student s2("Jeremy", "Trabka", 136);
  Student s3("Tony", "Jablko", 234);
  Student s4("Pan", "Bambino", 9);

  Lista nasza_lista(s1);
  nasza_lista.wstaw(s4);
  nasza_lista.wstaw(s2);
  nasza_lista.wstaw(s3);
  nasza_lista.wstaw(s2);

  cout << nasza_lista;

  nasza_lista.posortuj();

  cout << "Po posortowaniu: " << endl;

  cout << nasza_lista;

  return 0;
}
