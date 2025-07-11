#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
struct type_name {
    static const char* get() {
        return typeid(T).name();
    }
};

template <>
struct type_name<int> {
    static const char* get() { return "int"; }
};

template <>
struct type_name<double> {
    static const char* get() { return "double"; }
};

template <>
struct type_name<const char*> {
    static const char* get() { return "const char*"; }
};

template <>
struct type_name<std::string> {
    static const char* get() { return "string"; }
};

template <typename T>
const char* get_type_name(T&&) {
    // removes const/volatile & lvalue/rvaluequalifiers
    using Decayed = std::remove_cv_t<std::remove_reference_t<T>>;
    return type_name<Decayed>::get();
}