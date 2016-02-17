#ifndef INCLUDE_bencode_token_string_hpp__
#define INCLUDE_bencode_token_string_hpp__

#include <memory>
#include <string>

#include <bencode/token/basic_token.hpp>


namespace bencode {
namespace token {

template< typename CharT, typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT> >
class basic_string : public basic_token<CharT, Traits> {
private:
    std::basic_string<CharT, Traits, Allocator> value;

public:
    basic_string(const basic_string &token)
    : value(token.value) { }

    basic_string(std::basic_string<CharT, Traits, Allocator> s)
    : value(s) { }

    ~basic_string() { }

    // Serialie the basic_string token to the specified output stream.
    void dump(std::basic_ostream<CharT, Traits> &s)
    {
        s << this->value.length() << ":" << this->value;
    }

    // Deserialize the basic_string token from the specified input stream.
    void load(std::basic_istream<CharT, Traits> &s)
    {
        // TBD
    }

};


typedef basic_string<char> string;


typedef basic_string<wchar_t> wstring;


} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_string_hpp__
