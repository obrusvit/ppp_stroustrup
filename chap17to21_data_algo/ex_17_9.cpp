#include <iostream>
#include <stdexcept>

using namespace std;


int main(){
    try {
        // static memory on the stack
        char stack1[2] = {'y', 'n'};
        char stack2[2] = {'Y', 'N'};

        //to print address, cast to void*, otherwise operator<< is overloaded for char*
        cout << "Stack\n";
        cout << reinterpret_cast<void*>(&stack1[0]) << "\n";
        cout << reinterpret_cast<void*>(&stack1[1]) << "\n";
        cout << reinterpret_cast<char*>(&stack1[1])-reinterpret_cast<char*>(&stack1[0]) << "\n"; // 1
        cout << reinterpret_cast<void*>(&stack2[0]) << "\n";
        cout << reinterpret_cast<void*>(&stack2[1]) << "\n";

        // dynamic memroy on the heap
        char* heap1 = new char[2];
        char* heap2 = new char[2];
        heap1[0] = 'y'; heap1[1] = 'n';
        heap2[0] = 'Y'; heap2[1] = 'N';
        cout << "Heap\n";
        cout << reinterpret_cast<void*>(&heap1[0]) << "\n";
        cout << reinterpret_cast<void*>(&heap1[1]) << "\n";
        cout << reinterpret_cast<void*>(&heap2[0]) << "\n";
        cout << reinterpret_cast<void*>(&heap2[1]) << "\n";
        delete[] heap1;
        delete[] heap2;

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
