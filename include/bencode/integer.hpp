#ifndef INCLUDE_bencode_integer_hpp__
#define INCLUDE_bencode_integer_hpp__

#include <iterator>
#include <sstream>
#include <bencode/algorithm.hpp>
#include <bencode/basic_value.hpp>
#include <bencode/typedef.hpp>


namespace bencode
{


template
< typename CharT
, typename Traits
> class basic_integer : public basic_value<CharT, Traits>
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
    load(std::basic_istream<CharT, Traits> &__s)
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
        std::basic_stringstream<CharT, Traits> __i;

        // Define the input stream iterator of the provided stream to
        // be able to read the integer value symbol by symbol.
        auto __si = std::istream_iterator<CharT, CharT, Traits>(__s);

        // Define the output stream to as a buffer for the integer
        // value, which will be later converted.
        auto __ival = std::ostream_iterator<CharT, CharT, Traits>(__i);

        // Copy the values from the input stream into the integer
        // placeholder string stream.
        auto __result = copy_until(__si, __ival,
            [&__s](const CharT& __ch) {

            // Additionally, check that we did not exceed the
            // length of the stream to prevent hangs.
            return !__s.eof() && __ch != _Value::end_type;
        }, _Value::int_length);

        // Covert the value from the string into the integer.
        __i >> _M_value;

        // The "e" symbol should be already extracted at this moment,
        // so validate that the iterator pointing right to it.
        if (*__result != _Value::end_type) {
            std::ostringstream __error;

            __error << "bencode::integer::load the end of the integer "
                "`e` expected, but `" << CharT(*__result) << "` found\n";
            throw encoding_error(__error.str());
        }
    }

    operator
    value_type() const
    { return _M_value; }
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode

#endif // INCLUDE_bencode_integer_hpp__
