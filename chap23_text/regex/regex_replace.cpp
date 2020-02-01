#include <iostream>
#include <stdexcept>
#include <vector>
#include <regex>
using namespace std;

void test_geeks(){
    string subject{"its all about geeksforgeeks"};

    string result1, result2, result3, result4; 
    string result5; 
  
    // regex object 
    regex re{R"((geeks)(.*))"};
  
    // $2 contains, 2nd capturing group which is (.*) means 
    // string after "geeks" which is "forgeeks". hence 
    // the match(geeksforgeeks) will be replaced by "forgeeks". 
    // so the result1 = "its all about forgeeks" 
    result1 = regex_replace(subject, re, "$2"); 
  
    // similarly $1 contains, 1 st capturing group which is 
    // "geeks" so the match(geeksforgeeks) will be replaced 
    // by "geeks".so the result2 = "its all about geeks". 
    result2 = regex_replace(subject, re, "$1"); 
  
    // $0 contains the whole match 
    // so result3 will remain same. 
    result3 = regex_replace(subject, re, "$0"); 
  
    // $0 and $& contains the whole match 
    // so result3 will remain same 
    result4 = regex_replace(subject, re, "$&"); 
  
    // Here number of capturing group 
    // is 2 so anything above 2 
    // will be replaced by nothing. 
    result5 = regex_replace(subject, re, "$6"); 
  
    cout << result1 << "\n" << result2 << "\n"; 
    cout << result3 << "\n" << result4 << "\n" 
         << result5 << "\n"; 

}

void test_dates(){
    string d1{"17/07/1995"};
    string d1_fmt;

    regex pat_date_1{R"((\d{1}|\d{2})(/)(\d{1}|\d{2})(/)(\d{4})([\s\.,?!:]{0,1}))"}; // DD/MM/YYY ended with punctuation
    cout << regex_match(d1, pat_date_1) << "\n";

    d1_fmt = regex_replace(d1, pat_date_1, "$1.$3.$5");
    cout << d1_fmt << "\n";

}

int main(){
    try {
        test_geeks();
        test_dates();
  

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

