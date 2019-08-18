#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    try {
        while(true){
            // consume RAM pretty quickly
            char* not_todel = new char[1000];
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
