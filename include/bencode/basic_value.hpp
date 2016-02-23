#ifndef INCLUDE_bencode_basic_value_hpp__
#define INCLUDE_bencode_basic_value_hpp__

#include <algorithm>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <bencode/exception.hpp>


namespace bencode
{


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
// An abstract class for Bencode tokens.
class basic_value {
protected:
    typedef typename Traits::char_type char_type;

public:
    // Define the template typename-dependent values
    // of the Bencode format tokens.
    static const auto delim_type = char_type(':');
    static const auto int_type = char_type('i');
    static const auto list_type = char_type('l');
    static const auto dict_type = char_type('d');
    static const auto end_type = char_type('e');

    // Serialie the token to the specified output stream.
    virtual void
    dump(std::basic_ostream<CharT, Traits> &__s) const = 0;

    // Deserialize the token from the specified input stream.
    virtual void
    load(std::basic_istream<CharT, Traits> &__s) const = 0;

    // Free the resources occupied by the token.
    virtual
    ~basic_value() { }
};


} // namespace bencode

#endif // INCLUDE_bencode_basic_value_hpp__
