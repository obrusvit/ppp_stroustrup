#include "chrono.h"
int main(){
    Chrono::Date d1{2019, Chrono::Month::jun, 8};
    std::cout << d1 << "\n";
    return 0;
}
