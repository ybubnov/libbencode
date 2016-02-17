#ifndef INCLUDE_bencode_token_basic_token_hpp__
#define INCLUDE_bencode_token_basic_token_hpp__

#include <istream>
#include <ostream>
#include <string>


namespace bencode {
namespace token {

template< typename CharT, typename Traits = std::char_traits<CharT> >
// An abstract class for Bencode tokens.
class basic_token {
public:
    // Serialie the token to the specified output stream.
    virtual void dump(std::basic_ostream<CharT, Traits> &s) = 0;

    // Deserialize the token from the specified input stream.
    virtual void load(std::basic_istream<CharT, Traits> &s) = 0;

    // Free the resources occupied by the token.
    virtual ~basic_token() { }
};


template<typename CharT, typename Traits>
using _Token = basic_token<CharT, Traits>;

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_basic_token_hpp__
