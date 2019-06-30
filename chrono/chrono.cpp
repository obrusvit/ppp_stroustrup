#include "chrono.h"
//#include "../std_lib_facilities.h"

namespace Chrono{

//------------------------------------------------------------------------------
// Operators overloading
    
std::ostream& operator<<(std::ostream& os, const Month m){
    return os << static_cast<int>(m); //just write underlying integer
}
std::ostream& operator<<(std::ostream& os, const Date& d){
    return os << d.year() << " " << d.month() << " " << d.day();
}
std::istream& operator>>(std::istream& is, Date& date){
    int d, m, y;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')'){
        //format error
        is.clear(std::ios_base::failbit);
        return is;
    }
    date = Date{y, Month(m), d};
    return is;
}

bool operator==(const Date& d1, const Date& d2){
    return d1.day() == d2.day()
        && d1.month() == d2.month()
        && d1.year() == d2.year();
}
bool operator!=(const Date& d1, const Date& d2){
    return !(d1==d2);
}


//------------------------------------------------------------------------------
// Date members

Date::Date(int yy, Month mm, int dd)
    :y{yy}, m{mm}, d{dd}
{
    if(!is_date(yy, mm, dd)) throw Invalid();
}

const Date& default_date(){
    const static Date& dd{1970, Month::jan, 1};
    return dd;
}

Date::Date()
    : y{default_date().year()},
    m{default_date().month()}, 
    d{default_date().day()}
{
}

Date::Date(int yy)
    : y{yy},
    m{default_date().month()}, 
    d{default_date().day()}
{
}

void Date::add_year(int n){
    if(m == Month::feb && d==29 && !is_leapyear(y+n)){
        // hadle corner case: leap year
        d = 1;
        m = Month::mar;
    }
    y+=n;
}
void Date::add_month(int n){
}
void Date::add_day(int n){
}

bool is_date(int y, Month m, int d){
    if(d<=0) return false;
    if(m<Month::jan || m>Month::dec) return false;
    int days_in_month = 31;
    switch(m){
        case(Month::feb):
            days_in_month = is_leapyear(y) ? 29 : 28;
            break;
        case(Month::may):
        case(Month::jun):
        case(Month::sep):
        case(Month::nov):
            days_in_month = 30;
            break;
    }
    if(days_in_month < d) return false;
    
    return true;
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Helper methods

bool is_leapyear(int year){
    if(year%400 == 0){
        return true;
    }
    if(year%100 == 0){
        return false;
    }
    if(year%4 == 0){
        return true;
    }
    return false;
}

//Day day_of_week(const Date& d){//day of week of d
//}
//Date next_Sunday(const Date d){//next sunday after d
//}
//Date next_weekday(const Date& d){//next weekday after d
//}

}; // Chrono
