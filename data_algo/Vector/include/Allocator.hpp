#ifndef GUARD_MY_ALLOCATOR
#define GUARD_MY_ALLOCATOR

#include <memory>

template<typename T>
class My_allocator {
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;


        T* allocate(int n); // allocate space for n objects of type T
        void deallocate(T* p, int); // deallocate n objects of type T starting at p
        void construct(T* p, const T& v); // construct a T with value v at p
        void destroy(T* p); // destroy object T in p
};

template<typename T>
T* My_allocator<T>::allocate(int n){ 
    // allocate space for n objects of type T
    T* ret = static_cast<T*>(malloc(n* sizeof(T)));
    if(ret == 0) 
        throw std::bad_alloc();
    return ret;
}

template<typename T>
void My_allocator<T>::deallocate(T* p, int){
    // deallocate n objects of type T starting at p
    //::operator delete(p);
    if(p) free(p);
    
}

template<typename T>
void My_allocator<T>::construct(T* p, const T& v){
    // construct a T with value v at p
    //new(&p)T{v}; //placement new
    new(p)T{v}; //placement new
}

template<typename T>
void My_allocator<T>::destroy(T* p){
    // destroy object T in p
    p->~T();
}
#endif
