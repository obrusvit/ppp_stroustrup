#include "../std_lib_facilities.h"

long int factorial(int n){
    if(n == 0 || n == 1)
        return 1;
    else 
        return n*factorial(n-1);
}
int main(){

    for(int i = 0; i <= 25; ++i){
        cout << factorial(i) << "\n";
    }

    cout << narrow_cast<int, double>(3.1) << "\n";
}
