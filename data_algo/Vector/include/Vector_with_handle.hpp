/*
 * Vector.
 * Should resemble std::vector<T> AMAP.
 * As defined in PPP Chapter 19.
 * This version uses Vector_base as a resource handle to its memory.
 * Vector IS A Vector_base
 */
#ifndef GUARD_VECTOR_WITH_HANDLE_HPP
#define GUARD_VECTOR_WITH_HANDLE_HPP

#include <initializer_list>
#include <utility>
#include <iostream>
#include <memory>
#include "Vector_base.hpp"


template <typename T, typename A = std::allocator<T> >
class Vector : private Vector_base<T,A>{
    public:

        /* constructors */
        Vector(A a = A())
            : Vector_base<T,A>(a, 0)
        {
        }

        explicit 
        Vector(int sz, T def = T(), A a = A())
            : Vector_base<T,A>(a, sz)
        {
            for(int i = 0; i < sz; ++i){
                this->m_alloc.construct(&this->m_elem[i], def);
            }
        }

        Vector(std::initializer_list<T> init_list, A a = A())
            : Vector_base<T,A>(a, static_cast<int>(init_list.size()))
        {
            std::uninitialized_copy(init_list.begin(), init_list.end(), this->m_elem);
        }

        /* destructor */
        virtual ~Vector(){
            wipe_out_elements();
        }


        /* copy constructor */
        Vector(const Vector& vec)
            : Vector_base<T,A>(A(), vec.m_size)
        {
            std::copy(vec.m_elem, vec.m_elem + vec.m_size, this->m_elem);
        }

        /* copy assignment */
        Vector& operator=(const Vector& other){
            if(this == &other) return *this;
            if(other.m_size <= this->m_space){ // no need to allocate memory
                std::copy(other.m_elem, other.m_elem + other.m_size, this->m_elem);
                this->m_size = other.m_size;
                return *this;
            }
            Vector_base<T,A> b(this->m_alloc , other.m_size);
            std::copy(other.m_elem, other.m_elem + other.m_size, b.m_elem);
            wipe_out_elements();
            std::swap<Vector_base<T,A>>(*this, b); // swap representations
            return *this;
        }

        /* move constructor */
        Vector(Vector&& vec) //&& rvalue reference
            : Vector_base<T,A>{std::move(vec)}
        { 
        }

        /* move assignment */
        Vector& operator=(Vector&& vec)
        {
            wipe_out_elements();
            std::swap<Vector_base<T,A>>(*this, vec); // swap representation
            return *this;

        }

        /* access */
        int size() const{
            return this->m_size;
        }
        T& operator[](int idx){
            return this->m_elem[idx];
        }
        const T& operator[](int idx) const {
            return this->m_elem[idx]; 
        }
        T& at(int idx){
            if(idx < 0 || idx >= this->m_size){
               throw std::out_of_range("bad index"); 
            }
            return operator[](idx);
        }
        const T& at(int idx) const {
            if(idx < 0 || idx >= this->m_size){
               throw std::out_of_range("bad index"); 
            }
            return operator[](idx);
        }

        int capacity() const {
            return this->m_space;
        }

        /* memory management */
        void reserve(int newalloc){
            if(newalloc <= this->m_space) return;
            Vector_base<T,A> b{this->m_alloc, newalloc};
            b.m_size = this->m_size;
            std::uninitialized_copy(this->m_elem, this->m_elem + this->m_size, b.m_elem);
            wipe_out_elements();
            std::swap<Vector_base<T,A> >(*this, b); // swap representation
        }

        void resize(int new_size, T def = T()){
            reserve(new_size);
            for(int i = 0; i < new_size; ++i){
                this->m_alloc.construct(&this->m_elem[i], def);
            }
            for(int i = new_size; i < this->m_size; ++i){
                this->m_alloc.destroy(&this->m_elem[i]);
            }
            this->m_size = new_size;
        }
        void push_back(T d){
            if(this->m_size == 0){
                reserve(8);
            }
            if(this->m_size == this->m_space){
                reserve(this->m_space * 2);
            }
            this->m_alloc.construct(&this->m_elem[this->m_size], d);
            this->m_size++;
        }

    private:
        void wipe_out_elements(){
            for(int i = 0; i < this->m_size; ++i){
                this->m_alloc.destroy(&this->m_elem[i]);
            }
        }
};


#endif
