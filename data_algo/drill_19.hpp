#ifndef DRILL_19_HPP
#define DRILL_19_HPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>

template<typename T>
struct S{
    S() : val{T()}
    {
    }

    S(T t) : val{t}
    {
    }

    T& get();
    const T& get() const;
    
    void set(T t);

    void operator=(const T& t);


    private:
    T val;
};

//------------------------------------------------------------------------------

template<typename T>
T& S<T>::get(){
    return val;
}
template<typename T>
const T& S<T>::get() const{
    return val;
}

template<typename T>
void S<T>::set(T t){
    val = t;
}

template<typename T>
void S<T>::operator=(const T& t){
    val = t;
}

template<typename T>
void read_val(T& v){
    std::cin >> v;
}

//------------------------------------------------------------------------------

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vt){
     
    os << "{ ";
    if(!vt.empty()){
        std::for_each(vt.begin(), vt.end()-1, [&os](T t){os << t << ", ";});
    }
    os << vt.back() << " }\n";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vt){
    char c;
    is >> c;
    std::vector<T> vt_temp;
    if(c != '{') throw std::runtime_error("'{' expected");
    for(T t; is >> t >> c; ){
        vt_temp.push_back(t);
        if(c != ','){
            is.unget();
            is.clear(std::ios_base::failbit);
            break;
        }
    }
    if(is.bad()) throw std::runtime_error("istream bad");
    if(is.fail()){
        is.clear();
        is >> c;
        if(c != '}') {
            is.unget();
            is.clear(std::ios_base::failbit);
            throw std::runtime_error("'}' expected");
        }
    }
    vt = vt_temp;
    return is;
}

//------------------------------------------------------------------------------

#endif
