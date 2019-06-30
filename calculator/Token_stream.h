#ifndef GUARD_TOKEN_STREAM
#define GUARD_TOKEN_STREAM

//------------------------------------------------------------------------------

#include <iostream>
#include "Token.h"

//------------------------------------------------------------------------------

class Token_stream{
    public:
        Token_stream();
        Token_stream(std::istream& is);
        Token get();
        void putback(Token t);
        void ignore(char ch); //ignore all characters up to and including ch
    private:
        std::istream& is;
        bool full;
        Token buff;
};

//------------------------------------------------------------------------------

bool is_underscore(char ch);

//------------------------------------------------------------------------------
#endif
