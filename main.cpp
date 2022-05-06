#include "allocator.h"
#include "vector.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


int main()
{
    auto start = clock();
    TinyStl::vector<int> vec(1,0);
    for(int i = 0; i < 1000000; ++i) {
        vec.push_back(0);
    }
    cout << "My vector time: " << clock() - start << " ms"<<endl;
    cout << "capacity: " << vec.capacity() <<endl;
    return 0;
}