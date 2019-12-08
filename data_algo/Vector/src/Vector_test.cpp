/*
 * Test Vector implementations.
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>

#include "catch.hpp"

#include "Vector_double.hpp"

//#include "Vector_simplest.hpp"
//#include "Vector_simple.hpp"
#include "Vector_with_handle.hpp"

using namespace std;

//------------------------------------------------------------------------------

Vector_double return_large_Vector_double(){
    cout << "Measuring init of Vector_double...\n";
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Vector_double ret(100000000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
    cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    return ret;
}

Vector<double> return_large_Vector(){
    cout << "Measuring init of Vector<double>...\n";
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Vector<double> ret(100000000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
    cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    return ret;
}

vector<double> return_large_vector(){
    cout << "Measuring init of std::vector<double>...\n";
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<double> ret(100000000);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
    cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    return ret;
}

Vector<double>* make_Vector(){
    std::unique_ptr<Vector<double>> p {new Vector<double>};
    p->push_back(4.1);
    p->push_back(3.2);
    return p.release();
}

vector<double>* make_vector(){
    std::unique_ptr<vector<double>> p {new vector<double>};
    p->push_back(4.1);
    p->push_back(3.2);
    return p.release();
}


//------------------------------------------------------------------------------

class No_default{
    char val;

    public:
    No_default(char c)
        : val{c}
    {
    }
};

//------------------------------------------------------------------------------

TEST_CASE("Testing Vector_double") {
    SECTION("Initialization"){
        Vector_double vec1;
        Vector_double vec2(3);
        Vector_double vec3{1.1, 1.2, 1.3, 1.4};

        REQUIRE(vec1.size() == 0);
        REQUIRE(vec2.size() == 3);
        REQUIRE(vec2.at(1) == 0.0);
        REQUIRE(vec3.size() == 4);
    }
    SECTION("Copy constuction and copy assignment"){
        Vector_double vec1{1.1, 1.2, 1.3, 1.4};
        Vector_double vec2 = vec1;
        REQUIRE(vec1.size() == vec2.size());
        REQUIRE(vec1.at(0) == vec2.at(0));
        REQUIRE(vec1.at(1) == vec2.at(1));
        REQUIRE(vec1.at(2) == vec2.at(2));

        Vector_double vec3{3.1, 3.2, 3.3, 3.4, 3.5};
        vec3 = vec1;
        REQUIRE(vec3.size() == vec1.size());
        REQUIRE(vec3.at(0) == vec1.at(0));
        REQUIRE(vec3.at(1) == vec1.at(1));
        REQUIRE(vec3.at(2) == vec1.at(2));
    }
    SECTION("Move constructor"){
        // for testing how move constuctor helps.
        // (un)comment move constructor/assignment and try.
        // compile with -fno-elide-constructors to get "pure" effect without 
        // compiler optimizations.
        cout << "Measuring returning vector from function...\n";
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

        Vector_double returned =  return_large_Vector_double();

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
        cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    }
    SECTION("Access operator[]"){
        Vector_double vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1[0] == 1.1);
        vec1[0] = 8.1;
        REQUIRE(vec1[0] == 8.1);
    }
    SECTION("Growing vector - push_back(), capacity() and resize()"){
        Vector_double vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1.size() == 4);
        REQUIRE(vec1.capacity() == 4);
        vec1.push_back(1.5);
        REQUIRE(vec1.size() == 5);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.6);
        vec1.push_back(1.7);
        vec1.push_back(1.8);
        REQUIRE(vec1.size() == 8);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.9);
        REQUIRE(vec1.size() == 9);
        REQUIRE(vec1.capacity() == 16);

        vec1.resize(20);
        REQUIRE(vec1.size() == 20);
        REQUIRE(vec1.capacity() == 20);
        
    }
}

//------------------------------------------------------------------------------

TEST_CASE("Testing my implementation of Vector<T>") {
    SECTION("Initialization"){
        Vector<double> vec1;
        Vector<double> vec2(3);
        Vector<double> vec3{1.1, 1.2, 1.3, 1.4};

        REQUIRE(vec1.size() == 0);
        REQUIRE(vec2.size() == 3);
        REQUIRE(vec2.at(1) == 0.0);
        REQUIRE(vec2[1] == 0.0);
        REQUIRE(vec3.size() == 4);
    }
    SECTION("Copy constuction and copy assignment"){
        Vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        Vector<double> vec2 = vec1;
        REQUIRE(vec1.size() == vec2.size());
        REQUIRE(vec1.at(0) == vec2.at(0));
        REQUIRE(vec1.at(1) == vec2.at(1));
        REQUIRE(vec1.at(2) == vec2.at(2));

        Vector<double> vec3{3.1, 3.2, 3.3, 3.4, 3.5};
        vec3 = vec1;
        REQUIRE(vec3.size() == vec1.size());
        REQUIRE(vec3.at(0) == vec1.at(0));
        REQUIRE(vec3.at(1) == vec1.at(1));
        REQUIRE(vec3.at(2) == vec1.at(2));
    }
    SECTION("Move constructor"){
        // for testing how move constuctor helps.
        // (un)comment move constructor/assignment and try.
        // compile with -fno-elide-constructors to get "pure" effect without 
        // compiler optimizations.
        cout << "Measuring returning vector from function...\n";
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

        Vector<double> returned =  return_large_Vector();

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
        cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    }
    SECTION("Access operator[], at()"){
        Vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1[0] == 1.1);
        REQUIRE(vec1.at(0) == 1.1);
        vec1[0] = 8.1;
        REQUIRE(vec1[0] == 8.1);
        REQUIRE(vec1.at(0) == 8.1);

        REQUIRE(vec1.at(vec1.size()-1) == 1.4);
        REQUIRE_THROWS_AS(vec1.at(vec1.size()), std::out_of_range);
    }
    SECTION("Growing vector - push_back(), capacity() and resize()"){
        Vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1.size() == 4);
        REQUIRE(vec1.capacity() == 4);
        vec1.push_back(1.5);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 5);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.6);
        vec1.push_back(1.7);
        vec1.push_back(1.8);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 8);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.9);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 9);
        REQUIRE(vec1.capacity() == 16);
        vec1.resize(20);
        REQUIRE(vec1.size() == 20);
        REQUIRE(vec1.capacity() == 20);
    }
    SECTION("Testing Vector with custom class with no default constructor"){
        No_default n1('a');
        No_default n2('b');
        Vector<No_default> vec1;
        REQUIRE(vec1.size() == 0);
        vec1.push_back(n1);
        vec1.push_back(n2);

        //Vector<No_default> vec2(5); //error
        Vector<No_default> vec2(5, 'd');
    }

    SECTION("Testing make_Vector"){
        Vector<double>* p = make_Vector();
        delete p;
    }
}

//------------------------------------------------------------------------------

TEST_CASE("Testing std::vector<T>") {
    SECTION("Initialization"){
        vector<double> vec1;
        vector<double> vec2(3);
        vector<double> vec3{1.1, 1.2, 1.3, 1.4};

        REQUIRE(vec1.size() == 0);
        REQUIRE(vec2.size() == 3);
        REQUIRE(vec2.at(1) == 0.0);
        REQUIRE(vec2[1] == 0.0);
        REQUIRE(vec3.size() == 4);
    }
    SECTION("Copy constuction and copy assignment"){
        vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        vector<double> vec2 = vec1;
        REQUIRE(vec1.size() == vec2.size());
        REQUIRE(vec1.at(0) == vec2.at(0));
        REQUIRE(vec1.at(1) == vec2.at(1));
        REQUIRE(vec1.at(2) == vec2.at(2));

        vector<double> vec3{3.1, 3.2, 3.3, 3.4, 3.5};
        vec3 = vec1;
        REQUIRE(vec3.size() == vec1.size());
        REQUIRE(vec3.at(0) == vec1.at(0));
        REQUIRE(vec3.at(1) == vec1.at(1));
        REQUIRE(vec3.at(2) == vec1.at(2));
    }
    SECTION("Move constructor"){
        // for testing how move constuctor helps.
        // (un)comment move constructor/assignment and try.
        // compile with -fno-elide-constructors to get "pure" effect without 
        // compiler optimizations.
        cout << "Measuring returning vector from function...\n";
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

        vector<double> returned =  return_large_vector();

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
        cout << "Done. Time difference: " << t_elapsed << "[miliseconds].\n";
    }
    SECTION("Access operator[], at()"){
        vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1[0] == 1.1);
        REQUIRE(vec1.at(0) == 1.1);
        vec1[0] = 8.1;
        REQUIRE(vec1[0] == 8.1);
        REQUIRE(vec1.at(0) == 8.1);

        REQUIRE(vec1.at(vec1.size()-1) == 1.4);
        REQUIRE_THROWS_AS(vec1.at(vec1.size()), std::out_of_range);
    }
    SECTION("Growing vector - push_back(), capacity() and resize()"){
        vector<double> vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1.size() == 4);
        REQUIRE(vec1.capacity() == 4);
        vec1.push_back(1.5);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 5);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.6);
        vec1.push_back(1.7);
        vec1.push_back(1.8);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 8);
        REQUIRE(vec1.capacity() == 8);
        vec1.push_back(1.9);
        REQUIRE(vec1.at(0) == 1.1);
        REQUIRE(vec1.at(1) == 1.2);
        REQUIRE(vec1.size() == 9);
        REQUIRE(vec1.capacity() == 16);
        vec1.resize(20);
        REQUIRE(vec1.size() == 20);
        REQUIRE(vec1.capacity() == 20);
    }
    SECTION("Testing vector with custom class with no default constructor"){
        //No_default n1('a');
        //No_default n2('b');
        //vector<No_default> vec1;
        //REQUIRE(vec1.size() == 0);
        //vec1.push_back(n1);
        //vec1.push_back(n2);

        ////vector<No_default> vec2(5); //error
        //vector<No_default> vec2(5, 'd');
    }

    SECTION("Testing make_vector"){
        vector<double>* p = make_vector();
        delete p;
    }

}
//------------------------------------------------------------------------------
