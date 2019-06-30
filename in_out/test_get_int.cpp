#include "get_int.h"
#include<iostream>

int main(){
    int n = get_int("Enter some integer", "Oops, didn't work");
    std::cout << n << "\n";
}
