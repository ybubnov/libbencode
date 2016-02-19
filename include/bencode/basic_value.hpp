#ifndef INCLUDE_bencode_token_basic_value_hpp__
#define INCLUDE_bencode_token_basic_value_hpp__

#include <istream>
#include <ostream>
#include <string>


namespace bencode {
namespace token {


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
// An abstract class for Bencode tokens.
class basic_value {
public:
    // Serialie the token to the specified output stream.
    virtual void dump(std::basic_ostream<CharT, Traits> &s) = 0;

    // Deserialize the token from the specified input stream.
    virtual void load(std::basic_istream<CharT, Traits> &s) = 0;

    // Free the resources occupied by the token.
    virtual ~basic_value() { }
};


} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_basic_value_hpp__
