#ifndef INCLUDE_bencode_utility_hpp__
#define INCLUDE_bencode_utility_hpp__

#include <bencode/dict.hpp>
#include <bencode/integer.hpp>
#include <bencode/list.hpp>
#include <bencode/string.hpp>
#include <bencode/value.hpp>


namespace bencode
{
inline namespace literals
{


/**
 *  @brief User-defined bencode string literal.
 *  @param __str  Bencoded string value.
 *
 *  Returns the shared pointer to the basic bencode value, that
 *  is constructed by parsing the provided string.
 */
std::shared_ptr<basic_value<char>>
inline operator"" _bencode(const char* __str, std::size_t)
{
    std::istringstream __ss(__str);
    return make_value<char>(__ss);
}


/**
 *  @brief User-defined bencode string literal.
 *  @param __str  Bencoded string value.
 *
 *  Returns the shared pointer to the basic bencode value, that
 *  is constructed by parsing the provided string.
 */
std::shared_ptr<basic_value<wchar_t>>
inline operator"" _bencode(const wchar_t* __str, std::size_t)
{
    std::wistringstream __ss(__str);
    return make_value<wchar_t>(__ss);
}


/**
 *  @brief User-defined bencode string literal.
 *  @param __str  Bencoded string value.
 *
 *  Returns the shared pointer to the basic bencode value, that
 *  is constructed by parsing the provided string.
 */
std::shared_ptr<basic_value<char16_t>>
inline operator"" _bencode(const char16_t* __str, std::size_t)
{
    std::basic_stringstream<char16_t> __ss(__str);
    return make_value<char16_t>(__ss);
}


/**
 *  @brief User-defined bencode string literal.
 *  @param __str  Bencoded string value.
 *
 *  Returns the shared pointer to the basic bencode value, that
 *  is constructed by parsing the provided string.
 */
std::shared_ptr<basic_value<char32_t>>
inline operator"" _bencode(const char32_t* __str, std::size_t)
{
    std::basic_stringstream<char32_t> __ss(__str);
    return make_value<char32_t>(__ss);
}


} // inline namespace listerals
} // namespace bencode


#endif // INCLUDE_bencode_utility_hpp__
