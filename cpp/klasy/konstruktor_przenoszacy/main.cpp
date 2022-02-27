/*
The difference between a copy and a move is that a copy leaves the source unchanged. A move on the other hand leaves the source in a state defined differently for each type.

Suppose you have a function that returns a substantial object:

Matrix multiply(const Matrix &a, const Matrix &b);

When you write code like this:

Matrix r = multiply(a, b);

then an ordinary C++ compiler will create a temporary object for the result of multiply(), call the copy constructor to initialise r, 
and then destruct the temporary return value. Move semantics in C++0x allow the "move constructor" 
to be called to initialise r by copying its contents, and then discard the temporary value without having to destruct it.
*/

#include <iostream>

void printInt(int &i) { std::cout << "lvalue reference: " << i << std::endl; }

void printInt2(int &&i) { std::cout << "rvalue reference: " << i << std::endl; }

#include <iostream>

class Move {
private:
    int* data;
 
public:
   
    Move(int d)
    {
        data = new int;
        *data = d;

    };
 
    // Konstruktor kopiujacy
    Move(const Move& source)
        : Move{ *source.data }
    {
    }
 
    // Konstruktor przenoszacy
    Move(Move&& source)
        : data{ source.data }
    {
        source.data = nullptr;
    }
 
    ~Move()
    {
        delete data;
    }
};
 
int main()
{
    int a = 5;   // a is a lvalue

    printInt(a);
    printInt2(a + 1);
    
    Move obiekt(1);
    Move obiekt2(obiekt);
    Move obiekt3(1+1);
}
