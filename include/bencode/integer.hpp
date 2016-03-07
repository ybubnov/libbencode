#ifndef INCLUDE_bencode_integer_hpp__
#define INCLUDE_bencode_integer_hpp__

#include <iterator>
#include <sstream>
#include <bencode/algorithm.hpp>
#include <bencode/value.hpp>


namespace bencode
{


template
< typename CharT
, typename IntT
, typename Traits
> class basic_integer : public basic_value<CharT, Traits>
{
private:
    using basic_value_type = basic_value<CharT, Traits>;

    using value_type = IntT;

public:
    basic_integer(const basic_value_type& __value)
    {
        auto __integer = dynamic_cast<
            const basic_integer&>(__value);
        _M_value = __integer._M_value;
    }

    basic_integer(const basic_integer& __i)
    : _M_value(__i._M_value)
    { }

    basic_integer(value_type __i = 0)
    : _M_value(__i)
    { }

    ~basic_integer()
    { }

    // Serialize the integer value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    { __s << basic_value_type::integer_token << _M_value
        << basic_value_type::end_token; }

    // Deserialize the integer value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &__s)
    {
        // We must ensure that subsequent actions will be performed
        // for very likely integer value, otherwise and exception
        // should be raised.
        if (__s.peek() != basic_value_type::integer_token) {
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
            return !__s.eof() && __ch != basic_value_type::end_token;
        }, basic_value_type::integer_length);

        // Covert the value from the string into the integer.
        __i >> _M_value;

        // The "e" symbol should be already extracted at this moment,
        // so validate that the iterator pointing right to it.
        if (*__result != basic_value_type::end_token) {
            std::ostringstream __error;

            __error << "bencode::integer::load the end of the integer "
                "`e` expected, but `" << CharT(*__result) << "` found\n";
            throw encoding_error(__error.str());
        }

        // Validate that decoded value is an actual integer.
        if (!_M_value && __i.str() != std::basic_string<
                CharT, Traits>(1, CharT('0'))) {
            std::ostringstream __error;

            __error << "bencode::integer::load the specified "
                "value is not a number\n";
            throw value_error(__error.str());
        }
    }

    operator
    value_type() const
    { return _M_value; }

    bool
    operator==(const basic_integer& __i) const noexcept(true)
    { return _M_value == __i._M_value; }

    bool
    operator==(const value_type __i) const noexcept(true)
    { return _M_value == __i; }

    friend std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& __s,
        const basic_integer& __i)
    { __s << __i._M_value; return __s; }

private:
    value_type _M_value;
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode

#endif // INCLUDE_bencode_integer_hpp__
