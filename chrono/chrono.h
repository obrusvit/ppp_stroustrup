//#include"../std_lib_facilities.h"
#include<iostream>

namespace Chrono {
    
enum class Month{
    jan=1, feb, mar, may, apr, jun, jul, aug, sep, oct, nov, dec
};
enum class Day{
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};


class Date{

    public:
        class Invalid{}; //to throw

        Date(); //default consturctor
        Date(int yy);
        Date(int yy, Month mm, int dd);

        // non modifying members
        int year() const { return y;}
        Month month() const { return m;}
        int day() const { return d;}

        // modifying members
        void add_day(int d);
        void add_month(int m);
        void add_year(int y);

    private:
        int y;
        Month m;
        int d;
};

bool is_date(int y, Month m, int d);
bool is_leapyear(int y);
bool operator==(const Date& d1, const Date& d2);
bool operator!=(const Date& d1, const Date& d2);

std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& dd);

Day day_of_week(const Date& d); //day of week of d
Date next_Sunday(const Date d); //next sunday after d
Date next_weekday(const Date& d); //next weekday after d


} // Chrono
