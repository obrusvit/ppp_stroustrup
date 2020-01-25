#include <iostream>
#include <stdexcept>
#include <vector>
#include "drill_19.hpp"

using namespace std;


int main(){
    try {
        S<int> s1(4);
        S<char> s2('c');
        S<double> s3(4.3);
        S<vector<int>> s4({1, 2, 3});
        cout << s1.get() << "\n";
        cout << s2.get() << "\n";
        cout << s3.get() << "\n";
        for(auto& i : s4.get()){
            cout << i << " ";
        } cout << "\n";


        s1 = 5;
        s2 = 'e';
        s3.set(5.30);
        
        cout << s1.get() << "\n";
        cout << s2.get() << "\n";
        cout << s3.get() << "\n";

        //test read_val
        //use read_val to read to variables
        cout << "test read_val\n";
        //read_val(s1.get()); 
        //read_val(s2.get()); 
        //read_val(s3.get()); 
        //cout << s1.get() << "\n";
        //cout << s2.get() << "\n";
        //cout << s3.get()<< "\n";

        //bonus
        cout << "operators << >>\n";
        cout << s4.get();
        cin >> s4.get();
        cout << s4.get();


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
