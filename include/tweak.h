#pragma once

#ifdef TWEAK_BAKE
    #define TWEAK(type, name) \
        using tweak_baked::name;

    #define EXTERN_TWEAK(type, name) \
        TWEAK(type, name)

    namespace tweak
    {
        inline void init() {}
        inline bool process() {}
    }

#else

    #define TWEAK(type, name) \
        const type &name = tweak::define<type>(#name);

    #define EXTERN_TWEAK(type, name) \
        extern const type &name;

    #include <map>
    #include <string>
    #include <cassert>

    namespace tweak
    {
        void init();
        void process();

        class base_param
        {
            public:
                virtual std::string get_type_name() const = 0;
                virtual void load(std::istream &is) = 0;
                virtual void save(std::ostream &os) const = 0;
        };

        typedef std::map<std::string, base_param *> Params;
        Params &get_params();

        template<typename T>
        struct type_name
        {
            static std::string get();
        };

        template<typename T>
        struct io
        {
            static void load(T &value, std::istream &is)
            {
                is >> value;
            }

            static void save(const T &value, std::ostream &os)
            {
                os << value;
            }
        };

        template<typename T>
        class param: public base_param
        {
            public:
                param(): value() {}

                T &ref()
                {
                    return value;
                }

                std::string get_type_name() const override
                {
                    return tweak::type_name<T>::get();
                }

                void load(std::istream &is) override
                {
                    tweak::io<T>::load(value, is);
                }

                void save(std::ostream &os) const override
                {
                    tweak::io<T>::save(value, os);
                }

            private:
                T value;
        };

        void define(const std::string &name, base_param &);

        template<typename T>
        const T &define(const std::string &name)
        {
            param<T> *p = new param<T>;
            define(name, *p);
            return p->ref();
        }

        #define ITEM(T) \
            template<> struct type_name<T> { static std::string get(); };

        ITEM(float)
        ITEM(int)
        ITEM(std::string)

        #undef ITEM

        template<>
        struct io<std::string>
        {
            static void load(std::string &value, std::istream &is);
            static void save(const std::string &value, std::ostream &os);
        };
    }
#endif
