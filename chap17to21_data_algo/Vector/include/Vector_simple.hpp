/*
 * Vector.
 * Should resemble std::vector<T> AMAP.
 * As defined in PPP Chapter 19.
 * This version uses allocator to handle its memory.
 */
#ifndef GUARD_VECTOR_SIMPLE_HPP
#define GUARD_VECTOR_SIMPLE_HPP

#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <memory>

template <typename T, typename A = std::allocator<T> >
class Vector{
    public:
        /* constructors */
        Vector() 
            : elem{nullptr}, _size{0}, _space{0}
        {
        }

        explicit Vector(int sz, T def = T())
            : elem{alloc.allocate(sz)}, _size{sz}, _space{sz} 
        {
            for(int i = 0; i < sz; ++i){
                alloc.construct(&elem[i], def);
            }
        }

        Vector(std::initializer_list<T> init_list)
            : elem{alloc.allocate(init_list.size())}, _size{static_cast<int>(init_list.size())}, _space{_size}
        {
            std::uninitialized_copy(init_list.begin(), init_list.end(), elem);
        }

        /* destructor */
        ~Vector(){
            wipe_out_elements();
        }


        /* copy constructor */
        Vector(const Vector& vec)
            : elem{alloc.allocate(vec._size)}, _size{vec._size}, _space{_size}
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
            T* to_be_elem = alloc.allocate(other._size);
            std::copy(other.elem, other.elem + other._size, to_be_elem);
            wipe_out_elements();
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
                wipe_out_elements();
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
            std::unique_ptr<T> new_elem {alloc.allocate(new_alloc)};
            
            for(int i = 0; i<_size; ++i){
                alloc.construct(&new_elem.get()[i], elem[i]);
                
            }
            wipe_out_elements();
            elem = new_elem.release();
            _space = new_alloc;
        }

        void resize(int new_size, T def = T()){
            reserve(new_size);
            for(int i = 0; i < new_size; ++i){
                alloc.construct(&elem[i], def);
            }
            for(int i = new_size; i < _size; ++i){
                alloc.destroy(&elem[i]);
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
            alloc.construct(&elem[_size], d);
            _size++;
        }

    private:
        T* elem;
        A alloc;
        int _size;
        int _space;

        void wipe_out_elements(){
            // destory all elements and return the memory
            for(int i = 0; i<_size; ++i){
                alloc.destroy(&elem[i]);
            }
            alloc.deallocate(elem, _space);
        }
};

#endif
