#include <string>
#include <iostream>

#include "../include/tweak.h"

namespace tweak
{
    using std::string;

    string type_name<float>::get() { return "float"; }
    string type_name<int>::get() { return "int"; }
    string type_name<string>::get() { return "string"; }

    void io<string>::load(string &value, std::istream &is)
    {
        char delim;
        do {
            is.get(delim);
        }
        while(delim == ' ');

        if (delim == '$') {
            std::getline(is, value);
        }
        else {
            puts("Bad string format");
        }
    }

    void io<string>::save(const string &value, std::ostream &os)
    {
        os << "$" << value;
    }
}
