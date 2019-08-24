/**
 *
 * Chap 11/Ex 13
 */
#include "../std_lib_facilities.h"

int main(){
    try {
        fstream fs{"test_reverse"};
        if(!fs) error("could not open file");

        vector<string> v;
        for(string s; fs >> s; ){
            v.push_back(s);
        }
        ostringstream oss;
        for(int i = v.size()-1; i >= 0; --i){
            oss << v[i] << " ";
        }

        cout << oss.str() << "\n";
        fs.clear();
        fs << oss.str().c_str();

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
