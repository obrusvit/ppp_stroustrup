#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <array>

using namespace std;

template<typename It>
It high_it(It first, It last){
    if(first == last){
        cout << "empty container in high_it\n";
        return last; 
    }
    It high = first;
    for(It current = first; current != last; ++current){
        if(*high < *current){
            high = current;
        }
    }
    return high;
}

double* high(double* first, double* last){
    if(first == nullptr || last == nullptr){
        cout << "bad input\n";
        return nullptr;
    }
   double high = -1.0;
   double* phigh;
   for(double* current = first; current != last; ++current){
       if((*current) > high){
           phigh = current;
           high = *current;
       }
   }
   return phigh;
}

void copy(int* b1, int* e1, int* b2){
    while(b1!=e1)
        *(b2++) = *(b1++);
}

void test_copy(){
    int* int_arr1 = new int[5];
    int_arr1[0] = 0;
    int_arr1[1] = 1;
    int_arr1[2] = 2;
    int_arr1[3] = 3;
    int_arr1[4] = 4;

    int* int_arr2 = new int[5];
    copy(int_arr1, int_arr1+5, int_arr2);
    cout << "test copy:\n";
    for(int i = 0; i < 5; ++i){
        cout << int_arr2[i] << "\n";
    }
}


int main(){
    try {
        test_copy();
        double jack[] = {1.1, 5.1, 1.2, 1.3, 2.1, 7.2};
        double jack2[] = {};
        vector<double> jill{1.1, 5.1, 1.2, 1.3, 2.1, 7.2};
        vector<double> jill2{};
        array<double, 6> arr1{1.1, 5.1, 1.2, 1.3, 2.1, 7.2};

        double* jack_high = high_it(jack, jack+6);
        double* jack2_high = high_it(jack2, jack2+6); //undefined behaviour?
        auto jill_high = high_it(jill.begin(), jill.end());
        auto jill2_high = high_it(jill2.begin(), jill2.end());
        auto arr_high = high_it(arr1.begin(), arr1.end());


        cout << "Jack's high: " << *jack_high << ",\n"
             << "Jack2's high: " << *jack2_high << ",\n"
            << "Jill's high: " << *jill_high << ".\n"
            << "array high: " << *arr_high << ".\n";
        if(jill2_high != jill2.end()){
            cout << "Jill2's high: " << *jill2_high << "\n";
        }

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
