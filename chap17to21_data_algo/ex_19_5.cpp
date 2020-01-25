/*
 * Implement simple Int class having some nice features.
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

#include "catch.hpp"

using namespace std;

//------------------------------------------------------------------------------

class Int{
public:
    Int() : _val{0} {}
    Int(int v) : _val{v} {}

    int val() const { return _val; }

    /* copy constructor */
    Int(const Int& other){
        _val = other.val();
    }

    /* copy assignment */
    Int& operator=(const Int& a){
        _val = a.val();
        return *this;
    }

    Int& operator+=(const Int& rhs){
        _val = _val+rhs.val();
        return *this;
    }
private:
    int _val;
};

//------------------------------------------------------------------------------

Int operator+(const Int& a, const Int& b) {
    return Int(a.val() + b.val());
}
Int operator-(const Int& a, const Int& b) {
    return Int(a.val() - b.val());
}
Int operator*(const Int& a, const Int& b) {
    return Int(a.val() * b.val());
}
Int operator/(const Int& a, const Int& b) {
    return Int(a.val() / b.val());
}

bool operator==(const Int& i1, const Int& i2){
    return i1.val() == i2.val();
}

ostream& operator<<(ostream& os, const Int& i){
    os << "{Int: " << i.val() << "}";
    return os;
}
istream& operator>>(istream& is, Int& i){
    int v;
    is >> v;
    if(!is){
        is.clear(ios_base::failbit);
        return is;
    }
    i = Int(v); 
    return is;

}

//------------------------------------------------------------------------------

TEST_CASE("Testing exercise 5 of chapter 19") {
    SECTION("Construct some Ints"){
        Int i1;
        Int i2(5);
        Int i3(42);
        Int i4(47);
        Int i5(20);
        REQUIRE(i1.val() == 0);
        REQUIRE(i2.val() == 5);
        REQUIRE(i3.val() == 42);
        REQUIRE(i3+i2 == i4);
        REQUIRE(i3+i2 == 47); //implicit conversion
        REQUIRE(i5/i2 == 4);
        i1+=i2;
        REQUIRE(i1.val() == i2.val());

    }
    SECTION("Operators <<"){
        Int i1(10);
        Int i2(5);
        ostringstream os;
        os << i1;
        REQUIRE(os.str() == "{Int: 10}");
        os << i2;
        REQUIRE(os.str() == "{Int: 10}{Int: 5}");
    }
    SECTION("Operator >>"){
        Int i1;
        stringstream ss{"4"};
        ss >> i1;
        ostringstream os;
        os << i1;
        REQUIRE(os.str() == "{Int: 4}");

    }
    SECTION("Operator >> fails"){
        cout << "Enter int to init your Int\n";
        Int i2;
        cin >> i2;

        cout << "cin is ";
        if(cin.fail()) 
            cout << "not ";
        cout << "good\n";

        cout << i2 << "\n";
    }
}

//------------------------------------------------------------------------------
