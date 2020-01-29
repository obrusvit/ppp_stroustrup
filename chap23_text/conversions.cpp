#include <iostream>
#include <stdexcept>
#include <vector>
#include "conversions.hpp"

using namespace std;

void test_string_to_double(){
    string s1 = "4.45";
    double d1 = from_string<double>(s1);
    cout << d1 << "\n";
}
void test_bad_string_to_double(){
    string s1 = "----sdfja4abc";
    double d1 = from_string<double>(s1);
    cout << d1 << "\n";
}

void test_double_to_string(){
    double d1 = 42.2;
    string s1 = to_string<double>(d1);
    cout << s1 << "\n";
}

int main(){
    try {

        test_string_to_double();
        test_double_to_string();

        // will throw
        test_bad_string_to_double();
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
