/*
 * Vector of double only.
 * Should resemble std::vector<double> AMAP.
 * As defined in PPP Chapter 19.
 */
#ifndef GUARD_VECTOR_DOUBLE_HPP
#define GUARD_VECTOR_DOUBLE_HPP

#include <initializer_list>
#include <algorithm>
#include <iostream>

class Vector_double{
    public:
        /* constructors */
        Vector_double() 
            : elem{nullptr}, _size{0}, _space{0}
        {
        }

        explicit Vector_double(int sz)
            : elem{new double[sz]}, _size{sz}, _space{sz} 
        {
            for(int i = 0; i < sz; ++i){
                elem[i] = 0;
            }
        }

        Vector_double(std::initializer_list<double> init_list)
            : elem{new double[init_list.size()]}, _size{static_cast<int>(init_list.size())}, _space{_size}
        {
            std::copy(init_list.begin(), init_list.end(), elem);
        }

        /* destructor */
        ~Vector_double(){
            delete[] elem;
        }

        /* copy constructor */
        Vector_double(const Vector_double& vec)
            : elem{new double[vec._size]}, _size{vec._size}, _space{_size}
        {
            std::copy(vec.elem, vec.elem + vec._size, elem);
        }

        /* copy assignment */
        Vector_double& operator=(const Vector_double& other){
            if(this == &other) return *this;
            if(other._size <= _space){//no need to allocate memory
                std::copy(other.elem, other.elem + other._size, elem);
                _size = other._size;
                return *this;
            }
            double* to_be_elem = new double[other._size];
            std::copy(other.elem, other.elem + other._size, to_be_elem);
            delete[] elem;
            elem = to_be_elem;
            _size = other._size;
            _space = _size;
            return *this;
        }

        /* move constructor */
        Vector_double(Vector_double&& vec) //&& rvalue reference
            : elem{vec.elem}, _size{vec._size}, _space{vec._space}
        { 
            vec.elem = nullptr;
            vec._size = 0;
            vec._space = 0;
        }

        /* move assignment */
        Vector_double& operator=(Vector_double&& vec)
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

        double& operator[](int idx){
            return elem[idx];
        }
        const double& operator[](int idx) const {
            return elem[idx]; 
        }
        double& at(int idx){
            if(idx < 0 || idx >= _size){
               throw std::out_of_range("bad index"); 
            }
            return operator[](idx);
        }
        const double& at(int idx) const {
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
            double* new_elem = new double[new_alloc];
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
        void push_back(double d){
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
        double* elem;
        int _size;
        int _space;
};

#endif
