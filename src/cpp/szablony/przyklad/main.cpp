#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T> T add(T x, T y) { return x + y; }

template <class T> class Calc {
private:
  T x, y;

public:
  Calc(T a, T b) {
    x = a;
    y = b;
  }

  string display() {
    return "Numbers are: " + to_string(x) + " " + to_string(y);
  }

  T addition() { return add(x, y); }
};

int main() {
  std::string napis1 = "klej";
  std::string napis2 = "hej";

  cout << add(3, 5) << endl;
  cout << add(3.4, 5.2) << endl;
  cout << add(napis1, napis2) << endl;

  Calc<int> o1(5, 6);
  Calc<float> o2(4.6, 2.3);

  cout << o1.display() << endl;
  cout << o2.display() << endl;

  cout << o1.addition() << endl;

  return 0;
}
