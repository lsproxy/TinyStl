#include "allocator.h"
#include <iostream>

using namespace std;

int main()
{
    int* p = TinyStl::allocator<int>::allocate();
    TinyStl::allocator<int>::construct(p,2);
    cout << *p << endl;
}