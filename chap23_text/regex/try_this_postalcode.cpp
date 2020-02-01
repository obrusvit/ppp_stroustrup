#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <regex>
using namespace std;


int main(){
    try {

        ifstream ifs{"postal_code_test_file.txt"};
        if (!ifs)
            cerr << "no file\n";
        
        // czech postal code
        regex pat{R"(\d{3}\s*\d{2})"};

        // look for just one per line
        cout << "regex_search:\n";
        //for (string s; getline(ifs, s); ){
        //    smatch results;
        //    if (regex_search(s, results, pat)){
        //        cout << "Found: "<< results[0] << ". On line: "<< s << "\n";
        //    }
        //}

        // look for all per line via iterator
        cout << "regex_iterator:\n";
        for (string s; getline(ifs, s); ){
            cout << "line: " << s << "\n";
            for (auto it = sregex_iterator(s.begin(), s.end(), pat); it != sregex_iterator(); ++it){
                cout << "\t" << it->str() << "\n";
            }
            cout << "\n";
        }

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

