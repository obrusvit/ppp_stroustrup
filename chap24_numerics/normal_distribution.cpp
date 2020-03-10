#include <iostream>
#include <stdexcept>
#include <vector>

#include <functional>
#include <random>

using namespace std;




int main(){
    try {
        auto gen = std::bind(std::normal_distribution<double>{10.0, 2.0}, std::default_random_engine{2});
        vector<int> hist(20);

        for(int i = 0; i < 500; ++i){
            double new_one = gen();
            int idx = static_cast<int>(round(new_one));
            ++hist[idx];
        }

        for(std::vector<int>::size_type idx = 0; idx != hist.size(); ++idx){
            cout << idx << ":\t";
            for(int i = 0; i < hist[idx]; ++i)
                cout << "*";
            cout << "\n";

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

