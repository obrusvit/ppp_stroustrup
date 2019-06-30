#include "../std_lib_facilities.h"

double str_to_double(string& s){
    istringstream is {s}; // make a stream so we can read from s

    double d;
    is >> d;
    if(!is) error("not a double");
    return d;
}

int main(){
    try {
        // output formatting
        cout << 12 << "\t" << hex << 12 << "\n"; //c
        cout << dec << 0xc << "\n";
        cout << hex << showbase << 12 << "\n"; //0xc
        cout << dec << scientific << 120.000 << "\n";
        cout << setw(20) << "hello.\n"; // total space, hold only for one output
        // input format
        int a;
        cin >> hex >> a; //c
        if(!cin) error("not a hex number\n");
        cout <<  dec << a << "\n"; //12
        
        // move in file
        fstream fs {"file_merged"};
        if(!fs) error("could not open file\n");
        fs.exceptions(fs.exceptions() | ios_base::badbit); // make throw on bad() so we don't have to
        for(char ch; fs >> ch; ){
            cout << ch << " ";
        }
        
        cout << "\n";
        fs.clear(); // clear is necessary because there is eof() after loop
        fs.seekg(3); // set the position for reading
        char c;
        fs >> c;
        cout << c << "\n";

        fs.seekp(0); // set the position for writing
        fs << "z"; // change whatever is the first char by "z"
        
        // string stream
        string s = "2.45";
        cout << str_to_double(s) << "\n";

        int i = 2;
        //string s1 = "log_file" + i + ".log"; // not working
        ostringstream oss;
        oss << "log_file" << i << ".log";
        cout << oss.str() << "\n";


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
