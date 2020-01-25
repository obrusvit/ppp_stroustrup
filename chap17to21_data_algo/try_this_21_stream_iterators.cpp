#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
/* #include <sstream> */
#include <iterator>
#include <fstream>
#include <set>

using namespace std;

void say_hello(){
    ostream_iterator<string> oo{cout};
    *oo = "Hello ";
    ++oo;
    *oo = "world\n";
}
void say_hello_to(string who){
    ostream_iterator<string> oo{cout};
    *oo = "Hello ";
    ++oo;
    *oo = who;
    ++oo;
    *oo = "\n";
}
void test_istream_iterator(){
    istream_iterator<string> iss{cin};
    string s1 = *iss;
    ++iss;
    string s2 = *iss;
    cout << s1 << " " << s2 << "\n";
}

void test_file_copy(){
    string from = "lorem_ipsum_500000_paragraphs.txt";
    string to = "lorem_test.txt";
    ifstream is{from};
    ofstream os{to};
    for(string line; getline(is, line); )
        os << line << "\n";
}
void test_stream_copy(){
    //much slower than previous function

    /* string from = "lorem_ipsum_500_paragraphs.txt"; */
    string from = "lorem_ipsum_500000_paragraphs.txt";
    string to = "lorem_test.txt";

    ifstream is{from};
    ofstream os{to};

    cout << "istream_iterator\n";
    istream_iterator<string> ii{is};
    istream_iterator<string> eos;
    ostream_iterator<string> oo{os, "\n"};

    cout << "vector\n";
    /* vector<string> b{ii, eos}; */
    set<string> b{istream_iterator<string>{is}, istream_iterator<string>{}};

    cout << "sort\n";
    /* sort(b.begin(), b.end()); */

    cout << "copy\n";
    unique_copy(b.begin(), b.end(), oo);
}

int main(){
    try {
        /* say_hello(); */
        /* say_hello_to("Daria"); */
        /* test_istream_iterator(); */
        /* test_file_copy(); */
        test_stream_copy();



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
