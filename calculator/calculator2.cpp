/*
 * Calculator 2
 * TODO write nice description.
 * TODO write grammar
 */
#include <cmath>

//------------------------------------------------------------------------------

#include "std_lib_facilities.h"
#include "Token.h"
#include "Token_stream.h"
#include "constants.h"


//------------------------------------------------------------------------------
// Few util functions


int factorial(int n){
    if(n == 0 || n == 1)
        return 1;
    else 
        return n*factorial(n-1);
}

//------------------------------------------------------------------------------

class Variable{
    public:
        string name;
        double value;
};

//------------------------------------------------------------------------------

vector<Variable> var_table;

//------------------------------------------------------------------------------

double get_var(string name){
    for(const Variable& var : var_table){
        if(var.name == name){
            return var.value;
        }
    }
    error("get - unknown variable, name: ", name);
}

//------------------------------------------------------------------------------

void set_var(string name, double val){
    for(Variable& var : var_table){
        if(var.name == name){
            var.value = val;
            return;
        }
    }
    error("set- unknown variable, name: ", name);

}

//------------------------------------------------------------------------------

double expression(Token_stream&); //forward declaration

//------------------------------------------------------------------------------

/**
 * Returns factorial of atom value if the next token is '!'.
 * Returns the same atom value if the next token is not '!' and puts token back.
 */
double handle_factorial(Token_stream& ts, double d){
        Token t = ts.get(); //handle factorial
        if(t.type == '!'){
            return factorial(int(d));
        }
        ts.putback(t);
        return d;
}

//------------------------------------------------------------------------------

double atom(Token_stream& ts){
    Token t = ts.get();
    switch(t.type){
        case('('): //handle "(<expression>)" rule
            {
                double d = expression(ts);
                t = ts.get();
                if(t.type != ')') error("')' expected");
                d = handle_factorial(ts, d);
                return d;

            }
        case('{'):
            {
                double d = expression(ts);
                t = ts.get();
                if(t.type != '}') error("'}' expected");
                d = handle_factorial(ts, d);
                return d;
            }
        case('+'):
            return atom(ts);
        case('-'):
            return -atom(ts);
        case(number):
            {
                double d =  t.value;
                d = handle_factorial(ts, d);
                return d;
            }
        case(name):
            {
                string name = t.name;
                t = ts.get();
                if(t.type == '='){
                    double d = expression(ts);
                    set_var(name, d);
                    return d;
                } else {
                    ts.putback(t);
                    return get_var(name);
                }
            }
        case(sqrt_c):
            {
                t = ts.get();
                if(t.type != '(') error("'(' expected after sqrt'");
                double d = expression(ts);
                t = ts.get();
                if(t.type != ')') error("')' exptected");
                return sqrt(d);
            }
        case(pow_c):
            {
                t = ts.get();
                if(t.type != '(') error("'(' expected after pow'");
                double d1 = expression(ts);
                t = ts.get();
                if(t.type != ',') error("pow takes 2 arguments separated with ','");
                double d2 = expression(ts);
                t = ts.get();
                if(t.type != ')') error("')' exptected");
                return pow(d1,d2);
            }
        default:
            error("Primary expected");
    }

}

//------------------------------------------------------------------------------

double term(Token_stream& ts){
    double left = atom(ts);
    Token t = ts.get();
    while(true){
        switch(t.type){
            case('*'):
                left *= term(ts);
                t = ts.get();
                break;
            case('/'):
            {
                double denum  = atom(ts);
                if(denum==0) error("/, division by zero");
                left /= denum;
                t = ts.get();
                break;
            }
            case('%'):
            {
                
                double denum = atom(ts);
                if(denum == 0) error("%, division by zero");
                left = fmod(left, denum);
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }

    }

}

//------------------------------------------------------------------------------

double expression(Token_stream& ts){
    double left = term(ts);
    Token t = ts.get();
    while(true){
        switch(t.type){
            case('+'):
                left += term(ts);
                t = ts.get();
                break;
            case('-'):
                left -= term(ts);
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }

    }
}

//------------------------------------------------------------------------------

bool is_declared(string s){
    for(const Variable& var : var_table){
        if(var.name == s)
            return true;
    }
    return false;
}

//------------------------------------------------------------------------------

double define_var(string s, double d){
    if(is_declared(s)) error("define_var - name used");
    var_table.push_back(Variable{s, d});
    return d;
}

//------------------------------------------------------------------------------

double declaration(Token_stream& ts){
    // assumption: we have seen let
    // now we expect a name
    Token t = ts.get();
    if(t.type != name) error("declaration - variable name expected");
    string s = t.name;

    // now expect '='
    t = ts.get();
    if(t.type != '=') error("declaration - '=' expected");

    double d = expression(ts);
    return define_var(s, d);
}

//------------------------------------------------------------------------------

double statement(Token_stream& ts){
    Token t = ts.get();
    switch(t.type){
        case let:
            return declaration(ts);
        default:
            ts.putback(t);
            return expression(ts);
    }
}

//------------------------------------------------------------------------------

void clean_up_mess(Token_stream& ts){
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate(Token_stream& ts){
    double val = 0.0;
    while(cin){
        try{
            cout << prompt << " ";
            Token t = ts.get();
            while(t.type == print){
                t = ts.get(); //eat 'print' chars
            }
            if(t.type == quit) return;
            ts.putback(t);
            val = statement(ts);
            cout << result << val << "\n";
        }
        catch(exception& e){
            cerr << e.what() << "\n";
            clean_up_mess(ts);
        }
            
    }
}

//------------------------------------------------------------------------------

int main(){
    cout << "Welcome to DARIA Computing.\n";
    cout << "Enter expression.\n";

    try {
        define_var("pi", 3.1415926535);
        define_var("e", 2.7182818284);
        Token_stream ts;
        calculate(ts);
        return 0;
    } catch(exception&  e){
        cerr << e.what() << "\n";
        return 1;
    } catch(...){
        cerr << "exception thrown.\n";
        return 2;
    }
}
