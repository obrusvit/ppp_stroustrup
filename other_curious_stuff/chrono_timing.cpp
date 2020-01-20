#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace std;


int main(){
    try {
        int n = 10000000;
        auto t1 = std::chrono::system_clock::now();

        for(int i = 0; i < n; ++i){
            cout << "i, ";
        }
        cout << "\n";

        auto t2 = std::chrono::system_clock::now();

        cout << "it took: " 
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t2).count() << " millisecons\n";

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
