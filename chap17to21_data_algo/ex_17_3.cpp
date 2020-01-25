#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void to_lower(char* s){
    for( ; *s; s++){
        if(*s >= 'A' && *s <= 'Z') *s += 'a'-'A';
    }
}

void test(const string& ss){

    string s = ss;
    cout << s << "\n";
    char* p = &s[0];
    to_lower(p);
    cout << p << "\n";

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

        string s;
        for( ; cin >> s && s!="quit";){
            test(s);
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
