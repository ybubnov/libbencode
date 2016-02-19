#ifndef INCLUDE_bencode_token_basic_value_hpp__
#define INCLUDE_bencode_token_basic_value_hpp__

#include <exception>
#include <istream>
#include <ostream>
#include <string>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
// An abstract class for Bencode tokens.
class basic_value {
private:
    typedef typename Traits::int_type int_type;

protected:
    void ensure(std::basic_istream<CharT, Traits> &__s, int_type __c) const
    {
        const auto c = __s.peek();
        if (c != __c) {
            // TODO: implement the exception class
            throw "invalid type";
        }
    }

public:
    // Serialie the token to the specified output stream.
    virtual void
    dump(std::basic_ostream<CharT, Traits> &s) const = 0;

    // Deserialize the token from the specified input stream.
    virtual void
    load(std::basic_istream<CharT, Traits> &s) const = 0;

    // Free the resources occupied by the token.
    virtual
    ~basic_value() { }
};


} // namespace bencode


#endif // INCLUDE_bencode_token_basic_value_hpp__
