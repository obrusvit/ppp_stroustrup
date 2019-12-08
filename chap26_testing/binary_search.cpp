#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include<fstream>

#include "my_binary_search.hpp"
#include "my_linear_search.hpp"
#include "../std_lib_facilities.h"

using namespace std;

//------------------------------------------------------------------------------

struct Test{
    string label;
    int val;
    vector<int> sequence;
    bool res;
};

//------------------------------------------------------------------------------

void print_read_test(const Test& t){
    cout << "test read:\n"
        << " label: " << t.label << "\n"
        << " val: " << t.val << "\n"
        << " sequence: ";
    for(auto& s : t.sequence){
        cout << s << " " ;
    }
    cout << "\n";
    cout << " res: " << t.res << "\n";
}

//------------------------------------------------------------------------------

istream& operator>>(istream& is, Test& t){
    // not very good error handling
    string label;
    int val;
    int seq_in;
    vector<int> sequence;
    int res_t;
    bool res;

    char c;
    is >> c;
    if(is.eof()){
        return is;
    }
    if(c != '{') throw runtime_error("{ expected at the beginning of the test");
    is >> label;
    is >> val;

    is >> c;
    if(c != '{') throw runtime_error("{ expected at the beginning of a sequence");
    while(is>>seq_in){
        sequence.push_back(seq_in);
    }
    is.clear();
    is >> c;
    if(c != '}') throw runtime_error("} expected at the end of a sequence");

    is >> res_t;
    if(res_t == 1) res = true;
    else res = false;
    is >> c;
    if(c != '}') throw runtime_error("} expected at the end of a test");

    t.label = label;
    t.val = val;
    t.sequence = sequence;
    t.res = res;
    //print_read_test(t);

    return is;
}

//------------------------------------------------------------------------------

void make_test(const string& lab, int val, int n, int base, int spread, ofstream& ofs){
    //it's different than the previous tests, won't deal with that now.

    ofs << "{ " << lab << " " << val << " { ";
    vector<int> v;
    int elem = base;
    for(int i = 0; i<n; ++i){
        elem += randint(spread);
        v.push_back(elem);
    }

    bool found = false;
    for(int i=0; i < n; ++i){
        if(v[i]==val) found = true;
        ofs << v[i] << " ";
    }
    ofs << "} " << found << "}\n";
}

//------------------------------------------------------------------------------

ifstream generate_random_tests(const string& ofname){
    ofstream ofs{ofname};
    if(!ofs) throw runtime_error("file stream not opened");
    seed_randint(43);
    int no_of_tests = randint(9,10);
    //cout << no_of_tests << "\nr";
    for(int i = 0; i <no_of_tests; ++i){
        string lab = "rand_test_";
        make_test(lab+to_string(i), randint(50), randint(500), 0, randint(50), ofs);
    }
    return ifstream{ofname};
}

//------------------------------------------------------------------------------

int test_all(ifstream& is){
    int errors = 0;
    for(Test test; is>>test; ){
        bool r = my_binary_search(test.sequence.begin(), test.sequence.end(), test.val);
        if(r != test.res) {
            errors++;
            cerr << "test failed, label: " << test.label << "\n";
        }
    }
    return errors;
}

//------------------------------------------------------------------------------

struct test_obj {
    int _i1;
    int _i2;

    test_obj(int i1, int i2)
        : _i1{i1}, _i2{i2}
    {
    }
};

bool compare_test_objs(const test_obj& to1, const test_obj& to2){
    return to1._i2 < to2._i2;
}

bool operator==(const test_obj& to1, const test_obj& to2){
    return to1._i1==to2._i1 && to1._i2==to2._i2;
}

//------------------------------------------------------------------------------

int main(){
    try {
        ifstream ifs{"tests.txt"};
        int number_errors = test_all(ifs);
        cout << "tests finished, number of errors: " << number_errors << "\n";

        ifstream ifs_rand = generate_random_tests("random_tests.txt");
        int number_errors_rand = test_all(ifs_rand);
        cout << "random tests finished, number of errors: " << number_errors_rand << "\n";

        //test binary_search with compare
        vector<test_obj> vec1;
        for(int i = 0; i < 10; ++i){
            vec1.push_back(test_obj(1, i));
        }
        test_obj to_find = test_obj(1, 5);
        bool test_res = my_binary_search(vec1.begin(), vec1.end(), to_find, compare_test_objs);
        cout << test_res << "\n";

        return 0;
    }
    catch(exception& e){
        cerr << e.what() << "\n";
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}
