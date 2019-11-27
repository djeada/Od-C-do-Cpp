#include <iostream>

using namespace std;

/*
Abstract classes are used to represent general concepts (for example, Shape, Animal), which can be used as base classes for concrete classes (for example, Circle, Dog).

No objects of an abstract class can be created (except for base subobjects of a class derived from it) and no non-static data members of an abstract class can be declared.
*/

struct Abstract {
    virtual void f() = 0; // pure virtual
}; // "Abstract" is abstract
 
struct Concrete : Abstract {
    void f() override {} // non-pure virtual
    virtual void g();     // non-pure virtual
}; // "Concrete" is non-abstract
 
struct Abstract2 : Concrete {
    void g() override = 0; // pure virtual overrider
}; // "Abstract2" is abstract
 
int main()
{
    // Abstract a; // Error: abstract class
    Concrete b; // OK
    Abstract& a = b; // OK to reference abstract base
    a.f(); // virtual dispatch to Concrete::f()
    // Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
}



