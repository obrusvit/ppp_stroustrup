#include <iostream>
#include <stdexcept>

using namespace std;

class B1 {
    public:
    virtual void pvf() =0;
    virtual void vf(){
        cout << "B1::vf\n";
    }
    void f(){
        cout << "B1::f\n";
    }
};

class D1 : public B1 {
    public:
        void pvf() override {
            cout << "D1::pvf\n";
        }
        void vf() override {
            cout << "D1::vf\n";
        }
        void f() {
            cout << "D1::f\n";
        }
};

class D2 : public D1 {
    public:
        void pvf() override {
            cout << "D2::pvf\n";
        }
};

//------------------------------------------------------------------------------

class B2 {
    public:
        virtual void pvf() =0;
};

class D21 : public B2 {
    public:
        virtual void pvf() override {
            cout << "D21::pvf, " << s << "\n";
        }

    private:
        string s {"string D21"};
};

class D22 : public B2{
    public:
        void pvf() override {
            cout << "D22::pvf, " << i << "\n";
        }
    private:
        int i {42};

};

void f(B2& b2){
    cout << "from f(B2&): ";
    b2.pvf();
}

void g(B2* b2){
    cout << "from f(B2*): ";
    b2->pvf();
}

int main(){
    try {
        //
        //B1 b1;
        //b1.vf();
        //b1.f();
        
        D1 d1;
        d1.pvf();
        d1.vf();
        d1.f();

        B1& br = d1;
        br.pvf();
        br.vf();
        br.f();

        D2 d2;
        d2.pvf();
        d2.vf();
        d2.f();

        //
        
        D21 d21;
        d21.pvf();

        D22 d22;
        d22.pvf();

        f(d21);
        f(d22);

        g(&d21);
        g(&d22);

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
