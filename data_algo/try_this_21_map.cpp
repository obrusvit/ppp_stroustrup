#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;


int main(){
    try {
        unordered_map<string, double> umap;
        umap["ntb"] = 25000;
        umap["pho"] = 7000;

        for(const auto& el : umap){
            cout << el.first << ": " << el.second << "\n";
        }

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
