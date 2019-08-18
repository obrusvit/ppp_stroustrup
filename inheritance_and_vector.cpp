#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class A{
    public:
    A(int i) : val{i} { }

    virtual void foo(){
        cout << "foo from A\n";
    }

    protected:
    int val;
};

class B : public A {
    public:
    B(int i, double d) : A{i}, val2{d} { }

    void foo() override{
        cout << "foo from B\n";
    }

    protected:
    double val2;
};

void bar_func(vector<A*>& v){
    for(auto& el : v){
        el->foo();
    }
}

int main(){
    try {
        A a1(1);
        B b1(4, 4.2);
        B b2(4, 4.3);

        vector<A*> vec;
        vec.push_back(&a1);
        vec.push_back(&b1);
        vec.push_back(&b2);

        vector<B*> vec2;
        vec2.push_back(&b1);
        vec2.push_back(&b2);

        for(auto& el : vec){
            el->foo();
        }

        bar_func(vec);
        //bar_func(vec2); // error, see PPP 19.3.4.


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
