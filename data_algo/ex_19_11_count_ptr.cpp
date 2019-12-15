#include <iostream>
#include <stdexcept>
#include <string>
#include <stdexcept>
#include "ex_19_11_count_ptr.hpp"

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


int main(){
    try {
        my_counted_ptr<double> cp1(4.1);
        cout << *cp1 << "\n";
        cout << cp1.count() << "\n";

        my_counted_ptr<double> cp2(cp1);
        cout << *cp1 << "\n";
        cout << *cp2 << "\n";
        cout << cp1.count() << "\n";
        cout << cp2.count() << "\n";

        *cp1 = 4.2;
        cout << *cp1 << "\n";
        cout << *cp2 << "\n";
        cout << cp1.count() << "\n";
        cout << cp2.count() << "\n";


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
