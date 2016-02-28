#ifndef INCLUDE_bencode_utility_hpp__
#define INCLUDE_bencode_utility_hpp__

#include <cstddef>
#include <sstream>
#include <bencode/value.hpp>


namespace bencode
{


// std::shared_ptr<basic_value<char>>
// operator"" _bencode(const char* __chars)
// {
//     std::stringstream __ss(__chars);
//     return make_value<char>(__ss);
// }


} // namespace bencode


#endif // INCLUDE_bencode_utility_hpp__
