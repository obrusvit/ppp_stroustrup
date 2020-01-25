#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

//------------------------------------------------------------------------------

default_random_engine& get_rand()
{
	static default_random_engine ran;
	return ran;
};

void seed_randint(int s) { get_rand().seed(s); }

inline int randint(int min, int max) {  return uniform_int_distribution<>{min, max}(get_rand()); }

inline int randint(int max) { return randint(0, max); }

//------------------------------------------------------------------------------

string randstr(){
    string ret{"Hello Cpp!"};
    return ret;
}

//------------------------------------------------------------------------------

template<typename Cont, typename Elem>
    //requires Container<Cont>() && Element<Elem>()
void test_filling_container(Cont& cont){
    int maximal_value = 1000000;
    for(int i = 0; i < maximal_value; ++i){
        int x = randint(maximal_value);
        cont.push_back(x);
    }
}

template<typename Cont, typename Elem>
    //requires Container<Cont>() && Element<Elem>()
void test_filling_container_str(Cont& cont){
    int maximal_value = 1000000;
    for(int i = 0; i < maximal_value; ++i){
        string s = randstr();
        cont.push_back(s);
    }
}

template<typename Cont, typename Elem>
    //requires Container<Cont>() && Element<Elem>()
void test_sorting_container(Cont& cont){
    sort(cont.begin(), cont.end());
}
template<typename Elem>
    //requires Element<Elem>()
void test_sorting_list(list<Elem> lst){
    lst.sort();
}

template<typename Cont, typename Elem, typename Iterator>
    //requires Container<Cont>() && Element<Elem>()
Iterator test_getting_iterator_to_middle(const Cont& cont){
    Iterator it = cont.begin();
    advance(it, cont.size()/2);
    return it;
}

template<typename Cont, typename Elem, typename Iterator>
    //requires Container<Cont>() && Element<Elem>()
void test_removing_from_container(Cont& cont, Iterator it){
    cont.erase(it);
}


//------------------------------------------------------------------------------

int main(){
    try {
        auto time_func_invocation = 
            [] (string comment, auto&& func, auto&&... params){
                const auto& begin = chrono::high_resolution_clock::now();
                std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
                const auto& end = chrono::high_resolution_clock::now();
                auto t_elapsed = chrono::duration_cast<chrono::milliseconds>(end-begin).count();
                cout << comment << " done. Time difference: " << t_elapsed << "[miliseconds].\n";
            };

        vector<double> vec1;
        list<double> lst1;
        time_func_invocation("filling vector", test_filling_container<vector<double>, double>, vec1);
        time_func_invocation("filling list", test_filling_container<list<double>, double>, lst1);

        time_func_invocation("sorting vector", test_sorting_container<vector<double>, double>, vec1);
        time_func_invocation("sorting list", test_sorting_list<double>, lst1); //list has no RAI

        time_func_invocation("getting iterator from vector", test_getting_iterator_to_middle<vector<double>, double, vector<double>::const_iterator>, vec1);
        time_func_invocation("getting iterator from list", test_getting_iterator_to_middle<list<double>, double, list<double>::const_iterator>, lst1);
        auto vec1_it = test_getting_iterator_to_middle<vector<double>, double, vector<double>::const_iterator>(vec1);
        auto lst1_it = test_getting_iterator_to_middle<list<double>, double, list<double>::const_iterator>(lst1);

        time_func_invocation("removing from vector", test_removing_from_container<vector<double>, double, vector<double>::const_iterator>, vec1, vec1_it);
        time_func_invocation("removing from list", test_removing_from_container<list<double>, double, list<double>::const_iterator>, lst1, lst1_it);


        /* vector<string> vec1; */
        /* list<string> lst1; */
        /* time_func_invocation("filling vector", test_filling_container_str<vector<string>, string>, vec1); */
        /* time_func_invocation("filling list", test_filling_container_str<list<string>, string>, lst1); */

        /* time_func_invocation("sorting vector", test_sorting_container<vector<string>, string>, vec1); */
        /* time_func_invocation("sorting list", test_sorting_list<string>, lst1); //list has no RAI */

        /* time_func_invocation("getting iterator from vector", test_getting_iterator_to_middle<vector<string>, string, vector<string>::const_iterator>, vec1); */
        /* time_func_invocation("getting iterator from list", test_getting_iterator_to_middle<list<string>, string, list<string>::const_iterator>, lst1); */
        /* auto vec1_it = test_getting_iterator_to_middle<vector<string>, string, vector<string>::const_iterator>(vec1); */
        /* auto lst1_it = test_getting_iterator_to_middle<list<string>, string, list<string>::const_iterator>(lst1); */

        /* time_func_invocation("removing from vector", test_removing_from_container<vector<string>, string, vector<string>::const_iterator>, vec1, vec1_it); */
        /* time_func_invocation("removing from list", test_removing_from_container<list<string>, string, list<string>::const_iterator>, lst1, lst1_it); */

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
