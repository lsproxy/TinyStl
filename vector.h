
#include "allocator.h"
#include <iostream>
using namespace std;

namespace TinyStl {

using namespace TinyStl;

    template<typename T,typename Alloc = allocator<T>>
    class vector {
        public:
            using value_type = T;
            using pointer = T*;
            using iterator = T*;
            using reference = T&;
            using size_type = size_t;
            using difference_type = ptrdiff_t;
            using alloc = Alloc;

        protected:
            iterator start;
            iterator finish;
            iterator end_of_storage;
        
            void reallocate();
            void deallocate() {
                if(start) {
                    alloc::destroy(start,finish);
                    alloc::dealloc(start, end_of_storage - start);
                }
                start = finish = end_of_storage = nullptr;
            }

            iterator allocate_fill(size_t n, const T&x) {
                iterator result = alloc::alloc(n);
                for(size_t i = 0; i < n; ++i)
                {
                    alloc::construct(result + i, x);
                }
                return result;
            }

            void fill_initalize(size_type n, const T& value) {
                start = allocate_fill(n,value);
                finish = start + n;
                end_of_storage = finish;
            }
        public:
            iterator begin() {return start;}
            iterator end() {return finish;}
            size_type size() const { return size_type(end() - begin());}
            size_type capacity() const { return size_type(end_of_storage - start);}
            bool empty() const { return begin() == end();}
            reference operator[](size_type n) { return *(begin() + n);}

            //构造、析构
            vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
            vector(size_type n, const T& value) { fill_initalize(n,value);}
            vector(int n, const T& value) { fill_initalize(n,value);}
            vector(long n, const T& value) { fill_initalize(n,value);}
            explicit vector(size_type n) { fill_initalize(n,T());}
            
            ~vector() {
                deallocate();
            }

            reference front() {return *begin();}
            reference back() { return *(end() - 1);}

            void push_back(const T& value) {
                if(finish == end_of_storage) {
                    //重新分配空间
                    reallocate();
                }
                alloc::construct(finish, value);
                ++finish;
                    
            }

            void pop_back() {
                --finish;
                alloc::destroy(finish);
            }
        
    };

    template<typename T, typename Alloc>
    void vector<T, Alloc>::reallocate() {
        if(start == nullptr)
        {
            start = alloc::alloc(1);
            finish = end_of_storage = start;
        }
        else {
            size_t n = capacity() * 2;
            size_t f = finish - start;
            start = alloc::realloc(start,n);
            finish = start + f;

            end_of_storage = start + n;
        }
        
}

} 


