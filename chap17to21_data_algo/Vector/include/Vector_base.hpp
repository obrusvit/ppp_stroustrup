/**
 * Resource handle for Vector memory.
 * Handles data of type T. Takes care of correct m_size and m_space.
 * The purpose is to make my Vector RAII proof.
 */

#ifndef GUARD_VECTOR_BASE_HPP
#define GUARD_VECTOR_BASE_HPP

#include <memory>
#include <utility>
#include<iostream>

template<typename T, typename A = std::allocator<T>>
    // requires Element<T>() && Allocator<A>()
struct Vector_base{
    using size_type = unsigned int;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    iterator m_elem;
    A m_alloc;
    size_type m_size {0};
    size_type m_space {0};


    Vector_base(const A& a, size_type n)
        : m_alloc{a}, m_elem{m_alloc.allocate(n)}, m_size{n}, m_space{n}
    {

    }

    /* destructor */
    ~Vector_base()
    {
         m_alloc.deallocate(m_elem, m_space);
    }


    /* no copy */
    Vector_base(const Vector_base&) = delete;
    Vector_base& operator=(const Vector_base&) = delete;

    /* move */
    Vector_base(Vector_base&& vb)
        : m_elem{vb.m_elem}, m_alloc{vb.m_alloc}, m_size{vb.m_size}, m_space{vb.m_space}
    {
        vb.m_elem = nullptr;
    }

    Vector_base& operator=(Vector_base&& vb){
        //std::swap(*this, vb); // this doesn't work, not sure why
        m_elem = vb.m_elem;
        m_alloc = vb.m_alloc;
        m_size = vb.m_size;
        m_space = vb.m_space;
        vb.m_elem = nullptr; // without this, vb would still point to memory
                             // and destructor would try to deallocate the memory
                             // which would result in double free
        return *this;
    }

};
#endif
