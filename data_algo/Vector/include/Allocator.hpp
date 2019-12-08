#ifndef GUARD_MY_ALLOCATOR
#define GUARD_MY_ALLOCATOR

template<typename T>
class My_allocator {
    public:
        T* allocate(int n); // allocate space for n objects of type T
        void deallocate(T* p, int n); // deallocate n objects of type T starting at p
        void construct(T* p, const T& v); // construct a T with value v at p
        void destroy(T* p); // destroy object T in p
};

#endif
