#include "Mail_file.hpp"
#include <fstream>

Mail_file::Mail_file(const std::string& filename){
    std::ifstream ifs{filename};
    if(!ifs){
        throw std::runtime_error{"opening failed"};
    }

    for(std::string s; getline(ifs, s); ){
        all_lines.push_back(s);
    }

    // build vector of Messages
    auto first = all_lines.begin();
    for(auto it = all_lines.begin(); it != all_lines.end(); ++it){
        if(*it == "----"){
            messages.push_back(Message{first, it});
            first = it+1;
        }
    }
}
