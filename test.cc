#include <string>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include "include/tweak.h"

TWEAK(float, alertness)
TWEAK(int, num_cats)
TWEAK(std::string, tuesday)
TWEAK(bool, boosters_enabled)

int main(int argc, char **argv)
{
    tweak::init();

    for (;;) {
        tweak::process();
        std::cout << "\x1b[2K\r"; // clear line
        std::cout <<
            "alertness=" << alertness <<
            "  cats=" << num_cats <<
            "  tuesday=" << tuesday <<
            "  boosters=" << boosters_enabled;
        std::cout.flush();
        usleep(50);
    }
}
