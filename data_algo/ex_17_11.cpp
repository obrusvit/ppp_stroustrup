/*
 * Link list example
 * using standalone functions.
 */
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

struct Link {
    string value;
    Link* prev;
    Link* succ;
    Link(string v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s}
    {
    }
};

Link* insert(Link* p, Link* n){
    //insert n before p, return n;
    if(!p) return nullptr;
    if(!n) return nullptr;
    if(p->prev) p->prev->succ = n;
    n->prev = p->prev;
    p->prev = n;
    n->succ = p;

    return n;
}

Link* add(Link* p, Link* n){
    //add n after p, return n;
    if(!p) return nullptr;
    if(!n) return nullptr;
    if(p->succ) p->succ->prev = n;
    n->succ = p->succ;
    p->succ = n;
    n->prev = p;
    return n;
}

Link* find(Link* p, const string& s){
    //find Link with s in list
    //return nullptr if not found
    while(p){
        if(p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

Link* advance(Link* p, int n){
    //move n positions in the list
    if(!p) return nullptr;
    
    if(n > 0){
        while(n--){
            if(!p->succ) return nullptr;
            p = p->succ;
        }
    }
    else if(n < 0){
        while(n++){
            if(!p->prev) return nullptr;
            p = p->prev;
        }
    }
    return p;
}

Link* erase(Link* p){
    //remove*p from list, return p's successor
    if(!p) return nullptr;
    if(p->succ) p->succ->prev = p->prev;
    if(p->prev) p->prev->succ = p->succ;
    Link* to_ret = p->succ;
    delete p;
    return to_ret;
}

void delete_list(Link* p){
    while(p){
        Link* next_one = p->succ;
        delete p;
        p = next_one;
    }
}

void print_all(Link* p){
    cout << "{";
    while(p){
        cout << p->value;
        if((p = p->succ)) cout << ", ";
    }
    cout << "}";
}

int main(){
    try {
        Link* norse_gods = new Link{"Thor"};
        norse_gods = insert(norse_gods, new Link{"Odin"});
        norse_gods = insert(norse_gods, new Link{"Theia"});
        Link* newly_added = add(norse_gods, new Link{"Obrusvit"}); // adds after the first (Theia)

        print_all(norse_gods);
        erase(newly_added);
        print_all(norse_gods);
        norse_gods = erase(norse_gods); // we need care about ptr to first Link
        print_all(norse_gods);
        
        //delete norse_gods;
        delete_list(norse_gods);
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
