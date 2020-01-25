#include"get_int.h"
using std::cin;
using std::cout;
using std::string;

void skip_to_int(){
    if(cin.fail()){
        cin.clear();
        for(char ch; cin>>ch; ){
           if(isdigit(ch) || ch =='-'){
               cin.unget();
               return;
           }
        }
    }
    throw std::runtime_error("no input");//eof() or bad(), give up
}

int get_int(){
    int n;
    while(true){
        cin >> n;
        if(cin) return n;
        skip_to_int();
    }
}

int get_int(const string& greeting, const string& sorry){
    cout << greeting << "\n";
    int n;
    while(true){
        cin >> n;
        if(cin) return n;
        cout << sorry << "\n";
        skip_to_int();
    }
}

int get_int(const string& greeting, const string& sorry,int range_low, int range_high){
    cout << greeting << "; [" << range_low << ", " << range_high << "]" << "\n";
    int n;
    while(true){
        n = get_int();
        if(range_low <= n && n <= range_high) return n;
        cout << sorry << "\n";
    }
}
