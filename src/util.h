#include <string>
#include <map>

namespace tweak_util
{
    struct FloatParam
    {
        float value;
    };

    typedef std::map<std::string, FloatParam *> FloatMap;

    void update_tweakfile();
    void process_bytes(const char *, size_t);
    FloatMap &get_float_map();
}
