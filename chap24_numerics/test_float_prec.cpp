#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
using namespace std;

float test_float(int parts){
    float a = 1.0/parts;
    float sum = 0.0;
    for(int i = 0; i < parts; ++i){
        sum += a; 
    }
    return sum;
}


int main(){
    try {
        cout << setprecision(15) << test_float(333) << "\n";
        cout << setprecision(15) << test_float(10) << "\n";
        cout << setprecision(15) << test_float(2) << "\n";

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
