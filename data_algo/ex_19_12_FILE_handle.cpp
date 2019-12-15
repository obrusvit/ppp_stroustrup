#include <iostream>
#include <string>
#include <stdio.h>
#include <stdexcept>

class FILE_handle{
    public:
        FILE_handle(std::string file_name, std::string mode)
            : file{fopen(file_name.c_str(), mode.c_str())}
        {
            std::cout << "C style FILE opened, name: " << file_name << ", mode: " << mode << "\n";
        }

        ~FILE_handle(){
            fclose(file);
            std::cout << "C style FILE closed.\n";
        }

        FILE* get_file() const{
            return file;
        }

    private:
        FILE* file;

};



using namespace std;

int main(){
    try {
        FILE_handle fh("ex_19_12_FILE_handle.cpp", "r");
        char buff[200];
        fgets(buff, 100, fh.get_file());
        cout << buff << "\n";
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
