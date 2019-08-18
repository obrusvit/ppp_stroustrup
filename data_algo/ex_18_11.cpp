/*
 * Chap 18, ex 11
 * Skip list
 */
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    try {
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
