/**
 * Array_ref examples starting at 25.4.2.
 *
 * Showing several interface problems and their alternatives.
 * Instead of Shape and objects derived from Shape, I use simpler classes.
 * The definition of Base is not abstract (as in Shape, Stroustrup uses not
 * abstract version).
 */ 

#include <iostream>
#include <stdexcept>
#include <vector>

#include <memory>

using namespace std;

//------------------------------------------------------------------------------

class Base {
    public:
        virtual void foo() const {
            cout << "Base::foo, i= "<< _i << "\n";
        }
        Base() : _i{0} {}
        Base(int i) : _i{i} {}
        virtual ~Base() {};

        int _i;
};

class Derived_1 : public Base {
    public:
        Derived_1() : Base(), _d{0.0} {}
        Derived_1(int i) : Base(i), _d{0.0} {}
        Derived_1(int i, double d) : Base(i), _d{d} {}

        void foo() const override {
            cout << "Derived_1::foo, i=" << _i << ", d="<< _d << "\n";
        }
    private:
        double _d;
};

class Derived_2 : public Base {
    public:
        Derived_2() : Base(), _s{""} {}
        Derived_2(int i) : Base(i), _s{""} {}
        Derived_2(int i, string s) : Base(i), _s{s} {}

        void foo() const override {
            cout << "Derived_2::foo, i=" << _i << ", s="<< _s << "\n";
        }
    private:
        string _s;
};

class Derived_3 : public Base {
    public:
        Derived_3() : Base(){}
        Derived_3(int i) : Base(i){}

        void foo() const override {
            cout << "Derived_3::foo, i=" << _i << "\n";
        }
};

//------------------------------------------------------------------------------

void poor(Base* p, int sz){
    for(int i = 0; i < sz; ++i){
        p[i].foo();
    }
}

void use_poor(vector<Derived_1>& vec_d1){
    Derived_1 d1[10];
    Derived_2 d2[10];
    Derived_3 d3[10];
    Base* b1 = new Derived_1(1, 4.2); 
    Base b[20];
    
    /* poor(&vec_d1[0], vec_d1.size());  //seg fault, slicing of Derived_1 */
    /* poor(d1, 10); // seg fault, slicing of Derived_1 */
    /* poor(d2, 20); // seg fault, slicing of Derived_1 and wrong size */
    poor(d3, 10); // correct, lucky, Derived_3 is same size as Base, change in Derived_3 would cause error
    poor(b, 20);  // correct

    poor(b1, 1);  // correct
    delete b1;
    b1 = 0;
    /* poor(b1, 1); // seg fault */
}

//------------------------------------------------------------------------------

void general(vector<Base>& vec){
    // if it's possible, always use std::vector
    for(auto el : vec){
        el.foo();
    }
}

void general1(vector<Base*>& vec){
    for(auto el : vec){
        el->foo();
    }
}

void general2(const vector<unique_ptr<Base>>& vec){
    for (auto& el : vec){
        el->foo();
    }
}

void use_general(vector<Derived_1>& vec_d1){
    vector<Base*> d1;
    d1.push_back(new Derived_1(1,1.1));
    d1.push_back(new Derived_2(2, "Hey"));
    d1.push_back(new Derived_3(3));
    general1(d1);

    vector<unique_ptr<Base>> d2;
    d2.push_back(make_unique<Derived_1>(Derived_1(1,1.1)));
    d2.push_back(make_unique<Derived_2>(Derived_2(2, "Hey")));
    d2.push_back(make_unique<Derived_3>(Derived_3(3)));

    general2(d2);

    //how to use general()? // not possible in current setting
}

//------------------------------------------------------------------------------

template<typename T> class Array_ref {
    // non-owning array of references to objects stored in memory
    //      - does no memory management, in this it differs from std::array<T>
    // knows its size
    // knows the type of objects it points ot
    // cheap to pass (just as pointer, size pair)
    // does not implicitly convert to pointer
    // easy to express ubrange
    // easy to use 
    public:
        Array_ref(T* elem, int size) : _elem{elem}, _size{size} {}

        T& operator[](int idx) {
            return _elem[idx];
        }

        const T& operator[](int idx) const {
            return _elem[idx];
        }

        bool assign(Array_ref a){
            if(a._size != _size) return false;
            for (int i = 0; i < _size; ++i) 
                _elem[i] = a._elem[i];
            return true;
        }

        void reset(Array_ref a){
            reset(a._elem, a._size);
        }

        void reset(T* t, int sz){
           _elem = t;
           _size = sz;
        }

        int size() const { return _size; }

        // WARNING: expert territory
        // this allows us to convert Array_ref<Derived*> to immutable Array_ref<Base*>
        // in places where we do not want to modify the objects of Array_ref, but only
        // call virtual method, e.g foo()
        template<typename Q>
        operator const Array_ref<const Q>(){
            // check implicit conversion of elements:
            static_cast<Q>(*static_cast<T*>(nullptr)); //don't use that conversion, only check..
            return Array_ref<const Q>{reinterpret_cast<Q*>(_elem), _size};
        }

    private:
        T* _elem;
        int _size;

};

template<typename T> Array_ref<T> make_ref(T* pp, int sz){
    return (pp)? Array_ref<T>{pp, sz} : Array_ref<T>{nullptr, 0};
}

template<typename T> Array_ref<T> make_ref(vector<T> vec){
    return (vec.size()) ? Array_ref<T>{&vec[0], static_cast<int>(vec.size())} : Array_ref<T>{nullptr, 0};
}

template<typename T, int s> Array_ref<T> make_ref(T (&pp)[s]){
    // T (&pp)[s] declares the argument pp to be reference to an array
    // of s elements of type T, it must be known at compile time.
    return Array_ref<T>{pp, s};
}

//------------------------------------------------------------------------------

void better(Array_ref<Base> a){
    for(int i = 0; i < a.size(); ++i){
        a[i].foo();
    }
}

void better2(const Array_ref<Base * const> a){
    // to better handle polymorphism
    for(int i = 0; i < a.size(); ++i){
        if(a[i]) // we deal with pointers now
            a[i]->foo();
    }
}

void use_better(Base* p, vector<Derived_1> v){
    Derived_1 d1[10];
    Derived_2 d2[10];
    Derived_3 d3[10];
    Base* b1 = new Derived_1(1, 4.2); 
    Base b[20];
    vector<Base> v2(5);
    
    /* better(make_ref(v));  // cannot compile Array_ref<Base> required.....better than segfault, right? */
    better(make_ref(v2));
    /* better(make_ref(d1)); // cannot compile */
    /* better(make_ref(d2)); // cannot compile */
    /* better(make_ref(d3)); // cannot compile */
    better(make_ref(b1, 1)); // good
    better(make_ref(b));     // good, no need to specify size

    delete b1;
    b1 = 0;
    better(make_ref(b1,1)); // good, empty array
}

void use_better2(Base* p, vector<Derived_1*>& v){
    Derived_1* d1[2];
    Base* b[10];
    Base* b1 = new Derived_1(1, 4.2); 
    vector<Base*> v2(5);

    //initialize
    Derived_1 d11 {1};
    Derived_1 d12 {2};
    d1[0] = &d11;
    d1[1] = &d12;

    for(int i = 0; i < 10; ++i){ b[i] = nullptr; }
    
    better2(make_ref(&p, 1)); // correct, but see the ampersand
    better2(make_ref(v));  // correct
    better2(make_ref(v2)); // correct
    better2(make_ref(d1)); // correct, implicit conversion (defined in Array_ref)
    better2(make_ref(&b1, 1));  // correct, but a little bit cryptic, 
                                // why &b1 ?, because we need T**
                                // pass T*,  then we have Array_ref<T>  ..bad
                                // pass T**, then we have Array_ref<T*> ..needed for better2
    better2(make_ref(b));  // error

    delete b1;
    b1 = 0;
    better2(make_ref(&b1,1)); // correct
}


//------------------------------------------------------------------------------

int main(){
    try {
        vector<Derived_1> vec_d1 {{1,1.2}, {2, 4.3}, {3, 5.3}};
        /* use_poor(vec_d1); */
        /* use_general(vec_d1); */
        /* use_better(nullptr, vec_d1); */

        vector<Derived_1*> vec_pd1 {new Derived_1{1,1.2}, new Derived_1{2, 4.3}, new Derived_1{3, 5.3}};
        use_better2(nullptr, vec_pd1);

        for(auto& el : vec_pd1){
            delete el;
        }

        return 0;
    }
    catch(exception& e){
        cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}

