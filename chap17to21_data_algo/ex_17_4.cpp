#include <iostream>
#include <stdexcept>

using namespace std;


char* strdup(const char* s){
    if(s == 0) return 0;
    int c = 0;
    while(s[c]) c++;
    char* ret = new char[c];
    for(int i = 0; i < c; ++i){
        ret[i] = s[i];
    }
    ret[c+1] = '\0';
    return ret;
}

int main(){
    try {
        char cstr1[] = "Hello";
        char* cstr1_cp = strdup(cstr1);

        cout << cstr1_cp << "\n";

        delete[] cstr1_cp;
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
