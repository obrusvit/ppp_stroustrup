#include <iostream>
#include <stdexcept>

using namespace std;


int main(){
    try {
        //ex 7 - adding more memory is not implemented
        char* read_into = new char[1024];

        char c;
        int cntr = 0;
        while(cin >> c && c != '!'){
            read_into[cntr++] = c;
        }
        read_into[cntr] = '\0';

        cout << "Your input is: \n";
        cout << read_into << "\n";

        delete[] read_into;


        //ex 8 - the same using string
        string s;
        char sc;
        while(cin >> sc && sc != '!'){
            s += sc;
        }
        cout << "Your input in string: \n";
        cout << s << "\n";
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
