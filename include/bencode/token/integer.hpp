#ifndef INCLUDE_bencode_token_integer_hpp__
#define INCLUDE_bencode_token_integer_hpp__

#include <bencode/token/basic_token.hpp>


namespace bencode {
namespace token {

template<typename CharT,
         typename Traits>
class integer_token : public basic_token<CharT, Traits> {
private:
    long long value;

public:
    integer_token(const integer_token &token) : value(token.value) { }

    integer_token(long long i) : value(i) { }

    // Serialize the integer token to the specified output stream.
    void dump(std::base_ostream<CharT, Traits> &s) {
        s << "i" << value << "e";
    }

    // Deserialize the integer token from the specified input stream.
    void load(std::base_istream<CharT, Traits> &s) {
        // TBD
    }
};


template<typename CharT,
         typename Traits>
basic_token<CharT, Traits> integer(long long i) {
    return integer_token(i);
}

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_integer_hpp__
