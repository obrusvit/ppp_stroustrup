#include "Allocator.hpp"
#include <memory>
// hint: lookup "placement new" and "explicit call of a destructor"


template<typename T>
T* My_allocator<T>::allocate(int n){ 
    // allocate space for n objects of type T
    T* ret = malloc(n* sizeof(T));
    return ret;
}

template<typename T>
void My_allocator<T>::deallocate(T* p, int n){
    // deallocate n objects of type T starting at p
    
}

template<typename T>
void My_allocator<T>::construct(T* p, const T& v){
    // construct a T with value v at p
    new(&p)T{v}; //placement new
}

template<typename T>
void My_allocator<T>::destroy(T* p){
    // destroy object T in p
    p->~T();
    free(p);
}
