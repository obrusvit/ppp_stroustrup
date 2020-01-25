#ifndef GUARD_MY_UNIQUE_PTR
#define GUARD_MY_UNIQUE_PTR
#include <iostream>

template<typename T>
class my_unique_ptr {
    public:
        //constructor
        explicit my_unique_ptr(T* ptr)
            : ptr_{ptr}
        {
            std::cout << "my_unique_ptr constructed\n";
        }

        //destructor
        ~my_unique_ptr()
        {
            delete ptr_;
            std::cout << "my_unique_ptr destructed\n";
        }

        // delete generated copy constructor
        my_unique_ptr(const my_unique_ptr& other) = delete;
        // delete generated assignment
        my_unique_ptr& operator=(const my_unique_ptr& other) = delete;

        T* operator->() const{
            return ptr_;
        }

        T& operator*() const{
            return *ptr_;
        }

        explicit operator bool(){
            return ptr_;
        }

        T* release(){
            T* result = nullptr;
            std::swap(ptr_, result);
            return result;
        }

    private:
        T* ptr_;

};
#endif
