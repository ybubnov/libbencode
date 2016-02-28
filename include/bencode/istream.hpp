#ifndef INCLUDE_bencode_istream_hpp__
#define INCLUDE_bencode_istream_hpp__

#include <ostream>
#include <streambuf>
#include <bencode/value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_istream
{
protected:
    typedef basic_value<CharT, Traits> _Value;

    std::basic_istream<CharT, Traits> _M_istream;

public:
    explicit
    basic_istream(std::basic_streambuf<CharT, Traits>* sb)
    : _M_istream(sb) { }

    basic_istream&
    get(_Value &__v)
    { __v.load(_M_istream); return *this; }

    basic_istream&
    operator>>(_Value &__v)
    { return get(__v); }

    // Synchronizes the input buffer with the associated data source.
    int
    sync()
    { return _M_istream.sync(); }
};


typedef basic_istream<char> istream;


typedef basic_istream<wchar_t> wistream;


} // namespace bencode

#endif // INCLUDE_bencode_istream_hpp__
