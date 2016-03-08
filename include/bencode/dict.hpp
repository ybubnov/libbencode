#ifndef INCLUDE_bencode_dict_hpp__
#define INCLUDE_bencode_dict_hpp__

#include <utility>
#include <bencode/string.hpp>
#include <bencode/value.hpp>


namespace bencode
{


template
< typename CharT
, typename IntT
, typename Traits
, template
< typename T
> class Allocator
, template
< typename Key
, typename T
, typename... Args
> class DictContainer
, template
< typename T
, typename... Args
> class ListContainer
> class basic_dict : public basic_value<CharT, Traits>
{
private:
    // Define the dict key alias.
    using key_type = basic_string<CharT, Traits, Allocator>;

    // Define the dict value alias.
    using basic_value_type = basic_value<CharT, Traits>;

    using value_ptr_type = std::shared_ptr<basic_value_type>;

    // Define the key-value pair for the dict container.
    using value_type = std::pair<const key_type, value_ptr_type>;

    // Define the dict container key-value pairs allocator.
    using allocator_type = Allocator<value_type>;

    // Define the lexicographical comparator as a wrapper
    // around the STL function.
    template <typename _T>
    struct lexicographical_compare
    {
        bool
        operator()(const _T& lhs, const _T& rhs)
        {
            return std::lexicographical_compare(
                lhs.cbegin(), lhs.cend(),
                rhs.cbegin(), rhs.cend());
        }
    };

public:
    // Define the map comparator. According to the Bencode
    // specification the key in the associative list should
    // be sorted in the lexicographical order, therefore
    // it should denied for the user to specify the custom
    // comparator object.
    using comparator_type = lexicographical_compare<key_type>;

    // Define the dict container type to keep the map
    // of the Bencode values.
    using container_type = DictContainer<key_type, value_ptr_type,
        comparator_type, allocator_type>;

    // Define the constant iterator as a functional
    // equivalent to the container constant iterator.
    using iterator = typename container_type::iterator;

    // Define the mutable iterator as a functional
    // equivalent to the container mutable iterator.
    using const_iterator = typename container_type::const_iterator;

    basic_dict()
    { }

    basic_dict(const basic_value_type& __value)
    {
        auto __dict = dynamic_cast<const basic_dict&>(__value);
        _M_container = container_type(__dict._M_container);
    }

    basic_dict(const std::shared_ptr<basic_value_type>& __ptr)
    : basic_dict(*__ptr)
    { }

    basic_dict(std::initializer_list<value_type> __list)
    : _M_container(__list.begin(), __list.end())
    { }

    ~basic_dict()
    { }

    // Serialize the dictionary value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits> &__s) const
    {
        __s << basic_value_type::dict_token;

        std::for_each(_M_container.cbegin(), _M_container.cend(),
            [&__s](const value_type& value) {

            // To prevent access to the memory by null pointer
            // validate that the object is valid first.
            if (value.second != nullptr) {
                value.first.dump(__s);
                __s << basic_value_type::delimiter_token;
                value.second->dump(__s);
            }
        });

        __s << basic_value_type::end_token;
    }

    // Deserialize the dictionary value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits> &__s)
    {
        if (__s.peek() != basic_value_type::dict_token) {
            throw type_error(
                "bencode::dict::load the specified stream does not "
                "contain interpretable bencode dictionary value\n");
        }

        // Read the "d" symbol from the provided stream.
        __s.get();

        // At the next step we are going to decode the items
        // of the Bencoded dictionary.
        while (!__s.eof() && __s.peek() != basic_value_type::end_token) {
            // Read the key of the next dictionary item.
            key_type __key;

            // Extract the string key from the input stream.
            __key.load(__s);

            // Ensure that key is separated from the value
            // with the delimiter token, and throw an error
            // otherwise.
            if (__s.peek() != basic_value_type::delimiter_token) {
                std::ostringstream __error;

                __error << "bencode::dict::load after the key a `:` "
                    "delimiter expected, but `" << CharT(__s.peek())
                    << "` found\n";
                throw encoding_error(__error.str());
            }

            // Extract the delimiter symbol from the input
            // stream.
            __s.get();

            // Decode the value of the dictionary item.
            auto __value = make_value<__bencode_dict_typenames>(__s);

            // Insert a new element into the dictionary.
            _M_container.insert(value_type(__key, __value));

            // Force read the next symbols from the input stream.
            __s.peek();
        }

        // Ensure that all those operations where not performed
        // for nothing, and check that the stream is pointing to
        // the end token.
        if (__s.peek() != basic_value_type::end_token) {
            std::ostringstream __error;

            __error << "bencode::dict::load the end of the dictionary "
                "`e` expected, but `" << CharT(__s.peek()) << "` found\n";
            throw encoding_error(__error.str());
        }

        // Read the "e" symbol from the input stream.
        __s.get();
    }

    void
    insert(std::initializer_list<value_type> __list)
    { _M_container.insert(__list.begin(), __list.cend()); }

    std::pair<iterator, bool>
    insert(const value_type& __value)
    { return _M_container.insert(__value); }

    iterator
    begin()
    { return _M_container.begin(); }

    iterator
    end()
    { return _M_container.end(); }

    const_iterator
    cbegin()
    { return _M_container.cbegin(); }

    const_iterator
    cend()
    { return _M_container.cend(); }

    value_ptr_type&
    operator[](const CharT* __key)
    { return _M_container.operator[](key_type(__key)); }

private:
    // The associative list of the key-value pairs.
    container_type _M_container;
};


typedef basic_dict<char> dict;


typedef basic_dict<wchar_t> wdict;


} // namespace bencode

#endif // INCLUDE_bencode_dict_hpp__
