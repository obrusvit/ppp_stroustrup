#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct X {
    int val;
    void out(const string& s, int nv){
        cerr << this << "->" << s << ": " << val << "(" << nv << ")\n";
    }

    /* default constructor */
    X()
        : val{0}
    {
        out("X()", 0);
    }

    /* constructor */
    X(int v)
        : val{v}
    {
        out("X(int)", v);
    }

    /* copy constructor */
    X(const X& x)
    {
        val = x.val;
        out("X(X&)", x.val);
    }

    /* copy assignment */
    X& operator=(const X& x)
    {
        out("X::operator=()", x.val);
        val = x.val;
        return *this;
    }

    /* destructor */
    ~X()
    {
        out("~X()", 0);
    }

};

//------------------------------------------------------------------------------

X glob(2);
X copy(X a){
    return a;
}
X copy2(X a){
    X aa = a;
    return aa;
}
X& ref_to(X& a){
    return a;
}
X* make(int i){
    X a(i);
    return new X(a);
}
struct XX{
    X a;
    X b;
};

class A{
    public:
    int a;
    void out(const string& s){cout << "hey " << s << "\n";}
    A()
        :a{4}
    {
    }

};

//------------------------------------------------------------------------------

int main(){
    try {
        X loc{4};
        X loc2 {loc};
        loc = X{5};
        cout << "first copy\n";
        loc2 = copy(loc);
        cout << "first copy end\n\n";
        cout << "second copy\n";
        loc2 = copy2(loc);
        cout << "second copy end\n\n";
        X loc3{6};
        X& r = ref_to(loc); //nothing is called from this (y)

        cout << "delete make(7)\n";
        delete make(7);
        cout << "delete make(7) end\n\n";
        //delete make(8);

        vector<X> v(4);
        //
        XX loc4;
        X* p = new X{9};
        delete p;

        //X* pp = new X[5];
        X* pp = new X[1];
        delete[] pp;

        A* a = new A;
        delete a;

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
