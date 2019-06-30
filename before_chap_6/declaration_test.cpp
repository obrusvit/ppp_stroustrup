#include "std_lib_facilities.h"

int f(int i){
    return i;
}
int i = 10;
extern int i;
int main(){
    cout << f(i) << "\n";

    return 0;
}
