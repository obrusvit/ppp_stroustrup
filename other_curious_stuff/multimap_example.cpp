#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
using namespace std;


int main(){
    try {
        multimap<string, double> mm;
        mm.insert(pair{"A", 4.1});
        mm.insert(pair{"A", 4.2});
        mm.insert(pair{"B", 5.2});

        for(const auto& el : mm){
            cout << el.first << "\t" << el.second << "\n";
        }

        cout << mm.count("A") << "\n";
        cout << mm.count("C") << "\n";
        
        // get iterator to el with key "A", might return any..
        auto v = mm.find("A");
        cout << v->second << "\n";

        // get them all, use the fact that multimap stores items ordered by key
        // equal_range returns first and last iterator to items with key "A"
        auto vv = mm.equal_range("A");
        for(auto it = vv.first; it != vv.second; ++it){
            cout << it->first << "\t" << it->second << "\n";
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
