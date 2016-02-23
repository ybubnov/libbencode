#ifndef INCLUDE_bencode_integer_hpp__
#define INCLUDE_bencode_integer_hpp__

#include <iterator>
#include <bencode/basic_value.hpp>


namespace bencode
{


template
< typename CharT
, typename Traits = std::char_traits<CharT> >
class basic_integer : public basic_value<CharT, Traits>
{
private:
    typedef basic_value<CharT, Traits> _Value;

    typedef long long value_type;

    value_type _M_value;

public:
    basic_integer()
    : _M_value(0) { }

    basic_integer(const basic_integer &__i)
    : _M_value(__i._M_value) { }

    basic_integer(long long __i)
    : _M_value(__i) { }

    ~basic_integer() { }

    // Serialize the integer value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    { __s << _Value::int_type << _M_value << _Value::end_type; }

    // Deserialize the integer value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &__s) const
    {
        // We must ensure that subsequent actions will be performed
        // for very likely integer value, otherwise and exception
        // should be raised.
        if (__s.peek() != _Value::int_type) {
            throw type_error(
                "bencode::integer::load the specified stream does "
                "not contain interpretable bencode integer value\n");
        }

        // Read the leading "i" symbol from the provided stream.
        __s.get();

        // Define the integer symbol representation placeholder.
        std::basic_stringstream<CharT, Traits> __intval;

        // Define the stream iterator to read the integer value.
        auto __iter = std::istream_iterator<CharT, CharT, Traits>(__s);

        // Copy the values from the input stream into the integer
        // placeholder string stream.
        for (; *__iter != _Value::end_type; __iter++, __intval++)
        { *__intval = *__iter; }

        // Covert the value from the string
        __intval >> _M_value;

        // Read the trailing "e" symbol from the provided stream.
        if (__s.peek() != _Value::end_type) {
            std::ostringstream __error(
                "bencode::integer::load the end of the integer `e` "
                "expected, but `");

            __error << __s.peek() << "` found\n";
            throw encoding_error(__error);
        }

        // Extract the "e" symbol from the stream all
        // validations where succeeded.
        __s.get();
    }

    operator
    value_type() const
    { return _M_value; }
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode

#endif // INCLUDE_bencode_integer_hpp__
