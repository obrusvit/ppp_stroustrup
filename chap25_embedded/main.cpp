#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;


int main(){
    try {
        int a = 4;
        int b = 5;
        cout << "address a: " << &a << "\n";
        cout << "address b: " << &b << "\n";
        cout << reinterpret_cast<long>(&b) - reinterpret_cast<long>(&a) << "\n";

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

