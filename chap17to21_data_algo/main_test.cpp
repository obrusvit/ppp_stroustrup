/*
 * Use with test.cpp where main from Catch is specified
 * compile like this:
 * c++ test.cpp -c 
 * c++ this.cpp test.o -o program
 */
#include <iostream>
#include <stdexcept>
#include <vector>

#include "catch.hpp"

using namespace std;

//------------------------------------------------------------------------------

TEST_CASE("") {
    SECTION(""){
        REQUIRE(1==1);
    }
}

//------------------------------------------------------------------------------
