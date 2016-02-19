#ifndef INCLUDE_bencode_token_list_hpp__
#define INCLUDE_bencode_token_list_hpp__

#include <algorithm>
#include <iterator>
#include <initializer_list>
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
< typename T
, typename Allocator > class Container = std::vector
> class basic_list : public basic_value<CharT, Traits>
{
private:
    // Define the list token alias.
    typedef basic_value<CharT, Traits> _Token;

    // Define the list container allocator for the tokens.
    typedef Allocator<_Token*> _Alloc;

    // Define the list container type to keep the collection
    // of the Bencode tokens.
    typedef Container<_Token*, _Alloc> _List_container;

    // Define the list constant iterator as a functional
    // equivalent to the container iterator.
    typedef typename _List_container::const_iterator const_iterator;

    // The collections of the Bencode tokens.
    _List_container container;

public:
    basic_list() { }

    // Create a new list token from the initializer list.
    basic_list(std::initializer_list<_Token*> l)
    : container(l) { }

    basic_list(const_iterator cbegin, const_iterator cend)
    : container(cbegin, cend) { }

    ~basic_list() { }

    // Serialize the list token to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits>& s) const
    {
        s << "l";

        std::for_each(this->container.begin(), this->container.end(),
            [&s](_Token* value) {

            value->dump(s);
        });

        s << "e";
    }

    // Deserialize the list token from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits>& s) const
    { /* TBD */ }

    void
    push_back(_Token* value)
    { this->container.push_back(value); }
};


typedef basic_list<char> list;


typedef basic_list<wchar_t> wlist;


} // namespace bencode


#endif // INCLUDE_bencode_token_list_hpp__
