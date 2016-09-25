#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "../include/tweak.h"

#include "util.h"

namespace tweak_util
{
    static void cmd_set(std::istream &ss)
    {
        std::string name;
        ss >> name;

        tweak::Params &params = tweak::get_params();

        auto it = params.find(name);
        if (it == params.end()) {
            puts("set: bad name");
        }
        else
        {
            it->second->load(ss);
        }
    }

    static void process_message(const std::string &msg)
    {
        std::istringstream ss(msg);

        std::string command;
        ss >> command;

        if (command == "set")
            cmd_set(ss);
    }

    void process_bytes(const char *buf, size_t sz)
    {
        static std::string byte_queue;

        for (int i=0; i<sz; i++) {
            if (buf[i] == '\n') {
                process_message(byte_queue);
                byte_queue.clear();
            }
            else
                byte_queue.push_back(buf[i]);
        }
    }

    void update_tweakfile()
    {
        std::map<std::string, std::string> file_values;
        std::vector<std::string> pass_through;

        {
            std::ifstream is("Tweakfile");
            while (is.good()) {
                std::string line;
                std::getline(is, line);

                if (line.empty())
                    continue;

                std::istringstream ss(line);

                std::string cmd;
                ss >> cmd;
                if (cmd == "set") {
                    std::string name;
                    ss >> name;
                    file_values[name] = line;
                }
                else if (cmd != "type")
                    pass_through.push_back(line);
            }
        }

        std::ofstream os("Tweakfile");

        // Types
        tweak::Params &params = tweak::get_params();
        for (auto item: params) {
            const std::string &name = item.first;
            tweak::base_param &param = *item.second;
            os << "type " << name << " " << param.get_type_name() <<
                "\n";
        }
        os << "\n";

        // Values
        for (auto item: params) {
            const std::string &name = item.first;
            tweak::base_param &param = *item.second;

            auto it = file_values.find(name);
            if (it != file_values.end()) {
                // Keep value from file
                os << it->second << "\n";
            }
            else {
                // Write default value to file
                os << "set " << name << " ";
                param.save(os);
                os << "\n";
            }
        }
        os << "\n";

        // Leave all other lines in file
        for (auto cmd: pass_through)
            os << cmd << "\n";

    }
}
