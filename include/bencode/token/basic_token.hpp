#ifndef INCLUDE_bencode_token_basic_token_hpp__
#define INCLUDE_bencode_token_basic_token_hpp__

#include <istream>
#include <ostream>


namespace bencode {
namespace token {

// An abstract class for Bencode tokens.
template<typename CharT,
         typename Traits>
class basic_token {
public:
    // Serialie the token to the specified output stream.
    virtual void dump(std::base_ostream<CharT, Traits> &s) = 0;

    // Deserialize the token from the specified input stream.
    virtual void load(std::base_istream<CharT, Traits> &s) = 0;

    // Free the resources occupied by the token.
    virtual ~basic_token() = 0;
};

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_basic_token_hpp__
