#include <iostream>
#include <stdexcept>
#include <vector>
#include <regex>
using namespace std;


int main(){
    try {
        string s1 = "hello\nnewline";
        string s2 = "hello just space";
        cout << s1 << "\n";
        cout << s2 << "\n\n";

        regex pat{R"((\w+)(.)([\w ]+))"};
        smatch res;
        if(regex_match(s1, res, pat)){
            cout << "pat matches newline\n";
        }
        if(regex_match(s2, res, pat)){
            cout << "pat matches space\n";
        }

        // Conclusion: 
        //  . does not match newline
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

