#ifndef INCLUDE_bencode_string_hpp__
#define INCLUDE_bencode_string_hpp__

#include <iterator>
#include <sstream>
#include <bencode/basic_value.hpp>


namespace bencode
{


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
> class basic_string : public basic_value<CharT, Traits> {
private:
    typedef basic_value<CharT, Traits> _Value;

    typedef Allocator<_Value> _Alloc;

    typedef std::basic_string<CharT, Traits, _Alloc> _String_type;

    typedef typename _String_type::iterator iterator;

    typedef typename _String_type::const_iterator const_iterator;

    _String_type _M_value;

public:
    basic_string() { }

    basic_string(const basic_string &__string)
    : _M_value(__string._M_value) { }

    basic_string(const _String_type& __s)
    : _M_value(__s) { }

    basic_string(const CharT *__chars)
    : _M_value(__chars) { }

    ~basic_string() { }

    // Serialie the basic_string value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    { __s << _M_value.length() << _Value::delim_type << _M_value; }

    // Deserialize the basic_string value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &__s)
    {
        // Define the integer symbol representation placeholder.
        std::basic_stringstream<CharT, Traits> __i;

        // Define the input stream iterator of the provided stream to
        // be able to read the string length value symbol by symbol.
        auto __si = std::istream_iterator<CharT, CharT, Traits>(__s);

        // Define the output stream to as a buffer for the integer
        // value, which will be later converted.
        auto __ival = std::ostream_iterator<CharT, CharT, Traits>(__i);

        // Copy the symbols from the input stream to the integer
        // placeholder until the ":" delimiter value.
        auto __result = copy_until(__si, __ival,
            [&__s](const CharT& __ch) {

            // Additionally, check that we did not exceed the
            // length of the stream to prevent hangs.
            return !__s.eof() && __ch != _Value::delim_type;
        }, _Value::int_length);

        if (*__result != _Value::delim_type) {
            std::ostringstream __error;

            __error << "bencode::string::load the delimiter `:` "
                " expected, but `" << CharT(*__result) << "` found\n";
            throw encoding_error(__error.str());
        }

        // Save the length of the string.
        long long __count;
        __i >> __count;

        if (__count < 0) {
            std::ostringstream __error;

            __error << "bencode::string::load the length of the string "
                "value must be a positive: `" << __count << "`\n";
            throw encoding_error(__error.str());
        }

        // Allocate the array of symbols of the specified string length.
        std::unique_ptr<CharT[]> __str(new CharT[__count+1]);

        // Read the string value into the symbol array.
        __s.get(__str.get(), std::streamsize(__count+1));

        // Initialize the internal value with a new string.
        _M_value = _String_type(__str.get());
    }

    iterator
    begin()
    { return _M_value.begin(); }

    iterator
    end()
    { return _M_value.end(); }

    const_iterator
    cbegin() const
    { return _M_value.cbegin(); }

    const_iterator
    cend() const
    { return _M_value.cend(); }

    operator
    std::basic_string<CharT, Traits>() const
    { return _M_value; }
};


typedef basic_string<char> string;


typedef basic_string<wchar_t> wstring;


} // namespace bencode

#endif // INCLUDE_bencode_string_hpp__
