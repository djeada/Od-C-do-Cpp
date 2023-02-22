#include "stos.h"

int main() {

  Stos s1;

  s1.odlozNaStos(3);
  s1.odlozNaStos(54);
  s1.odlozNaStos(2);

  cout << s1 << endl;

  cout << boolalpha << s1.odlozNaStos(2) << endl;

  cout << s1 << endl;

  ++s1;
  ++s1;

  cout << boolalpha << s1.odlozNaStos(2) << endl;
  s1.odlozNaStos(10);

  cout << s1 << endl;

  cout << boolalpha << s1.czyPelny() << endl;

  Stos s2(2);

  s2.odlozNaStos(11);
  s2.odlozNaStos(7);
  cout << s2.sciagnijZeStosu() << endl;

  Stos s3(s2);

  cout << s3;

  return 0;
}
