#include <iostream>
#include <stdexcept>

using namespace std;

char* strdup(const char* s){
    int size = 0;
    while(*(s+size)) ++size;
    char* ret = new char[size+1];
    for(int i = 0; i < size; ++i){
        *ret++ = *s++;
    }
    *ret = '\0';
    return ret-size;
}

char* findx(const char* s, const char* x){
    //return pointer to first occurence of x in s
    if(x == 0) return const_cast<char*>(s);
    if(s == 0) return nullptr;
    char fb = *x;
    int x_sz = 0;
    while(*(x+x_sz)) ++x_sz;
    while(*s++){
        if(*s == fb){ //found first char
            for(int i = 1; i < x_sz; ++i){ //check the rest of characters
                if(*(s+i) != *(x+i)) break;
                if(i == x_sz-1) return const_cast<char*>(s);
            }
        }
    }
    return nullptr;
}

int strcmp(const char* s1, const char* s2){
    // not bothering with upper/lower case
    // returns  0 if equal
    //          1 if s1 is lexicographically before s2 
    //         -1 if s1 is lexicographically after s2 
    if(s1 == 0 || s2 == 0) throw runtime_error("strcmp with nullptr");
    while(*(s1++) && *(s2++)){
        if(*s1 < *s2) return -1;
        if(*s1 > *s2) return 1;
    }
    if(*s1) return -1;
    else    return 1;
    return 0;
}

void print_str(const char* s){
    if(s == 0) return;
    while(*s) cout << *s++;
    if(*s == '\0') cout << "zero" << "\n";
    cout << "\n";
}

void test_ex1(){
    //ex 18.1
    const char* s1 = "Hello";
    char* s1_dup = strdup(s1);
    cout << s1_dup << "\n";
    delete[] s1_dup;
}

void test_ex2(){
    //ex 18.2
    const char* s2 = "Hello";
    const char* s3 = "llo";
    char* found = findx(s2, s3);
    cout << found << "\n";
}

void test_ex3(){
    //ex 18.3
    const char* s4 = "AB";
    const char* s5 = "A";
    const char* s6 = "";
    cout << strcmp(s4, s5) << "\n";
    cout << strcmp(s4, s6) << "\n";
    //cout << strcmp(s4, nullptr) << "\n"; //error
}

void test_ex4(){
    //ex 18.4
    // BAD Code on purpose
    char s7[] = {'H', 'i'};  // not null-terminated
    const char s8[3] = {'H', 'i', '!'};
    char* s9 = new char[2];
    s9[0] = 'H';
    s9[1] = 'i';

    char* s7_dup = strdup(s7); // works almost correctly but valgrind shouts error
    char* s9_dup = strdup(s9); // also sometimes wied chars, unpredictable 
    cout << s7_dup << "\n"; 
    cout << s9_dup << "\n";

    int cmp_res1 = strcmp(s7, s9); // unpredictable results
    cout << cmp_res1 << "\n";

    char s10[] = {'H', 'e', 'l', 'l', 'o'};
    char s11[] = {'l', 'l', 'o'};
    char* found = findx(s10, s11); // just no...
    cout << found << "\n";

    delete[] s7_dup;
    delete[] s9;
    delete[] s9_dup;
}

void test_chars(){
    cout << "------------\n";
    char chars[] = {'a', 'b', 'c'};
    cout << chars[0] << "\n";
    cout << chars[1] << "\n";
    cout << chars[2] << "\n";
    for(int i = 0; i < 4; ++i){
        cout << chars[i] << "\n";
    }
}


int main(){

    try {

        test_ex2();
        test_ex4();
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
