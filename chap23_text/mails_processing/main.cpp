#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <regex>

#include "Mail_file.hpp"
#include "Message.hpp"

using namespace std;

//------------------------------------------------------------------------------

// NOTE:
// string(s,n)   constructs a tail of s from n onward: s[0]..s[n-1]
// string(s,x,n) constructs a string consisting of s[x]..s[n-1]

int is_prefix(const string& s, const string& p){
    int n = p.size();
    if (string(s,0,n) == p) return n;
    return 0;
}

//------------------------------------------------------------------------------

// find the name of the sender in a Message
// return true if found
// if true, save the name to s
bool find_from_addr(const Message* m, string& s){
    for (const auto& l : *m){
        if (int n = is_prefix(l, "From: ")){
            s = string(l, n);
            return true;
        }
    }
    return false;
}
// same as before but using regex
bool rx_find_from_addr(const Message* m, string& s){
    const regex pat{R"((From:\s+)(((\w)+\s)+\<\w+@\w+(\.com|\.example){1}\>))"};
    for (const auto& l : *m){
        smatch res;
        if (regex_search(l, res, pat)){
            s = res[2].str(); // return 2nd submatch.. group in ()
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

// return the subject of the Message if any, otherwise ""
string find_subject(const Message* m){
    for (const auto& l : *m){
        if (int n = is_prefix(l, "Subject: ")){
            return string(l, n);
        }
    }
    return "";
}
// same as before but using regex
string rx_find_subject(const Message* m){
    const regex pat{R"((Subject:\s+)([\w :]+))"};
    for (const auto& l : *m){
        smatch res;
        if (regex_search(l, res, pat)){
            return res[2].str(); // return 2nd submatch.. group in ()
        }
    }
    return "";
}

//------------------------------------------------------------------------------

int main(){
    try {
        Mail_file mail_file{"mails_examples.txt"};

        // gather messages from each sender to a multimap
        multimap<string, const Message*> sender;
        for (const auto& m : mail_file){
            string s;
            if (rx_find_from_addr(&m, s))
                sender.insert(make_pair(s, &m));
        }

        // now iterate through the multimap
        // and extract the subjects of John Doe's messages:
        auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
        for(auto it = pp.first; it != pp.second; ++it){
            cout << "subject is: " << find_subject(it->second) << "\n";
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

