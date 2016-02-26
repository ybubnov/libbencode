#ifndef INCLUDE_bencode_ostream_hpp__
#define INCLUDE_bencode_ostream_hpp__

#include <ostream>
#include <streambuf>
#include <bencode/basic_value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_ostream
{
protected:
    typedef basic_value<CharT, Traits> _Value;

    std::basic_ostream<CharT, Traits> _M_ostream;

public:
    explicit
    basic_ostream(std::basic_streambuf<CharT, Traits>* sb)
    : _M_ostream(sb) { }

    basic_ostream&
    put(const _Value &__v)
    { __v.dump(_M_ostream); return *this; }

    basic_ostream&
    operator<<(const _Value &__v)
    { return put(__v); }

    // Writes uncommitted changes to the underlying output sequence.
    basic_ostream&
    flush()
    { _M_ostream.flush(); return *this; }
};


typedef basic_ostream<char> ostream;


typedef basic_ostream<wchar_t> wstream;


} // namespace bencode

#endif // INCLUDE_bencode_ostream_hpp__
