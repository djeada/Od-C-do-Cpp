#include <iostream>

using namespace std;

/*
When derived class overrides the base class method by redefining the same
function, then if client wants to access redefined the method from derived class
through a pointer from base class object, then you must define this function in
base class as virtual function.
*/

class parent {
public:
  void Show() { cout << "i'm parent" << endl; }
  virtual void v_Show() { cout << "i'm parent" << endl; }
};

class child : public parent {
public:
  void Show() { cout << "i'm child" << endl; }
  void v_Show() { cout << "i'm child" << endl; }
};

int main(int argc, char *argv[]) {
  parent *parent_object_ptr = new child;
  parent_object_ptr->Show();
  parent_object_ptr->v_Show();
  return 0;
}
