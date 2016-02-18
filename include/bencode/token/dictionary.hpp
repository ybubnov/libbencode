#ifndef INCLUDE_bencode_token_dictionary_hpp__
#define INCLUDE_bencode_token_dictionary_hpp__

#include <functional>
#include <map>
#include <utility>

#include <bencode/token/basic_token.hpp>


namespace bencode {
namespace token {

template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename Key
, typename T
, typename Compare = std::less<Key>
, typename Allocator = std::allocator<
std::pair<const Key, T> > > class Container = std::map >
class basic_dictionary : public basic_token<CharT, Traits>
{
private:
    typedef std::basic_string<CharT, Traits> _Key;

    typedef basic_token<CharT, Traits> _Token;

    // Define the dictionary container type to kepp the map
    // of the Bencode tokens.
    typedef Container<_Key, _Token> _Dictionary_container;

    _Dictionary_container container;

public:
    basic_dictionary() { }

    ~basic_dictionary() { }

    void dump(std::basic_ostream<CharT, Traits> &s)
    {
        // TBD
    }

    void load(std::basic_istream<CharT, Traits> &s)
    {
        // TBD
    }

};


typedef basic_dictionary<char> dictionary;


typedef basic_dictionary<wchar_t> wdictionary;


} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_dictionary_hpp__
