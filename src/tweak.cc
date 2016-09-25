#include <iostream>
#include "sys.h"
#include "util.h"

#include "../include/tweak.h"

namespace tweak
{
    namespace sys = tweak_sys;
    namespace util = tweak_util;

    Params &get_params()
    {
        static Params params;
        return params;
    }

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

    void define(const std::string &name, base_param &param)
    {
        base_param *&x = get_params()[name];
        assert (x == 0);
        x = &param;
    }
}
