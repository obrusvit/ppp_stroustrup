#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

//------------------------------------------------------------------------------

class Record {
    int id;
    string name;
    double price;
    static int id_counter;

    public:
    Record(string n, double p)
        : id{id_counter}, name{n}, price{p}
    {
        ++id_counter;
    }

    const string& getName() const {
        return name;
    }
    double getPrice() const {
        return price;
    }
    int getID() const {
        return id;
    }
};
int Record::id_counter = 0;

//------------------------------------------------------------------------------

void print_records_ids(const vector<Record>& vec){
    cout << "{";
    for(vector<Record>::size_type i = 0; i < vec.size(); ++i){
        cout << vec[i].getID();
        if(i != vec.size()-1)
            cout << ", ";
    }
    cout << "}\n";
}
void print_records(const vector<Record>& vec){
    cout << "{\n";
    for(vector<Record>::size_type i = 0; i < vec.size(); ++i){
        cout << "\t{" << vec[i].getID() << ", " << vec[i].getName() << ", "
             << vec[i].getPrice() << "}\n";
    }
    cout << "}\n";
}

//------------------------------------------------------------------------------

int compare_records(const Record& r1, const Record& r2){
    map<string, double> m;
    return r1.getName() < r2.getName();
}

struct Compare_by_id_func_obj{
    bool operator()(const Record& r1, const Record& r2){
        return r1.getID() < r2.getID();
    }
};

//------------------------------------------------------------------------------

double compute_total_price(const vector<Record>& records, double initial){
    return std::accumulate(records.begin(), records.end(), initial,
                           [](double init, const Record& r2) {
                               return init + r2.getPrice();
                           });
}

//------------------------------------------------------------------------------

int main(){
    try {
        Record r1{"Ntb", 24000};
        Record r2{"Mi", 7000};
        Record r3{"PC", 30000};
        Record r4{"Pixel", 23000};
        Record r5{"Car", 2000000};
        vector<Record> records{r1, r2, r3, r4, r5};
        print_records(records);

        //------------------------------------------------------------------------------

        auto r_name = records;
        auto r_price = records;
        auto r_id = records;

        //------------------------------------------------------------------------------
    
        sort(r_name.begin(), r_name.end(), compare_records);
        print_records(r_name);

        //------------------------------------------------------------------------------

        sort(r_price.begin(), r_price.end(),
             [](const Record& r1, const Record& r2) {
                 return r1.getPrice() < r2.getPrice();
             });
        print_records(r_price);

        //------------------------------------------------------------------------------
        
        sort(r_id.begin(), r_id.end(), Compare_by_id_func_obj());
        print_records(r_id);

        //------------------------------------------------------------------------------
        
        auto total_price = compute_total_price(records, 0.0);
        cout << "Total price of records: " << fixed << setprecision(2) << total_price << "\n";

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
