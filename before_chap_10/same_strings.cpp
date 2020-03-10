#include "std_lib_facilities.h"
int main(){
    string previous = "";
    string current;
    int count_words = 0;
    int count_same = 0;
    cout << "Enter words:\n";
    while(cin >> current){
        ++count_words;
        if(current == previous){
            ++count_same;
        }
        previous = current;
        cout << "Words: " << count_words << "\n";
        cout << "Same: " << count_same << "\n";
    }
    return 0;
}

