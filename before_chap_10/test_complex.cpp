#include "std_lib_facilities.h"
#include <complex>
int main(){
    complex<float> f{1.0, 1.0};
    cout << f.real() << " + i" << f.imag() << "\n";
    double d = -1.0;
    complex<double> dc{d,0};
    complex<double> f1 = sqrt(dc);
    cout << f1.real() << " + i" << f1.imag() << "\n";
    double d1;
    cin >> d1;
    if(cin){
        cout << "ok\n";
    } else {
        cout << "not ok\n";
    }

    return 0;
}
