#include "std_lib_facilities.h"
#include <complex>
double comp_discriminant(double a, double b, double c){
    return pow(b,2)-4*a*c;
}
int main(){
    vector<double> coeffs_buff;
    double temp;
    while((cin>>temp)){
        coeffs_buff.push_back(temp);
        if(coeffs_buff.size() == 3) break;
    }
    if(!cin){
        error("wrong input");
    }
    if(coeffs_buff.size() != 3){
        error("wrong number of coeffs: " , coeffs_buff.size());
    }
    for(double d : coeffs_buff){
        cout << d << ", ";
    }
    double a, b, c;
    a = coeffs_buff[0];
    b = coeffs_buff[1];
    c = coeffs_buff[2];
    double D = comp_discriminant(a, b, c);

    cout << "a = " << a << ", b = " << b << ", c = " << c << "\n";
    cout << "(" << a << ")" << "x^2 + ";
    cout << "(" << b << ")" << "x + ";
    cout << "(" << c << ")" << "\n";
    cout << "D = " << D << "\n";

    if(D < 0){
        complex<double> D_complex{D,0.0};
        complex<double> sqrt_D = sqrt(D_complex);
        complex<double>  x_1 = (-b + sqrt_D)/(2*a);
        complex<double>  x_2 = (-b - sqrt_D)/(2*a);
        cout << "x1 = " << x_1.real() << "+ i" << x_1.imag() << ", ";
        cout << "x2 = " << x_2.real() << "+ i" << x_2.imag() << "\n";
    } else if (D == 0){
        double x = (-b + sqrt(D))/(2*a);
        cout << "x = " << x  << "\n";

    } else {
        double x_1 = (-b + sqrt(D))/(2*a);
        double x_2 = (-b - sqrt(D))/(2*a);
        cout << "x1 = " << x_1 << ", x2 = " << x_2 << "\n";
    }

    return 0;
}
