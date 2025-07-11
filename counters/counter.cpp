#include <algorithm>
#include <string>

int count_letter_a(const std::string& a_str) {
    return std::count(a_str.begin(), a_str.end(), 'a');
}