/*
 * Implement Number<T> template class
 * and test it on template functions from ex 1,2
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

#include "catch.hpp"
#include "ex_19_1to2.hpp" //f,g

using namespace std;

//------------------------------------------------------------------------------

template<typename N>
class Number{
public:
    Number() : _val{0} {}
    Number(N v) : _val{v} {}

    N val() const { return _val; }

    operator N() const {
        return _val;
    }

    /* copy constructor */
    Number(const Number& other){
        _val = other.val();
    }

    /* copy assignment */
    Number& operator=(const Number& a){
        _val = a.val();
        return *this;
    }

    Number& operator+=(const Number& rhs){
        _val = _val+rhs.val();
        return *this;
    }
private:
    N _val;
};

//------------------------------------------------------------------------------

template <typename N>
Number<N> operator+(const Number<N>& a, const Number<N>& b) {
    return Number<N>(a.val() + b.val());
}
template <typename N>
Number<N> operator-(const Number<N>& a, const Number<N>& b) {
    return Number<N>(a.val() - b.val());
}
template <typename N>
Number<N> operator*(const Number<N>& a, const Number<N>& b) {
    return Number<N>(a.val() * b.val());
}
template <typename N>
Number<N> operator/(const Number<N>& a, const Number<N>& b) {
    return Number<N>(a.val() / b.val());
}
template <typename N>
Number<N> operator%(const Number<N>& a, const Number<N>& b) {
    return Number<N>(a.val() % b.val());
}

template <typename N>
bool operator==(const Number<N>& i1, const Number<N>& i2){
    return i1.val() == i2.val();
}

//------------------------------------------------------------------------------
// >> <<

template <typename N>
ostream& operator<<(ostream& os, const Number<N>& i){
    os << "{Number: " << i.val() << "}";
    return os;
}
template <typename N>
istream& operator>>(istream& is, Number<N>& i){
    N v;
    is >> v;
    if(!is){
        is.clear(ios_base::failbit);
        return is;
    }
    i = Number<N>(v); 
    return is;

}

//------------------------------------------------------------------------------

TEST_CASE("Testing exercise 6 of chapter 19") {
    SECTION("Construct some Numbers of type int"){
        Number<int> i1;
        Number<int> i2(5);
        Number<int> i3(42);
        Number<int> i4(47);
        Number<int> i5(20);
        REQUIRE(i1.val() == 0);
        REQUIRE(i2.val() == 5);
        REQUIRE(i3.val() == 42);
        REQUIRE(i3+i2 == i4);
        REQUIRE(i3+i2 == 47); //implicit conversion
        REQUIRE(i5/i2 == 4);
        i1+=i2;
        REQUIRE(i1.val() == i2.val());
        REQUIRE(i3%i2 == 2);

        // copy constructor
        Number<int> i6 = i1;
        REQUIRE(i6.val() == i1.val());

        //copy assignment
        i6 = i5;
        REQUIRE(i6.val() != i1.val());
        REQUIRE(i6.val() == i5.val());
    }
    SECTION("Construct some Numbers of type double"){
        Number<double> i1;
        Number<double> i2(5.0);
        Number<double> i3(42.0);
        Number<double> i4(47.0);
        Number<double> i5(20.0);
        REQUIRE(i1.val() == 0);
        REQUIRE(i2.val() == 5);
        REQUIRE(i3.val() == 42);
        REQUIRE(i3+i2 == i4);
        REQUIRE(i3+i2 == 47); //implicit conversion
        REQUIRE(i5/i2 == 4);
        i1+=i2;
        REQUIRE(i1.val() == i2.val());
        /* the following does not compile, invalid operands to operator% */
        //REQUIRE(i3%i2 == 2);
    }
    SECTION("Operators <<"){
        Number<int> i1(10);
        Number<int> i2(5);
        ostringstream os;
        os << i1;
        REQUIRE(os.str() == "{Number: 10}");
        os << i2;
        REQUIRE(os.str() == "{Number: 10}{Number: 5}");
    }
    SECTION("Operator >>"){
        Number<int> i1;
        stringstream ss{"4"};
        ss >> i1;
        ostringstream os;
        os << i1;
        REQUIRE(os.str() == "{Number: 4}");

    }
    //SECTION("Operator >> fails"){
    //    cout << "Enter int to init your Int\n";
    //    Int i2;
    //    cin >> i2;

    //    cout << "cin is ";
    //    if(cin.fail()) 
    //        cout << "not ";
    //    cout << "good\n";

    //    cout << i2 << "\n";
    //}
}

//------------------------------------------------------------------------------

TEST_CASE("Testing exercise 7 of chapter 19"){
    SECTION("Init some vector with my Number<N> template class"){
        vector<Number<int>> v1{1, 2, 3}; 
        vector<Number<int>> v2{4, 5, 6}; 
        auto res_g1 = g(v1, v2);
        REQUIRE(res_g1 == 32);

    }
}

//------------------------------------------------------------------------------
