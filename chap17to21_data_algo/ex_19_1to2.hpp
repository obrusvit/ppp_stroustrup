#include <vector>
#include <stdexcept>
#include <iostream>
template<typename T>//requires Number<T>()
void f(std::vector<T>& v1, const std::vector<T>& v2){
    for(int i = 0; i < v1.size(); ++i){
        if(i == v2.size()) break;
        v1[i] += v2[i];
    }
}

template<typename T>//requires Element<T>()
void print_vec(const std::vector<T>& v){
    std::cout << "{";
    for(int i = 0; i < v.size()-1; ++i){
        std::cout << v[i] << ", ";
    }
    std::cout << v[v.size()-1] << "}" << "\n";
}

template<typename T, typename U> //requires Number<T>(), requires Number<U>()
T g(std::vector<T>& vt, const std::vector<U>& vu){
    if(vt.size() == 0 || vu.size() == 0) 
        throw std::runtime_error("empty std::vector passed to g()");
    T ret = vt[0]*vu[0];
    for(int i = 1; i < vt.size(); ++i){
        if(i == vu.size()) break;
        ret += vt[i]*vu[i];
    }
    return ret;
}
