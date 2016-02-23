#ifndef INCLUDE_bencode_hpp__
#define INCLUDE_bencode_hpp__


#include <fstream>
#include <bencode/dict.hpp>
#include <bencode/integer.hpp>
#include <bencode/list.hpp>
#include <bencode/string.hpp>


namespace bencode {


template
< CharT
, Traits = std::char_traits<CharT>
basic_token<CharT, Traits>* load_file(std::string& filename)
{
    // TBD
}


template
< CharT
, Traits = std::char_traits<CharT>
void dump_file(std::string& filename, std::shared_ptr<basic_token<CharT, Traits>>&)
{
    // TBD
}


} // namespace bencode


#endif // INCLUDE_bencode_hpp__
