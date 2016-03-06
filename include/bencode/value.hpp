#ifndef INCLUDE_bencode_value_hpp__
#define INCLUDE_bencode_value_hpp__

#include <algorithm>
#include <cstdint>
#include <istream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <bencode/exception.hpp>


namespace bencode
{


/**
 * @brief Template class basic_value.
 *
 * @tparam CharT  Type of character stream.
 * @tparam Traits Traits for character type, defaults to
 *                `std::char_traits<CharT>`.
 *
 * This is the base class for all bencode values.
 */
template
< typename CharT = char
, typename Traits = std::char_traits<CharT>
> class basic_value {
public:
    using char_type = typename Traits::char_type;

    using istream_type = std::basic_istream<CharT, Traits>;

    using ostream_type = std::basic_ostream<CharT, Traits>;

    // Define the template typename-dependent values
    // of the Bencode format tokens.
    static const auto delimiter_token = char_type(':');
    static const auto integer_token = char_type('i');
    static const auto list_token = char_type('l');
    static const auto dict_token = char_type('d');
    static const auto end_token = char_type('e');

    // To prevent the buffer overload during the extraction of the length
    // of the string value, we are going to limit the count of symbols to
    // read up to twenty symbols. So if after read of twenty symbols an
    // end of the token was not reached we should throw a error.
    static const auto integer_length = 20;

    // Serialize the token to the specified output stream.
    virtual void
    dump(std::basic_ostream<CharT, Traits> &__s) const = 0;

    // Deserialize the token from the specified input stream.
    virtual void
    load(std::basic_istream<CharT, Traits> &__s) = 0;

    // Free the resources occupied by the token.
    virtual
    ~basic_value() { }
};

/**
 * @brief Template class basic_list.
 *
 * @tparam CharT         Type of character stream.
 * @tparam IntT          Type of produced integer values.
 * @tparam Traits        Traits for character type, defaults to
 *                       `std::char_traits<CharT>`.
 * @tparam Allocator
 * @tparam ListContainer
 * @tparam DictContainer
 */
#define __declare_dict \
      typename CharT = char \
    , typename IntT = int64_t \
    , typename Traits = std::char_traits<CharT> \
    , template \
    < typename T \
    > class Allocator = std::allocator \
    , template \
    < typename T \
    , typename... Args \
    > class ListContainer = std::vector \
    , template \
    < typename Key \
    , typename T \
    , typename... Args \
    > class DictContainer = std::map

template
< typename CharT
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename T
, typename... Args
> class ListContainer = std::vector
, template
< typename Key
, typename T
, typename... Args
> class DictContainer = std::map
> class basic_list;


/**
 * @brief Template class basic_dict.
 *
 * @tparam CharT         Type of character stream.
 * @tparam IntT          Type of produced integer values.
 * @tparam Traits        Traits for character type, defaults to
 *                       `std::char_traits<CharT>`.
 * @tparam Allocator
 * @tparam DictContainer
 * @tparam ListContainer
 */
template
< typename CharT
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename Key
, typename T
, typename... Args
> class DictContainer = std::map
, template
< typename T
, typename... Args
> class ListContainer = std::vector
> class basic_dict;


template
< typename CharT = char
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename Key
, typename T
, typename... Args
> class DictContainer = std::map
, template
< typename T
, typename... Args
> class ListContainer = std::vector
> std::shared_ptr<
    basic_dict<CharT, IntT, Traits, Allocator,
        DictContainer, ListContainer>>
make_dict(std::intializer_list<
    std::pair<std::basic_string<CharT, Traits, Allocator>,
        basic_value<CharT, Traits>> __list)
{
    return nullptr;
}


/**
 * @brief Template class basic_integer.
 *
 * @tparam CharT  Type of character stream.
 * @tparam IntT   Type of produced integer values.
 * @tparam Traits Traits for character type, defaults to
 *                `std::char_traits<CharT>`.
 */
template
< typename CharT
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
> class basic_integer;


template
< typename CharT = char
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
> std::shared_ptr<
    basic_integer<CharT, IntT, Traits>>
make_integer(IntT __value)
{
    return std::make_shared<basic_integer<
        CharT, IntT, Traits>>(__value);
}


/**
 * @brief Template class basic_integer.
 *
 * @tparam CharT     Type of character stream.
 * @tparam Traits    Traits for character type, defaults to
 *                   `std::char_traits<CharT>`.
 * @tparam Allocator
 */
template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
> class basic_string;


template
< typename CharT
, typename IntT = int64_t
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename T
, typename... Args
> class ListContainer = std::vector
, template
< typename Key
, typename T
, typename... Args
> class DictContainer = std::map
> std::shared_ptr<basic_value<CharT, Traits>>
make_value(std::basic_istream<CharT, Traits> &__s)
{
    using basic_type = basic_value<CharT, Traits>;
    using integer_type = basic_integer<CharT, IntT, Traits>;
    using string_type = basic_string<CharT, Traits, Allocator>;
    using list_type = basic_list<CharT, IntT, Traits,
          Allocator, ListContainer, DictContainer>;
    using dict_token = basic_dict<CharT, IntT, Traits,
        Allocator, DictContainer, ListContainer>;

    std::shared_ptr<basic_type> __ptr;

    switch (__s.peek())
    {
    case basic_type::integer_token:
        __ptr = std::make_shared<integer_type>();
        break;
    case basic_type::list_token:
        __ptr = std::make_shared<list_type>();
        break;
    case basic_type::dict_token:
        __ptr = std::make_shared<dict_token>();
        break;
    default:
        __ptr = std::make_shared<string_type>();
    }

    __ptr->load(__s);
    return __ptr;
}


} // namespace bencode

#endif // INCLUDE_bencode_value_hpp__
