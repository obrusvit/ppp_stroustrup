#include "../std_lib_facilities.h"

//ifstream& open_the_file( string message, string error_msg){
//    cout << message << "\n";
//    string file;
//    cin >> file;
//    ifstream ifs {file};
//    if(!ifs) error(error_msg);
//
//    return ifs;
//}

void put_to_file(ifstream& ifs, ofstream& ofs){
    for(char c; ifs >> c; ){
        cout << c << "\n";
        ofs << c;
    }
}

int main(){
    try{
        cout << "Please, enter 1st filename.\n";
        string file1;
        cin >> file1;

        cout << "Please, enter 2nd filename.\n";
        string file2;
        cin >> file2;
        
        ifstream ifs1 {file1};
        if(!ifs1) error("1st file does not exist\n");
        ifstream ifs2 {file2};
        if(!ifs2) error("2nd file does not exist\n");

        ofstream ofs {"file_merged"};
        if(!ofs) error("could not open file");

        put_to_file(ifs1, ofs);
        put_to_file(ifs2, ofs);

        return 0;
    }
    catch(exception& e){
        cerr << e.what();
        return 1;
    }
    catch(...){
        cerr << "something went wrong\n";
        return 2;
    }
}
