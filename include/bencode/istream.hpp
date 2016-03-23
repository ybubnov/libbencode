#ifndef INCLUDE_bencode_istream_hpp__
#define INCLUDE_bencode_istream_hpp__

#include <istream>
#include <streambuf>
#include <bencode/value.hpp>


namespace bencode {


/**
 *  @brief Template class basic_istream.
 *
 *  @tparam CharT   Character type, defaults to `char`.
 *  @tparam Traits  Traits for character type, defaults to
 *                  `std::char_traits<CharT>`.
 *
 *  An input stream class with support of reading Bencode values.
 */
template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_istream
: public std::basic_istream<CharT, Traits>
{
protected:
    // Define the basic value type alias.
    using basic_value_type = basic_value<CharT, Traits>;

public:
    /**
     *  @brief Construct an input stream using stream buffer.
     *  @param __sb  Source stream buffer.
     */
    explicit
    basic_istream(std::basic_streambuf<CharT, Traits>* __sb)
    : std::basic_istream<CharT, Traits>(__sb)
    { }

    /**
     *  @brief Read the Bencode value from the input stream.
     *  @parmam __v  Source Bencode value.
     */
    basic_istream&
    get(basic_value_type& __v)
    { __v.load(*this); return *this; }

    /**
     *  @brief Read the Bencode value from the input stream.
     *  @parmam __v  Source Bencode value.
     */
    basic_istream&
    operator>>(basic_value_type& __v)
    { return get(__v); }
};


typedef basic_istream<char> istream;


typedef basic_istream<wchar_t> wistream;


} // namespace bencode

#endif // INCLUDE_bencode_istream_hpp__
