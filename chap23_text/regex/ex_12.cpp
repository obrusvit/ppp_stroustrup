/**
 * Exercise 6 - find date in the format DD/MM/YYYY in the text. Add other date formats.
 * Exercise 12 - replace dates found in Ex. 6 with a different format.
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include <regex>
#include <fstream>
#include <string>

using namespace std;


int main(){
    try {
        ifstream ifs{"ex_6_test_file.txt"};
        if (!ifs){
            cerr << "no input file\n";
        }

        ofstream ofs{"ex_12_test_file.txt"};
        if (!ofs){
            cerr << "no output file\n";
        }

        regex pat_date_1{R"((\d{1}|\d{2})(/)(\d{1}|\d{2})(/)(\d{4})([\s\.,?!:]{0,1}))"}; // DD/MM/YYY ended with punctuation


        // go through file and replace DD/MM/YYYY date format with DD.MM.YYYY
        for (string s; getline(ifs, s); ){
            s = regex_replace(s, pat_date_1, "$1.$3.$5$6"); // just place the groups and put dot instead of $2 and $4
            ofs << s;
            ofs << "\n";
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

