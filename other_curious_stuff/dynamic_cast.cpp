#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class A{
    public:
    A(int i) : val{i} { }
    virtual ~A(){};

    virtual void foo(){
        cout << "foo from A\n";
    }

    protected:
    int val;
};

class B : public A {
    public:
    B(int i, double d) : A{i}, val2{d} { }
    virtual ~B(){};

    void foo() override{
        cout << "foo from B\n";
    }

    void bar() {
        cout << "bar from B\n";
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

        B b1(1, 3.1);
        b1.bar();
        b1.foo();

        A* pa1 = new A(2);
        pa1->foo();

        B* ba1 = new B(2, 4.2);
        ba1->foo();
        ba1->bar();


        A* pb1 = dynamic_cast<A*>(ba1);
        pb1->foo();

        delete pa1;
        delete ba1;
        //delete pb1; //ERROR 
        
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
