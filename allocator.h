#pragma once
//粗糙版的allocateor
//底层暂时采用malloc 和 free
//暂时不实现自己的内存池
#include <iostream>
using namespace std;

namespace TinyStl{

    template<typename T>
    class allocator{
    public:
        //静态方法定义
        static T* allocate();
        static T* allocate(size_t n);
        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_t n);
        
        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        
        static void destroy(T* ptr);
        static void destroy(T* first, T* last);

    };

    template<class T>
    T* allocator<T>::allocate(){
        return (T*)malloc(sizeof(T));
    }

    template<typename T>
    T* allocator<T>::allocate(size_t n){
        if (n <= 0)
        {
            return nullptr;
        }
        return (T*)malloc(sizeof(T) * n);
    }

    template<typename T>
    void allocator<T>::deallocate(T* ptr){
        if(ptr == nullptr)
            return;
        free(ptr);
    }

    template<typename T>
    void allocator<T>::deallocate(T* ptr, size_t n){
        allocator<T>::deallocate(ptr);
    }

    template<typename T>
    void allocator<T>::construct(T* ptr){
        new(ptr) T();
    }
    
    template<typename T>
    void allocator<T>::construct(T* ptr,const T& value){
        new(ptr) T(value);
    }

    template<typename T>
    void allocator<T>::destroy(T* ptr){
        ptr->~T();
    }

    template<typename T>
    void allocator<T>::destroy(T* first, T* last){
        for(;first != last; ++first)
            first->~T();
    }
}

void allocator_test(){
    int* p = TinyStl::allocator<int>::allocate();
    TinyStl::allocator<int>::construct(p,2);
    cout << *p << endl;
    TinyStl::allocator<int>::destroy(p);
}
