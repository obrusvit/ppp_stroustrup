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

        regex pat_date_1{R"((\d{1}|\d{2})(/)(\d{1}|\d{2})(/)(\d{4}))"}; // DD/MM/YYY
        regex pat_date_2{R"((\d{1}|\d{2})(\.)(\d{1}|\d{2})(\.)(\d{4}))"}; // DD.MM.YYY

        int i = 1;
        for (string s; getline(ifs, s); ++i){
            sregex_iterator begin_1{s.begin(), s.end(), pat_date_1};
            sregex_iterator begin_2{s.begin(), s.end(), pat_date_2};
            sregex_iterator end{}; //empty regex

            for (sregex_iterator it = begin_1; it != end; ++it){
                cout << "Line " << i << ": "<< it->str() << "\n";
                // NOTE: e.g. (*it)[1] this matches first group

                string fmt_s = it->format(
                    "$`"    // $` means characters before the match
                    "[$&]"  // $& means the matched characters
                    "$'"    // $' means characters following the match
                    );
                cout << "Whole line with bracketed date: "<< fmt_s << '\n';
                cout << "---" << "\n";
            }

            for (sregex_iterator it = begin_2; it != end; ++it){
                cout << "Line " << i << ": "<< it->str() << "\n";
            }
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

