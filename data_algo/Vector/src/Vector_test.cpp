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
//#include "Vector_with_handle.hpp"
#include "Vector_with_handle_std_complient.hpp"

// test also own implementation of allocator
#include "Allocator.hpp"

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
Vector<double, My_allocator<double>>* make_Vector_with_My_allocator(){
    std::unique_ptr<Vector<double, My_allocator<double>>> p {new Vector<double, My_allocator<double>>};
    p->push_back(4.1);
    p->push_back(3.2);
    return p.release();

}

//------------------------------------------------------------------------------

class Placeholder_obj{
};

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

    SECTION("Testing Vector, std compliancy - with range access in algorithm "){
        Vector<double> v1(10);
        std::iota(v1.begin(), v1.end(), 7);
        REQUIRE(v1.size() == 10);
        REQUIRE(v1.at(0) == 7);
        REQUIRE(v1.at(1) == 8);
        REQUIRE(v1.at(2) == 9);
        REQUIRE(v1.at(3) == 10);
        REQUIRE(v1.at(4) == 11);
        REQUIRE(v1.at(5) == 12);
        REQUIRE(v1.at(6) == 13);
        REQUIRE(v1.at(7) == 14);
        REQUIRE(v1.at(8) == 15);
        REQUIRE(v1.at(9) == 16);
        REQUIRE_THROWS_AS(v1.at(10) == 17, std::out_of_range);
    }
    SECTION("Testing Vector, std compliancy - erase"){
        Vector<double> v1(10);
        std::iota(v1.begin(), v1.end(), 7);
        REQUIRE(*(v1.end()-1) == 16); //last element is now 16
        v1.erase(v1.end()-1);
        REQUIRE(v1.size() == 9);
        REQUIRE(*(v1.end()-1) == 15); //last element is now 15

        Vector<double> v2(10);
        std::iota(v2.begin(), v2.end(), 7);
        v2.erase(v2.begin());
        v2.erase(v2.begin());
        REQUIRE(v2.size() == 8);
        REQUIRE(v2.at(0) == 9);
        REQUIRE(v2.at(1) == 10);
        REQUIRE(v2.at(v2.size()-1) == 16);
    }

    SECTION("Testing Vector, std compliancy - insert"){
        Vector<double> v1(10);
        std::iota(v1.begin(), v1.end(), 7);
        v1.insert(v1.begin(), 100);
        REQUIRE(v1.size() == 11);
        REQUIRE(v1.at(0) == 100);
        REQUIRE(v1.at(1) == 7);
        REQUIRE(v1.at(2) == 8);
        REQUIRE(v1.at(v1.size()-1) == 16);

        v1.insert(v1.begin(), 200);
        REQUIRE(v1.size() == 12);
        REQUIRE(v1.at(0) == 200);
        REQUIRE(v1.at(1) == 100);
        REQUIRE(v1.at(2) == 7);
        REQUIRE(v1.at(3) == 8);
        REQUIRE(v1.at(v1.size()-1) == 16);

        v1.insert(v1.begin()+3, 300);
        REQUIRE(v1.size() == 13);
        REQUIRE(v1.at(0) == 200);
        REQUIRE(v1.at(1) == 100);
        REQUIRE(v1.at(2) == 7);
        REQUIRE(v1.at(3) == 300);
        REQUIRE(v1.at(v1.size()-1) == 16);
    }
    // 13.45
    SECTION("Testing Vector, std compliancy - insert and erase on one Vector"){
        Vector<double> v1(10);
        std::iota(v1.begin(), v1.end(), 7);
        v1.insert(v1.begin(), 100);
        REQUIRE(v1.at(0) == 100);
        REQUIRE(v1.at(1) == 7);
        REQUIRE(v1.at(v1.size()-1) == 16);
        REQUIRE(v1.size() == 11);
        v1.erase(v1.begin());
        REQUIRE(v1.size() == 10);
        REQUIRE(v1.at(0) == 7);
        REQUIRE(v1.at(1) == 8);
        REQUIRE(v1.at(v1.size()-1) == 16);
        
    }
}

//------------------------------------------------------------------------------

TEST_CASE("Testing My_allocator with my implementation of Vector<T>") {
    SECTION("Initialization"){
        Vector<double, My_allocator<double>> vec1;
        Vector<double, My_allocator<double>> vec2(3);
        Vector<double, My_allocator<double>> vec3{1.1, 1.2, 1.3, 1.4};

        REQUIRE(vec1.size() == 0);
        REQUIRE(vec2.size() == 3);
        REQUIRE(vec2.at(1) == 0.0);
        REQUIRE(vec2[1] == 0.0);
        REQUIRE(vec3.size() == 4);
    }

    SECTION("Copy constuction and copy assignment"){
        Vector<double, My_allocator<double>> vec1{1.1, 1.2, 1.3, 1.4};
        Vector<double, My_allocator<double>> vec2 = vec1;
        REQUIRE(vec1.size() == vec2.size());
        REQUIRE(vec1.at(0) == vec2.at(0));
        REQUIRE(vec1.at(1) == vec2.at(1));
        REQUIRE(vec1.at(2) == vec2.at(2));

        Vector<double, My_allocator<double>> vec3{3.1, 3.2, 3.3, 3.4, 3.5};
        vec3 = vec1;
        REQUIRE(vec3.size() == vec1.size());
        REQUIRE(vec3.at(0) == vec1.at(0));
        REQUIRE(vec3.at(1) == vec1.at(1));
        REQUIRE(vec3.at(2) == vec1.at(2));
    }

    SECTION("Access operator[], at()"){
        Vector<double, My_allocator<double>> vec1{1.1, 1.2, 1.3, 1.4};
        REQUIRE(vec1[0] == 1.1);
        REQUIRE(vec1.at(0) == 1.1);
        vec1[0] = 8.1;
        REQUIRE(vec1[0] == 8.1);
        REQUIRE(vec1.at(0) == 8.1);

        REQUIRE(vec1.at(vec1.size()-1) == 1.4);
        REQUIRE_THROWS_AS(vec1.at(vec1.size()), std::out_of_range);
    }
    SECTION("Growing vector - push_back(), capacity() and resize()"){
        Vector<double, My_allocator<double>> vec1{1.1, 1.2, 1.3, 1.4};
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
        Vector<No_default, My_allocator<No_default>> vec1;
        REQUIRE(vec1.size() == 0);
        vec1.push_back(n1);
        vec1.push_back(n2);

        //Vector<No_default> vec2(5); //error
        Vector<No_default, My_allocator<No_default>> vec2(5, 'd');
    }

    SECTION("Testing make_Vector_with_My_allocator"){
        Vector<double, My_allocator<double>>* p = make_Vector_with_My_allocator();
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
