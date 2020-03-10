#include <iostream>
#include <stdexcept>
#include <vector>
/* #include <concepts> */

using namespace std;

// concept
template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class A {
    public:
    int i;
    A() : i{42} {};
};

class B : public A {
    public:
    double d;
    B() : A(), d{1.5} {};
};

template<class Input> requires Derived<A, Input>  
void foo(Input in){
    cout << in.d << "\n";
    cout << "foo \n";
}

int main(){
    try {
        B b;
        foo(b);

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

