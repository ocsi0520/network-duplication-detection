#include <iostream>
#include "counter.hpp"
#include "TypeName.hpp"

int main()
{
    std::cout << count_letter_a("Hello World from main") << std::endl;
    std::cout << get_type_name(count_letter_a("Hello World from main")) << std::endl;
    return 0;
}