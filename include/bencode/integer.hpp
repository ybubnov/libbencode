#ifndef INCLUDE_bencode_integer_hpp__
#define INCLUDE_bencode_integer_hpp__

#include <bencode/basic_value.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
class basic_integer : public basic_value<CharT, Traits>
{
private:
    typedef basic_value<CharT, Traits> _Value;

    long long value;

public:
    basic_integer()
    : value(0) { }

    basic_integer(const basic_integer &__i)
    : value(__i.value) { }

    basic_integer(long long __i)
    : value(__i) { }

    ~basic_integer() { }

    // Serialize the integer value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    { __s << _Value::int_type << value << _Value::end_type; }

    // Deserialize the integer value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &__s) const
    {
        if s.peek() != _Value::int_type {
            throw type_error(
                "specified stream does not contain parsable "
                "bencode integer value");
        }
    }

    operator
    long long() const
    { return this->value; }
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode

#endif // INCLUDE_bencode_integer_hpp__
