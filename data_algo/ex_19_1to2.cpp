#include <iostream>
#include <stdexcept>
#include <vector>

//#include "ex_19_1to2.hpp"
#include "catch.hpp"

using namespace std;

//------------------------------------------------------------------------------

template<typename T> //requires Number<T>()
void f(std::vector<T>& v1, const std::vector<T>& v2)
{
    for(int i = 0; i < v1.size(); ++i){
        if(i == v2.size()) break;
        v1[i] += v2[i];
    }
}

template<typename T> //requires Element<T>()
void print_vec(const vector<T>& v){
    cout << "{";
    for(int i = 0; i < v.size()-1; ++i){
        cout << v[i] << ", ";
    }
    cout << v[v.size()-1] << "}" << "\n";
}

template<typename T, typename U> //requires Number<T>(), requires Number<U>()
T g(vector<T>& vt, const vector<U>& vu){
    if(vt.size() == 0 || vu.size() == 0) 
        throw runtime_error("empty vector passed to g()");
    T ret = vt[0]*vu[0];
    for(int i = 1; i < vt.size(); ++i){
        if(i == vu.size()) break;
        ret += vt[i]*vu[i];
    }
    return ret;
}

//------------------------------------------------------------------------------

TEST_CASE("Template function accepts vectors of arbitrary type") {
    SECTION("Testing f - exercise 1"){
        vector<double> v1 {3.0, 4.0, 5.0};
        vector<double> v2 {0.1, 0.2, 0.3};
        vector<int> v3 {1, 2, 3};
        f(v1,v2);
        REQUIRE((v1[0] == 3.1 && v1[1] == 4.2 && v1[2] == 5.3));
    }
    SECTION("Testing g - exercise 2"){
        vector<double> v1 {3.0, 4.0, 5.0};
        vector<double> v2 {0.1, 0.2, 0.3};
        vector<double> v2_a {0.1, 0.2};
        vector<int> v3 {1, 2, 3};
        vector<int> v_emp(0);
        auto res_g1 = g(v3, v3);
        auto res_g2 = g(v1, v2_a);
        REQUIRE(res_g1 == 14);
        REQUIRE(res_g2 == 1.1);
        REQUIRE_THROWS_WITH(g(v_emp, v3), "empty vector passed to g()");
    }
}

//------------------------------------------------------------------------------
