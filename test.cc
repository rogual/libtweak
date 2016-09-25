#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include "include/tweak.h"

TWEAK_FLOAT(thing)
TWEAK_FLOAT(cats)
TWEAK_FLOAT(tuesday)

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
