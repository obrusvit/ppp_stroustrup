#include "str_to_double.h"
#include<iostream>
#include <sstream>
#include <stdexcept>

double str_to_double(std::string s){
    std::istringstream iss {s};
    double d;
    iss >> d;
    if(!iss) throw std::runtime_error("conversion failes");
    return d;
}
