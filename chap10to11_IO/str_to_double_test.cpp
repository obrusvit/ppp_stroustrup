#include <iostream>
#include <stdexcept>
#include <string>
#include "str_to_double.h"

int main(){
try{
    std::string s1 = "2.4";
    double d1 = str_to_double(s1);
    std::cout << d1 << "\n";
    
}
catch(std::runtime_error e){
    std::cerr << e.what() << "\n";
    return 1;
}
catch(...){
    std::cerr << "something went wrong\n";
    return 2;
}
}
