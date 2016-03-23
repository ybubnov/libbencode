#ifndef INCLUDE_bencode_value_hpp__
#define INCLUDE_bencode_value_hpp__

#include <algorithm>
#include <cstdint>
#include <istream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <bencode/exception.hpp>


namespace bencode
{


/**
 *  @brief Template class basic_value.
 *
 *  @tparam CharT   Character type, defaults to `char`.
 *  @tparam Traits  Traits for character type, defaults to
 *                  `std::char_traits<CharT>`.
 *
 *  This is the base class for all bencode values.
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

    /**
     *  @brief Serialize the token to the specified output stream.
     */
    virtual void
    dump(std::basic_ostream<CharT, Traits>& __s) const = 0;

    /**
     *  @brief Deserialize the token from the specified input stream.
     */
    virtual void
    load(std::basic_istream<CharT, Traits>& __s) = 0;

    /**
     *  @brief Free the resources occupied by the value.
     */
    virtual
    ~basic_value()
    { }
};


// Define integer template typenames used in within class and
// function definitions.
#define __bencode_integer_template \
      typename CharT = char \
    , typename IntT = int64_t \
    , typename Traits = std::char_traits<CharT>


#define __bencode_integer_typenames \
    CharT, IntT, Traits


/**
 *  @brief Template class basic_integer.
 *
 *  @tparam CharT   Character type, defaults to `char`.
 *  @tparam IntT    Integer type, defaults to `int64_t`.
 *  @tparam Traits  Traits for character type, defaults to
 *                  `std::char_traits<CharT>`.
 */
template<__bencode_integer_template> class basic_integer;


/**
 *  @brief Create an integer shared pointer.
 *
 *  @tparam CharT   Character type, defaults to `char`.
 *  @tparam IntT    Integer type, defaults to `int64_t`.
 *  @tparam Traits  Traits for character type, defaults to
 *                  `std::char_traits<CharT>`.
 *
 *  @param __args  Arguments for integer constructor.
 *
 *  Returns a shared pointer to the integer type initialized using
 *  a provided value.
 */
template<__bencode_integer_template, typename ...Args>
std::shared_ptr<basic_integer<__bencode_integer_typenames>>
make_integer(Args&&... __args)
{
    return std::make_shared<basic_integer<
        __bencode_integer_typenames>>(std::forward<Args>(__args)...);
}


// Define string template typenames used in the class and
// function definitions.
#define __bencode_string_template \
      typename CharT = char \
    , typename Traits = std::char_traits<CharT> \
    , template \
    < typename T \
    > class Allocator = std::allocator


#define __bencode_string_typenames \
    CharT, Traits, Allocator

/**
 *  @brief Template class basic_string.
 *
 *  @tparam CharT      Character type.
 *  @tparam Traits     Traits for character type, defaults to
 *                     `std::char_traits<CharT>`.
 *  @tparam Allocator  Allocator type, defaults to `std::allocator<CharT>`.
 */
template<__bencode_string_template> class basic_string;


/**
 *  @brief Create a sting shared pointer.
 *
 *  @tparam CharT      Character type.
 *  @tparam Traits     Traits for character type, defaults to
 *                     `std::char_traits<CharT>`.
 *  @tparam Allocator  Allocator type, defaults to `std::allocator<CharT>`.
 *
 *  @param __args  Arguments for string constructor.
 *
 *  Returns a shared pointer to the string.
 */
template<__bencode_string_template, typename ...Args>
std::shared_ptr<basic_string<__bencode_string_typenames>>
make_string(Args&&... __args)
{
    return std::make_shared<basic_string<
        __bencode_string_typenames>>(std::forward<Args>(__args)...);
}


// Define dictionary template typenames used in the class and
// function definitions.
#define __bencode_dict_template \
      typename CharT = char \
    , typename IntT = int64_t \
    , typename Traits = std::char_traits<CharT> \
    , template \
    < typename T \
    > class Allocator = std::allocator \
    , template \
    < typename Key \
    , typename T \
    , typename... Args \
    > class DictContainer = std::map \
    , template \
    < typename T \
    , typename... Args \
    > class ListContainer = std::vector


#define __bencode_dict_typenames \
    CharT, IntT, Traits, Allocator, DictContainer, ListContainer


/**
 *  @brief Template class basic_dict.
 *
 *  @tparam CharT          Character type, defaults to `char`.
 *  @tparam IntT           Integer type, defaults to `int64_t`.
 *  @tparam Traits         Traits for character type, defaults to
 *                         `std::char_traits<CharT>`.
 *  @tparam Allocator      Allocator type, defaults to `std::allocator`.
 *  @tparam DictContainer  Dictionary type, defaults to `std::map`.
 *  @tparam ListContainer  List type, defaults to `std::vector`.
 *
 *  Define the type of associative array, which is storing the mapping
 *  of string keys to the bencode values.
 */
template<__bencode_dict_template> class basic_dict;


/**
 *  @brief Create a dictionary shared pointer.
 *
 *  @tparam CharT          Character type, defaults to `char`.
 *  @tparam IntT           Integer type, defaults to `int64_t`.
 *  @tparam Traits         Traits for character type, defaults to
 *                         `std::char_traits<CharT>`.
 *  @tparam Allocator      Allocator type, defaults to `std::allocator`.
 *  @tparam DictContainer  Dictionary type, defaults to `std::map`.
 *  @tparam ListContainer  List type, defaults to `std::vector`.
 *
 *  @param __list  Dictionary initializer list.
 *
 *  Returns a shared pointer to the dictionary type.
 */
template<__bencode_dict_template, typename ...Args>
std::shared_ptr<basic_dict<__bencode_dict_typenames>>
make_dict(Args&&... __args)
{
    return std::make_shared<basic_dict<
        __bencode_dict_typenames>>(std::forward<Args>(__args)...);
}


// Define list template typenames used in the class and
// function definitions.
#define __bencode_list_template \
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


#define __bencode_list_typenames \
    CharT, IntT, Traits, Allocator, ListContainer, DictContainer

/**
 *  @brief Template class basic_list.
 *
 *  @tparam CharT          Character type, defaults to `char`.
 *  @tparam IntT           Integer type, defaults to `int64_t`.
 *  @tparam Traits         Traits for character type, defaults to
 *                         `std::char_traits<CharT>`.
 *  @tparam Allocator      Allocator type, defaults to `std::allocator`.
 *  @tparam ListContainer  List type, defaults to `std::vector`.
 *  @tparam DictContainer  Dictionary type, defaults to `std::map`.
 *
 *  Define the type of array, which is storing the list of bencode
 *  values.
 */
template<__bencode_list_template> class basic_list;


/**
 *  @brief Create a list shared pointer.
 *
 *  @tparam CharT          Character type, defaults to `char`.
 *  @tparam IntT           Integer type, defaults to `int64_t`.
 *  @tparam Traits         Traits for character type, defaults to
 *                         `std::char_traits<CharT>`.
 *  @tparam Allocator      Allocator type, defaults to `std::allocator`.
 *  @tparam ListContainer  List type, defaults to `std::vector`.
 *  @tparam DictContainer  Dictionary type, defaults to `std::map`.
 *
 *  @param __args  Arguments for the list constructor.
 *
 *  Returns a shared pointer to the list type.
 */
template<__bencode_list_template, typename ...Args>
std::shared_ptr<basic_list<__bencode_list_typenames>>
make_list(Args&&... __args)
{
    return std::shared_ptr<basic_list<
        __bencode_list_typenames>>(std::forward<Args>(__args)...);
}


/**
 *  @brief Parse bencoded value.
 *
 *  @tparam CharT          Character type, defaults to `char`.
 *  @tparam IntT           Integer type, defaults to `int64_t`.
 *  @tparam Traits         Traits for character type, defaults to
 *                         `std::char_traits<CharT>`.
 *  @tparam Allocator      Allocator type, defaults to `std::allocator`.
 *  @tparam ListContainer  List type, defaults to `std::vector`.
 *  @tparam DictContainer  Dictionary type, defaults to `std::map`.
 *
 *  @param __s  Input stream.
 *
 *  Returns a shared pointer of the base value class. The pointer is
 *  storing the decoded value from the provided input stream. The target
 *  type is selected based on the first character of the input stream.
 */
template<__bencode_dict_template>
std::shared_ptr<basic_value<CharT, Traits>>
make_value(std::basic_istream<CharT, Traits> &__s)
{
    using basic_type = basic_value<CharT, Traits>;

    // Define a bunch of aliases with template arguments.
    using integer_type = basic_integer<__bencode_integer_typenames>;
    using string_type = basic_string<__bencode_string_typenames>;
    using list_type = basic_list<__bencode_list_typenames>;
    using dict_type = basic_dict<__bencode_dict_typenames>;

    std::shared_ptr<basic_type> __ptr;

    // Based on the first character in the provided input stream,
    // select the target parser type.
    switch (__s.peek())
    {
    case basic_type::integer_token:
        __ptr = std::make_shared<integer_type>();
        break;
    case basic_type::list_token:
        __ptr = std::make_shared<list_type>();
        break;
    case basic_type::dict_token:
        __ptr = std::make_shared<dict_type>();
        break;
    default:
        __ptr = std::make_shared<string_type>();
    }

    __ptr->load(__s);
    return __ptr;
}


} // namespace bencode

#endif // INCLUDE_bencode_value_hpp__
