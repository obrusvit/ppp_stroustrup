#ifndef GUARD_CONVERSIONS_TEST_HPP_
#define GUARD_CONVERSIONS_TEST_HPP_ 

#include <string>
#include <stdexcept>
#include <sstream>

template<typename T>
std::string to_string(T t){
    std::ostringstream os;
    os << t;
    return os.str();
}

struct bad_conversion_from_string : std::bad_cast {
    const char* what() const  noexcept override {
        return "bad cast from string";
    }
};

template<typename T>
T from_string(std::string s){
    std::istringstream is{s};
    T t;
    if(!(is >> t))
        throw bad_conversion_from_string{};
    return t;
}

template<typename Source, typename Target>
Target to(Source s){
    std::stringstream interpreter;
    Target ret;
    if(!(interpreter << s)
        || !(interpreter >> ret)
        || !(interpreter >> std::ws).eof()) // something left in stream? ..but allow whitespaces
    {
        throw std::bad_cast{};
    }
    return ret;
}

#endif

