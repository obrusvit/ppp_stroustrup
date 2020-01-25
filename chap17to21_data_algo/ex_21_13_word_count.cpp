#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

void process_word(string& s){
    transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c){return tolower(c);}
            );

    if(s[s.size()-1] == '.'){
        s.pop_back();
    }
}

template<typename M>
void print_out_map(M m){
    for(const auto& el : m){
        cout << el.first << "  -->  " << el.second << "\n";
    }
}

int main(){
    try {
        map<string, int> word_count;
        ifstream ifs{"lorem_ipsum_500_paragraphs.txt"};
        if(ifs){
            for(string s; ifs >> s; ){
                process_word(s);
                ++word_count[s];
            }

        }
        print_out_map(word_count);

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
