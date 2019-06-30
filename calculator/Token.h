#ifndef GUARD_TOKEN
#define GUARD_TOKEN

//------------------------------------------------------------------------------

#include<string>

//------------------------------------------------------------------------------

class Token{
    public:
        char type;
        double value;
        std::string name;

        Token(){};
        Token(char ch)
            :type(ch), value(0), name(""){ };
        Token(char ch, double v)
            :type(ch), value(v), name("") { };
        Token(char ch, std::string s)
            :type(ch), value(0), name(s) { };
};

//------------------------------------------------------------------------------
#endif
