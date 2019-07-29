#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void print_array10(ostream& os, int* a){
    for(int i = 0; i <10; ++i){
        os << a[i] << "\n";
    }
    os << "\n";
}

void print_array(ostream& os, int* a, int n){
    for(int i = 0; i < n; ++i){
        os << a[i] << "\n";
    }
    os << "\n";
}

void print_vector(ostream& os, const vector<int>& v){
    for(const int& i : v){
        os << i << "\n";
    }
    os << "\n";
}

//------------------------------------------------------------------------------

void print_ptr_and_val(int* p){
    cout << "addres: " << p << ", value: " << *p << "\n";
}

//------------------------------------------------------------------------------

int main(){
    try {

        // 1st part
        int* ip = new int[10];
        for(int i = 0; i < 10; ++i){
            ip[i] = i;
        }
        cout << ip << "\n";
        for(int i = 0; i < 10; ++i){
            cout << i << ": " << ip[i] << "\n";
        }

        print_array10(cout, ip);
        delete[] ip;

        int* ip2 = new int[11];
        for(int i = 0; i < 11; ++i){
            ip2[i] = 100 + i;
        }

        print_array10(cout, ip2);
        print_array(cout, ip2, 11);

        delete[] ip2;

        vector<int> v;
        for(int i = 0; i < 10; ++i){
            v.push_back(i);
        }
        print_vector(cout, v);

        // 2nd part
        int i1 = 7;
        int* p1 = &i1;
        print_ptr_and_val(p1);


        int i2[] {1, 2, 4, 8, 16, 32, 64};
        int* p2 = &i2[0];
        for(int i = 0; i<7; ++i){

            cout << p2[i] << "\n";
        }

        int* p3 = p2;
        p2 = p1;
        p2 = p3;
        print_ptr_and_val(p1);
        print_ptr_and_val(p2);
        print_ptr_and_val(p3);
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
