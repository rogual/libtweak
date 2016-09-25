#pragma once

#ifdef TWEAK_BAKE
    #define TWEAK_FLOAT(name) \
        using tweak_baked::name;

    namespace tweak
    {
        inline void init() {}
        inline bool process() {}
    }

#else
    #define TWEAK_FLOAT(name) \
        static const float &name = tweak::register_float(#name);

    namespace tweak
    {
        void init();
        bool process();
        float &register_float(const char *name);
    }
#endif

