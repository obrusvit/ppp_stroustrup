#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

char* findx(const char* s, const char* x){
    if(s==0 || x==0) return nullptr;
    for(int i = 0; s[i]; ++i){
        for(int j = 0; x[j]; ++j){
            if(s[i+j] != x[j]) break;
            if(x[j+1] == '\0') {
                //found! copy the result
                char* ret = new char[j+2];
                for(int k = 0; k < j+1; ++k){
                    ret[k] = s[i+k];
                }
                ret[j+1] = '\0';
                return ret;
            }
        }
    }
    return nullptr;
}

void test(const string& ss, const string& ff = "find me"){
    string s = ss;
    string to_find = ff;
    cout << "test: should find: " << to_find << ", in: " << s << "\n";
    char* par1 = &s[0];
    char* par2 = &to_find[0];
    char* found = findx(par1, par2);
    
    if(found){
        cout << "found: " <<  found << "\n";
        delete[] found;
    }
    cout << "\n";
}

int main(){
    try {
        string s1 = "Hello world.";
        string f1 = "llo";
        test(&s1[0], &f1[0]);

        //some more testing
        string s;
        while(getline(cin, s) && s != "quit"){
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
