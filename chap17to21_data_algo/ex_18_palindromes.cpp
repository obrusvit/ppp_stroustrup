#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

using namespace std;

bool is_palindrome(const string& s){
    auto first = s.begin();
    auto last = s.end() -1;
    while(first < last){
        if(*first != *last) return false;
        ++first;
        --last;
    }
    return true;
}

bool is_palindrome(const char* s, int n){
    //char* s with length n
    int first = 0;
    int last = n-1;
    while(first < last){
        if(s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;
}

bool is_palindrome(const char* first, const char* last){
    while(first < last){
        if(*first != *last) return false;
        ++first;
        --last;
    }
    return true;
}

//------------------------------------------------------------------------------

void test_string_version(){
    string s1;
    while(cin >> s1){
        if(s1 == "quit") break;
        cout << s1 << " is ";
        if(!is_palindrome(s1)) cout << "not ";
        cout << "a palindrome.\n";
    }
}
istream& read_word(istream& is, char* buffer, int max){
    //read at most max-1 chars in next >> into buffer
    is.width(max); 
    is >> buffer;
    return is;
}
void test_array_version(){
    constexpr int  max_len = 128;
    char s1[max_len];
    while(read_word(cin, s1, max_len)){
        if(strcmp("quit", s1)==0) break;
        cout << s1 << " is ";
        if(!is_palindrome(s1, strlen(s1))) cout << "not ";
        cout << "a palindrome.\n";
    }
}

void test_ptr_version(){
    constexpr int  max_len = 128;
    char s1[max_len];
    while(read_word(cin, s1, max_len)){
        if(strcmp("quit", s1)==0) break;
        cout << s1 << " is ";
        if(!is_palindrome(&s1[0], &s1[strlen(s1)-1])) cout << "not ";
        cout << "a palindrome.\n";
    }

    string s2;
    while(cin >> s2){
        if(s2 == "quit") break;
        cout << s2 << " is ";
        if(!is_palindrome(&s2[0], &s2[s2.size()-1])) cout << "not ";
        cout << "a palindrome.\n";
    }
}

//------------------------------------------------------------------------------

int main(){
    try {
        //test_string_version();
        //test_array_version();
        test_ptr_version();
        
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
