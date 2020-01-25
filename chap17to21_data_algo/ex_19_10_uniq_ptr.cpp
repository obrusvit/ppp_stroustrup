#include <iostream>
#include <stdexcept>
#include <string>
#include <stdexcept>
#include "ex_19_10_uniq_ptr.hpp"

using namespace std;

struct my_simple_struct {
    int i;
    double d;
    string s;
    double* pd;

};

my_simple_struct* make_my_simple_struct(int i, double d, string s){
    my_simple_struct* ret = new my_simple_struct();
    ret->i = i;
    ret->d = d;
    ret->s = s;
    ret->pd = &ret->d;
    return ret;
}

void test_with_exception(){
    //int* pi_local = new int(4); //memory leak after throw
    my_unique_ptr<int> up_local(new int(1));
    throw runtime_error("error");
}

int main(){
    try {
        double* pd1 = new double(4.2);
        my_unique_ptr<double> up1(new double(4.1));

        cout << "up1 holds: " << *up1 << "\n";
        *up1 = 5.1;
        cout << "up1 holds: " << *up1 << "\n";
        double* up1_released = up1.release(); //after this, you need to delete manually

        delete pd1;
        delete up1_released;

        // test with some custom struct
        my_simple_struct* ps1 = make_my_simple_struct(1, 1.1, "Hi");
        my_unique_ptr<my_simple_struct> up2(make_my_simple_struct(2, 1.2, "Hello"));
        delete ps1;

        // test that unique_ptr releases even after exception
        test_with_exception();

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
