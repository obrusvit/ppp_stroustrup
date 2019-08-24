#include"../std_lib_facilities.h"

struct Reading{
    int hour;
    double temperature;
};

void test_input(){
    ifstream ist{"test_input.txt"};
    if(!ist) error("error opening file");
    vector<Reading> temps;
    int hour;
    double temperature;
    while(ist >> hour >> temperature){
        temps.push_back(Reading{hour,temperature});
    }
    for(Reading& r : temps){
        cout << r.hour << " " << r.temperature << "\n";
    }
}

void test_istream_states(){
    int i = 0;
    for(int k = 0; k<10; ++k){
        cin >> i;
        if(!cin){ //input operation failed
            if(cin.bad()) error("cin is bad"); //stream corrupted
            if(cin.eof()){
                //no more input, this is usually how we want to end
                cout << "no more input\n";
            }
            if(cin.fail()){
                //stream encountered something unexped
                cout << "cin fail'\n";
                cin.clear(); //make ready for other input
                //somehow recover...
            }
        }
        cout << i << "\n";
        cout << "test_istream_states done\n";
    }
}

void fill_vector(istream& ist, vector<int>& v, char terminator){
    for(int i; ist >> i; ) v.push_back(i);
    if(ist.eof()) return; // everything all right

    if(ist.bad()) error("ist is bad");
    if(ist.fail()){
        ist.clear(); //clear the stream state so we can look for terminator
        char c;
        ist >> c;
        if(c != terminator){ // unexpected character
            ist.unget(); //put it back
                        // unget is the shorter version of putback(c);
            ist.clear(ios_base::failbit);
        }
    }
}

void fill_vector_2(istream& ist, vector<int>& v, char terminator){
    // the following line will make ist to throw exception
    // automatically when in bad() state
    // throws ios_base::failure
    ist.exceptions(ist.exceptions() | ios_base::badbit);
    for(int i; ist >> i; ) v.push_back(i);
    if(ist.eof()) return; // everything all right

    //not good(), not bad(), not eof(), so it must be fail()
    ist.clear(); //clear the stream state so we can look for terminator
    char c;
    ist >> c;
    if(c != terminator){ // unexpected character
        ist.unget(); //put it back
                    // unget is the shorter version of putback(c);
        ist.clear(ios_base::failbit); // set back to fail() state
    }
}

//------------------------------------------------------------------------------
// Some better but not that good tries

void repeated_input(){
    cout << "enter integer [1,10] inclusive:\n";
    int n = 0;
    while(cin>>n){
        if(1<=n && n<=10) break;
        cout << "Sorry, must be in range [1,10] inclusive\n";
    }
    cout << "input is " << n << "\n";
}


void repeated_input_2(){
    cout << "enter integer [1,10] inclusive:\n";
    int n = 0;
    while(true){
        cin >> n;
        if(cin){
            
            if(1<=n && n<=10) break;
            cout << "Sorry, must be in range [1,10] inclusive\n";
        }
        else if(cin.fail()){
            cin.clear();    //set the state back to good()
                            // we want to look at the characters
            cout << "That was not an integer\n";
            for(char ch; cin>>ch && !isdigit(ch); ); //throw away not digits

            if(!cin) error("no input"); //give up
            
            cin.unget(); // put the digit back so we can read it
        }
        else {
            error("no input");
        }
    }
    cout << "input is " << n << "\n";
}

void skip_to_int();
void repeated_input_3(){
    cout << "enter integer [1,10] inclusive:\n";
    int n = 0;
    while(true){
        cin >> n;
        if(cin){
            
            if(1<=n && n<=10) break;
            cout << "Sorry, must be in range [1,10] inclusive\n";
        }
        else {
            cout << "Sorry, that was not integer\n";
            skip_to_int();
        }
    }
    cout << "input is " << n << "\n";
}
//------------------------------------------------------------------------------
//good methods for int

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
    error("no input"); //eof() or bad(), give up
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

int main(){
    //test_istream_states();

    //vector<int> vec;
    //char terminator = '*';
    //fill_vector(cin, vec, terminator);
    
    //repeated_input_3();
    int a = get_int("Enter integer", "Not an integer, try again");
    cout << "input is: " << a << "\n";

    int b = get_int("Enter integer", "Not an inteter, or not in range, try again", 0, 10);
    cout << "input is: " << b << "\n";

    double f = 1234567.89;
    cout << defaultfloat << f << "\n";
    cout << fixed << f << "\n";
    cout << fixed << setprecision(4) << f << "\n";
    cout << scientific << f << "\n";
    cout << setprecision(12) << scientific << f << "\n";

    return 0;
}
