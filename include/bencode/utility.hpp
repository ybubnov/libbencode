#ifndef INCLUDE_bencode_utility_hpp__
#define INCLUDE_bencode_utility_hpp__

#include <bencode/dict.hpp>
#include <bencode/integer.hpp>
#include <bencode/list.hpp>
#include <bencode/string.hpp>
#include <bencode/value.hpp>


namespace bencode
{


std::shared_ptr<basic_value<char>>
inline operator"" _bencode(const char* __chars, std::size_t)
{
    std::istringstream __ss(__chars);
    return make_value<char>(__ss);
}


} // namespace bencode


#endif // INCLUDE_bencode_utility_hpp__
