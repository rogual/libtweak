#include <string>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include "include/tweak.h"

TWEAK(int, thing)
TWEAK(float, cats)
TWEAK(std::string, tuesday)

int main(int argc, char **argv)
{
    tweak::init();

    for (;;) {
        tweak::process();
        std::cout << "\x1b[2K\r"; // clear line
        std::cout << "thing=" << thing << "  cats=" << cats << "  tuesday=" << tuesday;
        std::cout.flush();
        usleep(50);
    }
}
