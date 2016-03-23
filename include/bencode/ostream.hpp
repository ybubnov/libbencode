#ifndef INCLUDE_bencode_ostream_hpp__
#define INCLUDE_bencode_ostream_hpp__

#include <ostream>
#include <streambuf>
#include <bencode/value.hpp>


namespace bencode {


/**
 *  @brief Template class basic_ostream.
 *
 *  @tparam CharT   Character type, defaults to `char`.
 *  @tparam Traits  Traits for character type, defaults to
 *                  `std::char_traits<CharT>`.
 *
 *  An output stream class with support of writing Bencode values.
 */
template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_ostream
: public std::basic_ostream<CharT, Traits>
{
protected:
    // Define the basic value type alias.
    using basic_value_type = basic_value<CharT, Traits>;

public:
    /**
     *  @brief Construct an output stream using stream buffer.
     *  @param __sb  Source stream buffer.
     */
    explicit
    basic_ostream(std::basic_streambuf<CharT, Traits>* __sb)
    : std::basic_ostream<CharT, Traits>(__sb)
    { }
    /**
     *  @brief Write the Bencode value into the output stream.
     *  @param __v  Source Bencode value.
     */
    basic_ostream&
    put(const basic_value_type& __v)
    { __v.dump(*this); return *this; }

    /**
     *  @brief Write the Bencode value into the output stream.
     *  @param __v  Source Bencode value.
     */
    basic_ostream&
    operator<<(const basic_value_type& __v)
    { return put(__v); }
};


typedef basic_ostream<char> ostream;


typedef basic_ostream<wchar_t> wostream;


} // namespace bencode

#endif // INCLUDE_bencode_ostream_hpp__
