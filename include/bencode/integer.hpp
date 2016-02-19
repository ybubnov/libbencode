#ifndef INCLUDE_bencode_token_integer_hpp__
#define INCLUDE_bencode_token_integer_hpp__

#include <string>
#include <bencode/basic_value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
class basic_integer : public basic_value<CharT, Traits>
{
private:
    long long value;

public:
    basic_integer(const basic_integer &token)
    : value(token.value) { }

    basic_integer(long long i)
    : value(i) { }

    ~basic_integer() { }

    // Serialize the integer token to the specified output stream.
    void dump(std::basic_ostream<CharT, Traits> &s)
    {
        s << "i" << value << "e";
    }

    // Deserialize the integer token from the specified input stream.
    void load(std::basic_istream<CharT, Traits> &s)
    {
        // TBD
    }
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode


#endif // INCLUDE_bencode_token_integer_hpp__
