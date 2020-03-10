#include <iostream>
#include <stdexcept>
#include <vector>

#include <functional>

using namespace std;

reference_wrapper<const int> get_data(){
    const int i = 3;
    return {i};
}

template<typename Value, typename Handler>
int* caller(Value&& v, Handler&& handler){
    return handler(std::forward<Value>(v));
}

void dangle_1(){
    auto d = get_data();
    cout << d << "\n";
}

void dangle_2(){
    auto handler = [](auto&& value){ return &value; };
    int value = 17;
    int* result = caller(value, handler);
    cout << *result << "\n";

    int* result_bad = caller(42, handler);
    cout << *result_bad << "\n";

    int i = *result + *result_bad;
    cout << i << "\n";

    /* cout << *handler(43) << "\n"; */
}

int main(){
    try {

        dangle_2();

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

