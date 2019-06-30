#include <iostream>

//------------------------------------------------------------------------------

#include "Token_stream.h"
#include "std_lib_facilities.h"
#include "constants.h"

//------------------------------------------------------------------------------

bool is_underscore(char ch){
    return ch == '_';
}

//------------------------------------------------------------------------------

Token_stream::Token_stream()
    :is{cin}, full(false), buff(0)
{
}

//------------------------------------------------------------------------------

Token_stream::Token_stream(istream& is)
    :is{is}, full(false), buff(0)
{
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t){
    if(full) error("full buffer of Token_stream");
    buff = t;
    full = true;
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c){
// Discards all chars until and including 'c'
    if(full && c == buff.type){
        full = false;
        return;
    }
    full = false;
    char ch;
    while(is >> ch){
        if(ch == c){
            return; 
        }
    }
}

//------------------------------------------------------------------------------

Token Token_stream::get(){
    if(full){   //use buffer if we already have some Token ready
        full = false;
        return buff;
    }
    char ch;
    is >> ch;  //note that >> skips whitespace (space, newline, tab, etc.)
    switch(ch){
        case quit:
        case print:
        case ',':
        case '=':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
        case '{':
        case '}':
        case '!':
            return Token{ch};
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            is.putback(ch);
            double d;
            is >> d;
            return Token{number, d};
        }
        default:
            // handle variable names and keywords (e.g. "let", "sqrt", etc.)
            if(isalpha(ch)){
                string s;
                s+=ch;
                while(is.get(ch) && (isalpha(ch) || isdigit(ch) || is_underscore(ch)))
                    s+=ch;
                is.putback(ch);
                if(s == declcommand)
                    return Token{let};
                if(s == sqrtcommand)
                    return Token{sqrt_c};
                if(s == powcommand)
                    return Token{pow_c};
                return Token{name, s};
            }
            error("Bad token");
    }
}
