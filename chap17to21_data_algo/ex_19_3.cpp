/*
 * Implement Pair class
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "catch.hpp"

using namespace std;

//------------------------------------------------------------------------------

template <typename T, typename U>
class Pair{
public:
    Pair(T t, U u)
        : _first{t}, _second{u}
    {
    }

    T first(){
        return _first;
    }
    U second(){
        return _second;
    }

private:
        T _first;
        U _second;
};

struct C {
};
struct D {
};

//------------------------------------------------------------------------------

TEST_CASE("Creating Pair should work with arbitrary types") {
    SECTION("Create some and check their values"){
        Pair<int, double> p1(42, 4.2);
        Pair<string, char> p2("Hello from Pair", 'p');
        Pair<double, double> p3(1.4, 0.6);
        C c;
        D d;
        Pair<C, D> p4(c, d);
        REQUIRE(p1.first() == 42);
        REQUIRE(p1.second() == 4.2);
        REQUIRE(p2.first() == "Hello from Pair");
        REQUIRE(p2.second() == 'p');
        REQUIRE(p3.first() + p3.second() == 2.0);
        C c_taken = p4.first();
        REQUIRE(dynamic_cast<C*>(&c_taken));
    }
}

//------------------------------------------------------------------------------
