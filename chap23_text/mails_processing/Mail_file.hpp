#ifndef GUARD_MAIL_FILE_HPP
#define GUARD_MAIL_FILE_HPP

#include <vector>
#include <string>

#include "Message.hpp"

class Mail_file {
    using Mess_iter = std::vector<Message>::const_iterator;

    std::string name;
    std::vector<std::string> all_lines;
    std::vector<Message> messages;

public:
    Mail_file(const std::string& filename);

    Mess_iter begin() const {
        return messages.begin();
    }
    Mess_iter end() const {
        return messages.end();
    }

};
#endif

