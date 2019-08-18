#include <iostream>
#include <stdexcept>
#include <vector>

#include <memory>

using namespace std;

class A{
    public:
    int* p;
    char* ch;
    double * d;
    A(){
       p = new int(42); 
       ch = new char('c');
    }
    ~A(){
        delete p;
        /* memory leak 1 byte because ch not deleted */
        /* NO leak for d, because it is not initialized */
    }
    void foo(){
        cout << "A has " << *p << "\n";
        cout << "A has " << *ch << "\n";
    }
};

int main(){
    try {

        A a;
        a.foo();

        /* this "fixes" the memory leak */
        allocator<char> a1;
        a1.deallocate(a.ch, 1);

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
