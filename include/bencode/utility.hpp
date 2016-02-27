#ifndef INCLUDE_bencode_utility_hpp__
#define INCLUDE_bencode_utility_hpp__

#include <map>
#include <vector>
#include <bencode/dict.hpp>
#include <bencode/integer.hpp>
#include <bencode/list.hpp>
#include <bencode/string.hpp>


namespace bencode
{

// Forward declaration of the Bencode dictionary type.
template
< typename CharT
, typename Traits
, template
< typename T
> class Allocator
, template
< typename Key
, typename T
, typename Compare
, typename Allocator
> class DictContainer
, template
< typename T
, typename Allocator
> class ListContainer
> class basic_dict;


// Forward declaration of the Bencode list type.
template
< typename CharT
, typename Traits
, template
< typename T
> class Allocator
, template
< typename T
, typename Allocator
> class ListContainer
, template
< typename Key
, typename T
, typename Compare
, typename Allocator
> class DictContainer
> class basic_list;


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator
, template
< typename T
, typename Allocator
> class ListContainer = std::vector
, template
< typename Key
, typename T
, typename Compare
, typename Allocator
> class DictContainer = std::map
> std::shared_ptr<basic_value<CharT, Traits> >
make_value(std::basic_istream<CharT, Traits> &__s)
{
    typedef basic_value<CharT, Traits> _Value;
    typedef basic_integer<CharT, Traits> _Integer;
    typedef basic_string<CharT, Traits, Allocator> _String;

    typedef basic_list<CharT, Traits,
        Allocator, ListContainer, DictContainer> _List;

    typedef basic_dict<CharT, Traits,
        Allocator, DictContainer, ListContainer> _Dict;

    std::shared_ptr<_Value> __ptr;

    switch (__s.peek())
    {
    case _Value::int_type:
        __ptr = std::make_shared<_Integer>();
        break;
    case _Value::list_type:
        __ptr = std::make_shared<_List>();
        break;
    case _Value::dict_type:
        __ptr = std::make_shared<_Dict>();
        break;
    default:
        __ptr = std::make_shared<_String>();
    }

    __ptr->load(__s);
    return __ptr;
}


} // namespace bencode

#endif // INCLUDE_bencode_utility_hpp__
