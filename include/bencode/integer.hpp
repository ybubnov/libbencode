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

public:
    /**
     *  @brief Internal integer type.
     */
    using value_type = IntT;

    /**
     *  @brief Construct an integer using downcasted reference to the
     *         basic type.
     *  @param __value  Reference to the basic type.
     */
    basic_integer(const basic_value_type& __value)
    {
        auto __integer = dynamic_cast<const basic_integer&>(__value);
        _M_value = __integer._M_value;
    }

    /**
     *  @brief Construct an integer using downcasted pointer to the
     *         basic type.
     *  @param __ptr  Shared pointer to the basic type.
     *
     *  The pointer should not be equal to `nullptr`, it will not be checked.
     */
    basic_integer(const std::shared_ptr<basic_value_type>& __ptr)
    : basic_integer(*__ptr)
    { }

    /**
     *  @brief Construct an integer as a copy of a @int.
     *  @param __i  Source integer.
     */
    basic_integer(const basic_integer& __i)
    : _M_value(__i._M_value)
    { }

    /**
     *  @brief Construct an integer initialized by specified value.
     *  @param __i  Source integer value.
     */
    basic_integer(value_type __i = 0)
    : _M_value(__i)
    { }

    ~basic_integer()
    { }

    /**
     *  @brief Serialize the integer value to the specified output stream.
     *  @param __s  Reference to the input stream.
     */
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    { __s << basic_value_type::integer_token << _M_value
        << basic_value_type::end_token; }

    /**
     *  @brief Deserialize the integer value from the specified input stream.
     *  @param __s  Reference to the input stream.
     */
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

    /**
     *  @brief Convert to the underlying integer type.
     *
     *  Returns the copy of the internal representation of the integer.
     */
    operator
    value_type() const
    { return _M_value; }

    /**
     *  @brief Test the equivalence of the integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is equal to this one, False
     *  otherwise.
     */
    bool
    operator==(const basic_integer& __i) const noexcept(true)
    { return _M_value == __i._M_value; }

    /**
     *  @brief Test the equivalence of the integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is equal to this one, False
     *  otherwise.
     */
    bool
    operator==(const value_type __i) const noexcept(true)
    { return _M_value == __i; }

    /**
     *  @brief Test the non-equivalence of the integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is not equal to this one,
     *  False otherwise.
     */
    bool
    operator!=(const basic_integer& __i) const noexcept(true)
    { return _M_value != __i._M_value; }

    /**
     *  @brief Test the non-equivalence of the integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is not equal to this one,
     *  False otherwise.
     */
    bool
    operator!=(const value_type __i) const noexcept(true)
    { return _M_value != __i; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is less than this one,
     *  False otherwise.
     */
    bool
    operator>(const basic_integer& __i) const noexcept(true)
    { return _M_value > __i._M_value; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is less than this one,
     *  False otherwise.
     */
    bool
    operator>(const value_type __i) const noexcept(true)
    { return _M_value > __i; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is more than this one,
     *  False otherwise.
     */
    bool
    operator<(const basic_integer& __i) const noexcept(true)
    { return _M_value < __i._M_value; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is more than this one,
     *  False otherwise.
     */
    bool
    operator<(const value_type __i) const noexcept(true)
    { return _M_value < __i; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is less or equal than
     *  this one, False otherwise.
     */
    bool
    operator>=(const basic_integer& __i) const noexcept(true)
    { return _M_value >= __i._M_value; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is less or equal than
     *  this one, False otherwise.
     */
    bool
    operator>=(const value_type __i) const noexcept(true)
    { return _M_value >= __i; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is more or equal than
     *  this one, False otherwise.
     */
    bool
    operator<=(const basic_integer& __i) const noexcept(true)
    { return _M_value <= __i._M_value; }

    /**
     *  @brief Compare two integers.
     *  @param __i  Source integer.
     *
     *  Returns True if the specified integer is more or equal than
     *  this one, False otherwise.
     */
    bool
    operator<=(const value_type __i) const noexcept(true)
    { return _M_value <= __i; }

private:
    value_type _M_value;
};


typedef basic_integer<char> integer;


typedef basic_integer<wchar_t> winteger;


} // namespace bencode

#endif // INCLUDE_bencode_integer_hpp__
