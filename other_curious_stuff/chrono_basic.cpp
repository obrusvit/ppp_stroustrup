#include <chrono>

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/* 
 * watch this tutorial for everything you need for setup:
 * https://www.youtube.com/watch?v=P32hvk8b13M 
 *
 */

void f(chrono::seconds t){
    cout << "f(): t is " << t.count() << "s\n";
}

void f(chrono::milliseconds t){
    cout << "f(): t is " << t.count() << "ms\n";
}
void f(chrono::minutes t){
    cout << "f(): t is " << t.count() << "m\n";
}



int main(){
    try {
        chrono::seconds t1{3s};
        /* chrono::seconds t2 = 3; //COMPILATION ERROR, int is ambiguous */
        chrono::seconds t2{6s};
        auto t3 = t1+t2;

        chrono::milliseconds t4{6s}; //OK, conversion from higher to lower is loss-less
        chrono::milliseconds t5{6ms};
        /* chrono::minutes t6{60s}; //COMPILATION ERROR, conversion from lower to higher units is lossy */
        chrono::minutes t6{1min};
        auto t7 = t4+t5;

        cout << "t1 has: " << t1.count() << "s\n";
        cout << "t3 has: " << t3.count() << "s\n";
        cout << "t7 has: " << t7.count() << "ms\n";

        f(t1);
        f(t2);
        f(t3);
        f(t4);
        f(t5);
        f(t6);

        auto t8 = chrono::duration_cast<chrono::milliseconds>(t4-t5);
        f(t8);

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
