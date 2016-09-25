#include <iostream>
#include "sys.h"
#include "util.h"

namespace tweak
{
    namespace sys = tweak_sys;
    namespace util = tweak_util;

    void process()
    {
        sys::process();
    }

    void init()
    {
        util::update_tweakfile();

        sys::init();
        sys::read_tweakfile();
    }

    float &register_float(const char *name)
    {
        using namespace util;

        FloatMap &float_map = get_float_map();

        FloatParam *&p = float_map[std::string(name)];

        if (!p) {
            p = new FloatParam;
            p->value = 0;
        }

        return p->value;
    }

}

