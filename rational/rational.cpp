#include"rational.h"
#include "std_lib_facilities.h"

namespace Rational_number{

//------------------------------------------------------------------------------
// members

Rational::Rational(int num, int denum)
    : numerator{num}, denumerator{denum}
{
    if(denum == 0) error("division by zero");
    normalize();
}

void Rational::normalize(){
    if(denumerator < 0){
       numerator = -numerator;
       denumerator = -denumerator;
    }
    int greatest_denum = gcd(numerator, denumerator);
    if(greatest_denum > 1){
        numerator/= greatest_denum;
        denumerator /= greatest_denum;
    }

}

//------------------------------------------------------------------------------
// arithmetic operators
Rational operator+(Rational& r1, Rational& r2){
    Rational r = Rational{r1.num()*r2.denum() + r1.denum()*r2.num(), r1.denum()*r2.denum()};
    r.normalize();
    return r;
}
Rational operator-(Rational& r1, Rational& r2){
    Rational r = Rational{r1.num()*r2.denum() - r1.denum()*r2.num(), r1.denum()*r2.denum()};
    r.normalize();
    return r;
}

Rational operator*(Rational& r1, Rational& r2){
    Rational r = Rational{r1.num()*r2.num(), r1.denum()*r2.denum()};
    r.normalize();
    return r;
}
Rational operator/(Rational& r1, Rational& r2){
    Rational r = Rational{r1.num()*r2.denum(), r1.denum()*r2.num()};
    r.normalize();
    return r;
}

Rational operator-(Rational& r1){
    Rational r = Rational{-r1.num(), r1.denum()};
    r.normalize();
    return r;
}

//------------------------------------------------------------------------------
// util operators
std::ostream& operator<<(std::ostream& os, const Rational& rat){
    return os << rat.num() << "/" << rat.denum(); 
}
bool operator==(const Rational& r1, const Rational& r2){
    return r1.num() * r2.denum() == r1.denum() * r2.num();
}
bool operator!=(const Rational& r1, const Rational& r2){
    return !(r1==r2);
}

//------------------------------------------------------------------------------
// utils
int gcd(int a, int b){
    a = abs(a);
    b = abs(b);
    if(a==b) return a;
    if(a>b) return gcd(a-b, b);
    if(a<b) return gcd(a, b-a);
    return 1;
}

double to_double(Rational& r){
    return double(r.num())/r.denum();
}

} // Rational

//------------------------------------------------------------------------------

//int main(){
//    try{
//        using Rational_number::Rational;
//
//        Rational r1(1,2);
//        Rational r2(3,9);
//        
//        cout << r1 << "\n";
//        cout << r2 << "\n";
//
//        Rational r3 = r1+r2;
//        cout << r3 << "\n";
//        cout << to_double(r3) << "\n";
//
//        Rational r4{3,-1};
//        cout << r4 << "\n";
//        r4.normalize();
//        cout << r4 << "\n";
//
//
//    }catch(runtime_error e){
//        cerr << e.what() << "\n";
//    }catch(...){
//        cerr << "other error occured\n";
//    }
//
//}
