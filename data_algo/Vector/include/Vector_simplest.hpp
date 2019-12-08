/*
 * Vector of T.
 * As defined in PPP Chapter 19.
 * Not using handle or allocator, takes care of its own memory.
 * Cannot handle more complicated types.
 */
#ifndef GUARD_VECTOR_SIMPLEST_HPP
#define GUARD_VECTOR_SIMPLEST_HPP

#include <initializer_list>
#include <algorithm>
#include <iostream>

template<typename T>
class Vector{
    public:
        /* constructors */
        Vector() 
            : elem{nullptr}, _size{0}, _space{0}
        {
        }

        explicit Vector(int sz)
            : elem{new T[sz]}, _size{sz}, _space{sz} 
        {
            for(int i = 0; i < sz; ++i){
                elem[i] = 0;
            }
        }

        Vector(std::initializer_list<T> init_list)
            : elem{new T[init_list.size()]}, _size{static_cast<int>(init_list.size())}, _space{_size}
        {
            std::copy(init_list.begin(), init_list.end(), elem);
        }

        /* destructor */
        ~Vector(){
            delete[] elem;
        }

        /* copy constructor */
        Vector(const Vector& vec)
            : elem{new T[vec._size]}, _size{vec._size}, _space{_size}
        {
            std::copy(vec.elem, vec.elem + vec._size, elem);
        }

        /* copy assignment */
        Vector& operator=(const Vector& other){
            if(this == &other) return *this;
            if(other._size <= _space){//no need to allocate memory
                std::copy(other.elem, other.elem + other._size, elem);
                _size = other._size;
                return *this;
            }
            T* to_be_elem = new T[other._size];
            std::copy(other.elem, other.elem + other._size, to_be_elem);
            delete[] elem;
            elem = to_be_elem;
            _size = other._size;
            _space = _size;
            return *this;
        }

        /* move constructor */
        Vector(Vector&& vec) //&& rvalue reference
            : elem{vec.elem}, _size{vec._size}, _space{vec._space}
        { 
            vec.elem = nullptr;
            vec._size = 0;
            vec._space = 0;
        }

        /* move assignment */
        Vector& operator=(Vector&& vec)
        {
            if(this != &vec){
                delete[] elem;
                elem = vec.elem;
                _size = vec._size;
                _space = vec._space;
                vec.elem = nullptr;
                vec._size = 0;
                vec._space = 0;
            }
            return *this;
        }

        /* access */
        int size() const{
            return _size;
        }

        T& operator[](int idx){
            return elem[idx];
        }
        const T& operator[](int idx) const {
            return elem[idx]; 
        }
        T& at(int idx){
            if(idx < 0 || idx >= _size){
               throw std::out_of_range("bad index"); 
            }
            return operator[](idx);
        }
        const T& at(int idx) const {
            if(idx < 0 || idx >= _size){
               throw std::out_of_range("bad index"); 
            }
            return operator[](idx);
        }
        int capacity() const {
            return _space;
        }

        /* memory management */
        void reserve(int new_alloc){
            if(new_alloc <= _space) return;
            T* new_elem = new T[new_alloc];
            std::copy(elem, elem+_size, new_elem);
            delete[] elem;
            elem = new_elem;
            _space = new_alloc;
        }

        void resize(int new_size){
            reserve(new_size);
            for(int i = 0; i < new_size; ++i){
                elem[i] = 0.0;
            }
            _size = new_size;
        }
        void push_back(T d){
            if(_size == 0){
                reserve(8);
            }
            if(_size == _space){
                reserve(_space * 2);
            }
            elem[_size] = d;
            _size++;
        }

    private:
        T* elem;
        int _size;
        int _space;
};

#endif
