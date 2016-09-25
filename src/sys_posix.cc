#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#include <cerrno>
#include <cstdlib>
#include <iostream>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "util.h"

namespace tweak_sys
{
    namespace util = tweak_util;

    static int fifo_fd;

    static bool process_fd(int fd)
    {
        static const int bufsz = 1024;
        static char buf[bufsz];

        ssize_t r = read(fd, &buf, bufsz);
        if (r == 0) {
            return false;
        }
        else if (r == -1) {
            if (errno == EAGAIN)
                return true;
            puts("ERR");
            exit(-1);
        }
        else {
            util::process_bytes(buf, r);
        }
        return true;
    }

    void read_tweakfile()
    {
        int fd = open("Tweakfile", O_RDONLY);
        if (fd > 0)
            while (process_fd(fd)) {}
    }

    void process()
    {
        process_fd(fifo_fd);
    }

    void init()
    {
        if (mkfifo("Tweakfifo", 0644)) {
            if (errno == EEXIST)
                ;
            else {
                std::cout << "ERROR " << errno << "\n";
                exit(-1);
            }
        }

        fifo_fd = open("Tweakfifo", O_RDONLY | O_NONBLOCK);
    }
}

#endif
