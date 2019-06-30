#include "../std_lib_facilities.h"

void fill_the_rest(ofstream& ofs, vector<string>& v, unsigned long& index){
    for( ; index < v.size(); ++index){
        ofs << v[index];
    }
}

void merge_sorted_files(ifstream& ifs1, ifstream& ifs2, ofstream& ofs){
    string s1 = "";
    string s2 = "";

    while(true){
        if(s1 == "" && !(ifs1 >> s1)) break;
        if(s2 == "" && !(ifs2 >> s2)) break;
        if(s1 <= s2){
            ofs << s1;
            s1 = "";
        }
        else {
            ofs << s2;
            s2 = "";
        }
    }
    if(s1 != "") ofs << s1;
    if(s2 != "") ofs << s2;
    while(ifs1 >> s1) ofs << s1;
    while(ifs2 >> s2) ofs << s2;
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

        merge_sorted_files(ifs1, ifs2, ofs);

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
