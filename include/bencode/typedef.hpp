#ifndef INCLUDE_bencode_typedef_hpp__
#define INCLUDE_bencode_typedef_hpp__

#include <map>
#include <vector>
#include <bencode/basic_value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename Key
, typename T
, typename Compare
, typename Allocator
> class Container = std::map
> class basic_dict;


template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_integer;


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename T
, typename Allocator > class Container = std::vector
> class basic_list;


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT>
> class basic_string;


} // namespace bencode

#endif // INCLUDE_bencode_typedef_hpp__
