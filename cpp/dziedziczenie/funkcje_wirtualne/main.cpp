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

/*

class Base
{
public:
    virtual void print() const = 0;
    virtual void printthat() const = 0;
    virtual void printit() const = 0;
};

class inhert : public Base
{
public:
    // only virtual keyword for overriding.
    virtual void print() const {}

    // only override keyword for overriding.
    void printthat() const override {}

    // using both virtual and override keywords for overriding.
    virtual void printit() const override {}
};

When you override a function you don't technically need to write either virtual
or override.

The original base class declaration needs the keyword virtual to mark it as
virtual.

In the derived class the function is virtual by way of having the ¹same type as
the base class function.

However, an override can help avoid bugs by producing a compilation error when
the intended override isn't technically an override. For instance, the function
type isn't exactly like the base class function. Or that a maintenance of the
base class changes that function's type, e.g. adding a defaulted argument.

If some member function vf is declared as virtual in a class Base, and some
class Derived, which is derived, directly or indirectly, from Base, has a
declaration for member function with the same name parameter type list (but not
the return type) cv-qualifiers ref-qualifiers Then this function in the class
Derived is also virtual
*/
