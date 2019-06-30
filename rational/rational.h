#ifndef GUARD_RATIONAL
#define GUARD_RATIONAL
#include <iostream>

//------------------------------------------------------------------------------

namespace Rational_number{

class Rational{
public:
    class Invalid{ };
    Rational(int num, int denum);

    void normalize();

    // non-modifying
    int num() const { return numerator; }
    int denum() const { return denumerator; }

private:
    int numerator;
    int denumerator;
};

//------------------------------------------------------------------------------
// arithmetic operators
Rational operator+(Rational& r1, Rational& r2);
Rational operator-(Rational& r1, Rational& r2);
Rational operator*(Rational& r1, Rational& r2);
Rational operator/(Rational& r1, Rational& r2);
Rational operator-(Rational& r); //unary minus

//------------------------------------------------------------------------------
// util operators
std::ostream& operator<<(std::ostream& os, const Rational& rat);
bool operator==(const Rational& r1, const Rational& r2);
bool operator!=(const Rational& r1, const Rational& r2);

//------------------------------------------------------------------------------
// utils
int gcd(int a, int b);

} //Rational
#endif
