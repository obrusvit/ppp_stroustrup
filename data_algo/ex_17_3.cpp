#include <iostream>
#include <stdexcept>

using namespace std;

void to_lower(char* s){
    while(*s){
        if(*s >= 'A' && *s <= 'Z') *s += 32;
        s++;
    }
}

int main(){
    try {
        //string s = "HelLo!";
        //const char* cs = s.c_str();
        char cs[7] = {'H', 'e', 'l', 'L', 'o', '!', '\0'};
        char cs1[] = "HEy";
        cout <<  cs << "\n";
        cout <<  cs1 << "\n";
        to_lower(cs);
        to_lower(cs1);
        cout <<  cs << "\n";
        cout <<  cs1 << "\n";
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
