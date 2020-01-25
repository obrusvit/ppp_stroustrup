
#include <iostream>
#include <stdexcept>
#include <string>


using namespace std;

//string cat_dot(const string& s1, const string& s2){
//    return s1+"."+s2;
//}
string cat_dot(const string& s1, const string& s2, const string& sep = "."){
    return s1+sep+s2;
}

int my_str_len(const char* s){
    int size = 0;
    while(*(s+size)) size++;
    return size;
}
char* cat_dot(const char* s1, const char* s2, char sep = '.'){
    int sz1 = my_str_len(s1);
    int sz2 = my_str_len(s2);


    int ret_size = sz1 + sz2 + 2;  //+ null + sep
    char* ret = new char[ret_size];

    int c = 0;
    for(int i = 0; i < sz1; ++i, ++c){
        ret[c] = s1[i];
    }
    ret[c] = sep; 
    ++c;
    for(int i = 0; i < sz2; ++i, ++c){
        ret[c] = s2[i];
    }
    ret[c] = '\0';
    return ret;
}

int main(){
    try {
        string s1 = "Niels";
        string s2 = "Bohr";
        string s12 = cat_dot(s1, s2);
        cout << s12 << "\n";

        const char* cs1 = "Niels";
        const char* cs2 = "Bohr";
        char* cs12 = cat_dot(cs1, cs2);
        cout << cs12 << "\n";

        delete[] cs12;
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
