#ifndef INCLUDE_bencode_token_string_hpp__
#define INCLUDE_bencode_token_string_hpp__

#include <memory>
#include <string>
#include <bencode/basic_value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, typename Allocator = std::allocator<CharT> >
class basic_string : public basic_value<CharT, Traits> {
private:
    typedef std::basic_string<CharT, Traits, Allocator> _String_type;

    typedef typename _String_type::iterator iterator;

    typedef typename _String_type::const_iterator const_iterator;

    _String_type value;

public:
    basic_string(const basic_string &__string)
    : value(__string.value) { }

    basic_string(std::basic_string<CharT, Traits, Allocator> __s)
    : value(__s) { }

    basic_string(const CharT *__chars)
    : value(__chars) { }

    ~basic_string() { }

    // Serialie the basic_string token to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &s) const
    { s << this->value.length() << ":" << this->value; }

    // Deserialize the basic_string token from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &s) const
    { /* TDB */ }

    iterator
    begin()
    { return this->value.begin(); }

    const_iterator
    cbegin() const
    { return this->value.cbegin(); }

    const_iterator
    cend() const
    { return this->value.cend(); }
};


typedef basic_string<char> string;


typedef basic_string<wchar_t> wstring;


} // namespace bencode


#endif // INCLUDE_bencode_token_string_hpp__
