#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;
long addr_to_int(void* ptr){
    ostringstream ss;
    ss << ptr;
    istringstream iss(ss.str());
    long ret;
    iss >> hex >> ret;
    return ret;
}
void sizes(char ch, char* chp, int n, int* p, double d, double* dp){
    cout << "sizeof()...\n";
    cout << "char \t" << sizeof(ch) << " "<<  sizeof(char) << "\n";
    cout << "char* \t" << sizeof(chp) << " "<<  sizeof(char*) << "\n";
    cout << "int \t" << sizeof(n) << " "<<  sizeof(int) << "\n";
    cout << "int* \t" << sizeof(p) << " "<<  sizeof(int*) << "\n";
    cout << "double \t" << sizeof(d) << " "<<  sizeof(double) << "\n";
    cout << "double*\t" << sizeof(dp) << " "<<  sizeof(double*) << "\n";
}
int main(){
    try {
        // ex 1
        int* i = new int(17);
        cout << i << ", " << *i << "\n";
        *i = 8;
        cout << i << ", " << *i << "\n";

        // ex 2
        cout << "int\n";
        int* ai = new int[4]{4,5,6,7};
        cout << reinterpret_cast<char*>(&ai[1]) - reinterpret_cast<char*>(&ai[0]) << "\n";
        cout << addr_to_int(&ai[1]) - addr_to_int(&ai[0]) << "\n";

        cout << "float\n";
        float * af = new float[10];
        cout << reinterpret_cast<char*>(&af[1]) - reinterpret_cast<char*>(&af[0]) << "\n";
        cout << addr_to_int(&af[1]) - addr_to_int(&af[0]) << "\n";

        cout << "double\n";
        double * ad = new double[10];
        cout << reinterpret_cast<char*>(&ad[1]) - reinterpret_cast<char*>(&ad[0]) << "\n";
        cout << addr_to_int(&ad[1]) - addr_to_int(&ad[0]) << "\n";

        cout << "bool\n";
        bool * ab = new bool[10];
        cout << reinterpret_cast<char*>(&ab[1]) - reinterpret_cast<char*>(&ab[0]) << "\n";
        cout << addr_to_int(&ab[1]) - addr_to_int(&ab[0]) << "\n";


        char ch1 = 'a';
        double d1 = 4.0;
        sizes(ch1, &ch1, 4, i, d1, &d1);

        
        delete i;
        delete[] ai;
        delete[] af;
        delete[] ad;
        delete[] ab;

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
