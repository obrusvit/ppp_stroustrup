#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
using namespace std;

template<typename Num_type>
    // requires Real_number or something...just not int
Num_type test_num_type_precistion(int parts){
    Num_type a = 1.0/parts;
    Num_type sum = 0.0;
    for(int i = 0; i < parts; ++i){
        sum += a; 
    }
    return sum;
}


int main(){
    try {
        cout << "Testing float: \n";
        cout << setprecision(15) << test_num_type_precistion<float>(333) << "\n";
        cout << setprecision(15) << test_num_type_precistion<float>(10) << "\n";
        cout << setprecision(15) << test_num_type_precistion<float>(2) << "\n";

        cout << "Testing double: \n";
        cout << setprecision(15) << test_num_type_precistion<double>(333) << "\n";
        cout << setprecision(15) << test_num_type_precistion<double>(10) << "\n";
        cout << setprecision(15) << test_num_type_precistion<double>(2) << "\n";

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
