#ifndef GUARD_MY_COUNTED_PTR
#define GUARD_MY_COUNTED_PTR
#include <iostream>

template<typename T>
class my_counted_ptr {
    public:
        //constructor
        explicit my_counted_ptr(const T& data)
            : ptr_{new T(data)}, use_count{new int(1)}
        {
            std::cout << "my_counted_ptr constructed\n";
        }

        my_counted_ptr(const my_counted_ptr& other)
            : ptr_{other.ptr_}, use_count{other.use_count}
        {
            ++(*use_count);
            std::cout << "my_counted_ptr copy constructed\n";
        }

        my_counted_ptr& operator=(const my_counted_ptr& other){
            if(&other == this){
                return *this;
            }
            --(*use_count);
            if(*use_count == 0){
                delete ptr_;
                delete use_count;
            }
            this->ptr_ = other.ptr_;
            this->use_count = other.use_count;
            ++(*use_count);
            return *this;
        }


        //destructor
        ~my_counted_ptr()
        {
            --(*use_count);
            if(*use_count == 0){
                delete ptr_;
                delete use_count;
                std::cout << "my_counted_ptr ptr_ and use_count deleted\n";
            }
            std::cout << "my_counted_ptr destructor called\n";
        }


        T* operator->() const{
            return ptr_;
        }

        T& operator*() const{
            return *ptr_;
        }

        explicit operator bool(){
            return ptr_;
        }

        int count(){
            return *use_count;
        }

    private:
        T* ptr_;
        int* use_count;

};
#endif
