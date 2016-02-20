#ifndef INCLUDE_bencode_token_dict_hpp__
#define INCLUDE_bencode_token_dict_hpp__

#include <algorithm>
#include <map>
#include <utility>
#include <bencode/basic_value.hpp>
#include <bencode/string.hpp>


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
> class basic_dict : public basic_value<CharT, Traits>
{
private:
    // Define the dict key alias.
    typedef basic_string<CharT, Traits> _Key;

    // Define the dict token alias.
    typedef basic_value<CharT, Traits> _Token;

    // Define the key-value pair for the dict container.
    typedef std::pair<const _Key, _Token*> value_type;

    // Define the dict container key-value pairs allocator.
    typedef Allocator<value_type> _Alloc;

    // Define the lexicographical comparator as a wrapper
    // around the STL function.
    template <typename _T>
    struct lexicographical_compare
    {
        bool
        operator()(const _T& lhs, const _T& rhs)
        {
            return std::lexicographical_compare(
                lhs.cbegin(), lhs.cend(),
                rhs.cbegin(), rhs.cend());
        }
    };

    // Define the map comparator. According to the Bencode
    // specification the key in the associative list should
    // be sorted in the lexicographical order, therefore
    // it should denied for the user to specify the custom
    // comparator object.
    typedef lexicographical_compare<_Key> _Compare;

    // Define the dict container type to keep the map
    // of the Bencode tokens.
    typedef Container<_Key, _Token*, _Compare, _Alloc> _Dictionary_container;

    // Define the list constant iterator as a functional
    // equivalent to the container constant iterator.
    typedef typename _Dictionary_container::iterator iterator;

    // Define the list mutable iterator as a functional
    // equivalent to the container mutable iterator.
    typedef typename _Dictionary_container::const_iterator const_iterator;

    // The associative array of the key-value pairs.
    _Dictionary_container container;

public:
    basic_dict() { }

    basic_dict(std::initializer_list<value_type> __list)
    : container(__list.begin(), __list.end()) { }

    ~basic_dict() { }

    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    {
        __s << _Token::dict_type;

        std::for_each(this->container.cbegin(), this->container.cend(),
            [&__s](const value_type& value) {

            value.first.dump(__s);
            __s << _Token::delim_type;
            value.second->dump(__s);
        });

        __s << _Token::end_type;
    }

    void
    load(std::basic_istream<CharT, Traits> &__s) const
    { /* TBD */ }

    void
    insert(std::initializer_list<value_type> __list)
    { this->container.insert(__list.begin(), __list.cend()); }

    std::pair<iterator, bool>
    insert(const value_type& __value)
    { return this->container.insert(__value); }
};


typedef basic_dict<char> dict;


typedef basic_dict<wchar_t> wdict;


} // namespace bencode

#endif // INCLUDE_bencode_token_dict_hpp__
