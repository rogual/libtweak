#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "util.h"

namespace tweak_util
{
    FloatMap &get_float_map() {
        static FloatMap float_map;
        return float_map;
    }

    static void cmd_set(std::istream &ss)
    {
        std::string name;
        ss >> name;

        float value;
        ss >> value;

        FloatMap &float_map = get_float_map();

        auto it = float_map.find(name);
        if (it == float_map.end()) {
            puts("set: bad name");
        }
        else
        {
            it->second->value = value;
        }
    }

    static void cmd_range(std::istream &ss)
    {
    }

    static void process_message(const std::string &msg)
    {
        std::istringstream ss(msg);

        std::string command;
        ss >> command;

        if (command == "set")
            cmd_set(ss);
        else if (command == "range")
            cmd_range(ss);
        else {
            puts("bad cmd");
        }
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
        std::map<std::string, float> file_values;
        std::vector<std::string> range_cmds;

        {
            std::ifstream is("Tweakfile");
            while (is.good()) {
                std::string line;
                std::getline(is, line);
                std::istringstream ss(line);

                std::string cmd;
                ss >> cmd;
                if (cmd == "set") {
                    std::string name;
                    float value;
                    ss >> name >> value;
                    file_values[name] = value;
                }
                else
                    range_cmds.push_back(line);
            }
        }

        std::ofstream os("Tweakfile");
        FloatMap &float_map = get_float_map();
        for (auto cmd: range_cmds)
            os << cmd << "\n";
        for (auto item: float_map) {
            const std::string &name = item.first;
            FloatParam param = *(item.second);
            auto it = file_values.find(name);
            if (it != file_values.end()) {
                param.value = it->second;
            }
            os << "set " << name << " " << param.value << "\n";
        }
    }
}
