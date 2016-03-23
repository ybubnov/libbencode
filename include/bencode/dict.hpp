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

    // Define the shared pointer type of basic values.
    using value_ptr_type = std::shared_ptr<basic_value_type>;

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
    /**
     *  @brief Key-value pair for the dict container.
     */
    using value_type = std::pair<const key_type, value_ptr_type>;

    /**
     *  @brief Dict container key-value pairs allocator.
     */
    using allocator_type = Allocator<value_type>;

    /**
     *  @brief Lexicographical map comparator type.
     *
     *  According to the Bencode specification the key in the associative
     *  list should be sorted in the lexicographical order, therefore it
     *  should denied for the user to specify the custom comparator object.
     */
    using comparator_type = lexicographical_compare<key_type>;

    /**
     *  @brief Dictionary container type to keep the map of the Bencode values.
     */
    using container_type = DictContainer<key_type, value_ptr_type,
        comparator_type, allocator_type>;

    /**
     *  @brief Unsigned integral type of the dictionary size.
     */
    using size_type = typename container_type::size_type;

    /**
     *  @brief Mutable elements iterator.
     */
    using iterator = typename container_type::iterator;

    /**
     *  @brief Immutable (constant) elements iterator.
     */
    using const_iterator = typename container_type::const_iterator;

    /**
     *  @brief Construct an empty dictionary.
     */
    basic_dict()
    { }

    /**
     *  @brief Constuct a dictionary using downcasted reference to the
     *         basic type.
     *  @param __value  Reference to the basic type.
     */
    basic_dict(const basic_value_type& __value)
    {
        auto __dict = dynamic_cast<const basic_dict&>(__value);
        _M_container = container_type(__dict._M_container);
    }

    /**
     *  @brief Construct a dictionary using downcasted pointer to the basic type.
     *  @param __ptr  Shared pointer to the basic type.
     *
     *  The pointer should not be equal to `nullptr`, it will not be checked.
     */
    basic_dict(const std::shared_ptr<basic_value_type>& __ptr)
    : basic_dict(*__ptr)
    { }

    /**
     *  @brief Construct a dictionary using the initializer list.
     *  @param __list  List of elements
     */
    basic_dict(std::initializer_list<value_type> __list)
    : _M_container(__list.begin(), __list.end())
    { }

    /**
     *  @brief Construct a dictionary from the range.
     *  @param __first  First element of the range
     *  @param __last   Last element of the range.
     */
    basic_dict(const_iterator __first, const_iterator __last)
    : _M_container(__first, __last)
    { }

    ~basic_dict()
    { }

    /**
     *  @brief Serialize the dictionary value to the specified output stream.
     *  @param __s  Reference to the output stream.
     */
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

    /**
     *  @brief Deserialize the dictionary value from the specified
     *         input stream.
     *  @param __s  Reference to the input stream.
     */
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

    /**
     *  @brief Iterator to the first element.
     *
     *  Returns read-write iterator that points to the first element in
     *  the %dict.
     */
    iterator
    begin()
    { return _M_container.begin(); }

    /**
     *  @brief Iterator one past the last element.
     *
     *  Return read/write iterator that point to the past the last element
     *  in the %dict.
     */
    iterator
    end()
    { return _M_container.end(); }

    /**
     *  @brief Constant iterator to the first element.
     *
     *  Returns read-only iterator that point to the first element in
     *  the %dict.
     */
    const_iterator
    cbegin()
    { return _M_container.cbegin(); }

    /**
     *  @brief Constant iterator to one past the last element.
     *
     *  Returns read-only iterator that points to the past the last element
     *  in the %dict.
     */
    const_iterator
    cend()
    { return _M_container.cend(); }

    /**
     *  @brief Subscript access to the data container in the %dict.
     *  @param __key  The key of the element for which data should be
     *                accessed.
     *  @return  Read/write reference to the data.
     */
    value_ptr_type&
    operator[](const CharT* __key)
    { return _M_container.operator[](key_type(__key)); }

    /**
     *  @brief Insert element into the container, if the container does not
     *         already contain an element with an equivalent key.
     *  @param __value  Element value to insert.
     */
    std::pair<iterator, bool>
    insert(const value_type& __value)
    { return _M_container.insert(__value); }

    /**
     *  @brief Removes the specified element from the container.
     *  @param __pos  Mutable iterator to the element to remove.
     */
    void
    erase(iterator __pos)
    { _M_container.erase(__pos); }

    /**
     *  @brief Removes the specified element from the container.
     *  @param __pos  Immutable iterator to the element to remove.
     */
    void
    erase(const_iterator __pos)
    { _M_container.erase(__pos); }

    /**
     *  @brief Returns the number of elements in the container.
     */
    size_type
    size()
    { return _M_container.size(); }

private:
    // The associative list of the key-value pairs.
    container_type _M_container;
};


typedef basic_dict<char> dict;


typedef basic_dict<wchar_t> wdict;


} // namespace bencode

#endif // INCLUDE_bencode_dict_hpp__
