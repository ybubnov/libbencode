#ifndef INCLUDE_bencode_token_string_hpp__
#define INCLUDE_bencode_token_string_hpp__

#include <string>

#include <bencode/token/basic_token.hpp>


namespace bencode {
namespace token {

template<typename CharT,
         typename Traits,
         typename Allocator>
class string_token : public basic_token<CharT, Traits> {
private:
    std::basic_string<CharT, Traits, Allocator> value;


public:
    string_token(const string_token &token) : value(token.value) { }

    string_token(std::basic_string<CharT, Traits, Allocator> &s) : value(s) { }

    // Serialie the string token to the specified output stream.
    void dump(std::base_ostream<CharT, Traits> &s) {
        s << this->value.length() << ":" << this->value;
    }

    // Deserialize the string token from the specified input stream.
    void load(std::base_istream<CharT, Traits> &s) {
        // TBD
    }

};


// Create a new instance of the string token.
template<typename CharT
         typename Traits
         typename Allocator>
basic_token<CharT, Traits> string(
        std::basic_string<CharT, Traits, Allocator> s) {
    return string_token(s);
}

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_string_hpp__
