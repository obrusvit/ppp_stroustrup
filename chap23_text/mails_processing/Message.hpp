#ifndef GUARD_MESSAGE_HPP
#define GUARD_MESSAGE_HPP

#include <vector>
#include <string>

class Message {

    using Line_iter = std::vector<std::string>::const_iterator;

    Line_iter first;
    Line_iter last;

public:
    Message(Line_iter f, Line_iter l)
        : first{f}, last{l}
    {

    }

    Line_iter begin() const {
        return first;
    }

    Line_iter end() const {
        return last;
    }

};

#endif

