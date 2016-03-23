#ifndef INCLUDE_bencode_list_hpp__
#define INCLUDE_bencode_list_hpp__

#include <algorithm>
#include <iterator>
#include <sstream>
#include <initializer_list>
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
< typename T
, typename... Args
> class ListContainer
, template
< typename Key
, typename T
, typename... Args
> class DictContainer
> class basic_list: public basic_value<CharT, Traits>
{
private:
    // Define the list value alias.
    using basic_value_type = basic_value<CharT, Traits>;

    using value_ptr_type = std::shared_ptr<basic_value_type>;

public:
    /**
     *  @brief List container allocator for the values.
     */
    using allocator_type = Allocator<value_ptr_type>;

    /**
     *  @brief List container type of the shared pointers to bencode values.
     */
    using container_type = ListContainer<value_ptr_type, allocator_type>;

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
     *  @brief Construct an empty list.
     */
    basic_list()
    { }

    /**
     *  @brief Construct a list using downcasted reference to the basic type.
     *  @param __value  Reference to the basic type.
     */
    basic_list(const basic_value_type& __value)
    {
        auto __list = dynamic_cast<const basic_list&>(__value);
        // Explicitly copy the containers content.
        _M_container = container_type(__list._M_container);
    }

    /**
     *  @brief Construct a list using downcasted pointer to the basic type.
     *  @param __ptr  Shared pointer to the basic type.
     *
     *  The pointer should not be equal to `nullptr`, it will not be checked.
     */
    basic_list(const std::shared_ptr<basic_value_type&> __ptr)
    : basic_list(*__ptr)
    { }

    /**
     *  @brief Construct a list with pre-allocated count of elements.
     *  @param __count  Count to elements to allocate.
     */
    basic_list(std::size_t __count)
    :_M_container(__count)
    { }

    /**
     *  @brief Construct a list using the initializer list.
     *  @param __list  List of elements.
     */
    basic_list(std::initializer_list<value_ptr_type> __list)
    : _M_container(__list)
    { }

    /**
     *  @brief Construct a list from the range.
     *  @param __first  First element of the range.
     *  @param __last   Last element of the range.
     */
    basic_list(const_iterator __first, const_iterator __last)
    : _M_container(__first, __last)
    { }

    ~basic_list()
    { }

    /**
     *  @brief Serialize the list value to the specified output stream.
     *  @param __s  Reference to the output stream.
     */
    void
    dump(std::basic_ostream<CharT, Traits>& __s) const
    {
        __s << basic_value_type::list_token;

        std::for_each(_M_container.begin(), _M_container.end(),
            [&__s](value_ptr_type value) {

            if (value != nullptr) {
                value->dump(__s);
            }
        });

        __s << basic_value_type::end_token;
    }

    /**
     *  @brief Deserialize the list value from the specified input stream.
     *  @param __s  Reference to the input stream.
     */
    void
    load(std::basic_istream<CharT, Traits>& __s)
    {
        // Ensure that the stream is starting with the valid
        // list token, otherwise all subsequent actions will
        // make more damage.
        if (__s.peek() != basic_value_type::list_token) {
            throw type_error(
                "bencode::list::load the specified stream does "
                "not contain interpretable bencode list value\n");
        }

        // Read the "l" symbols from the provided stream.
        __s.get();

        // Decode the Bencode values one by one until the
        // end of the stream or the list token.
        while (!__s.eof() && __s.peek() != basic_value_type::end_token) {
            // Decode the value of the next list item.
            auto __value = make_value<__bencode_dict_typenames>(__s);

            // Append the decoded item to the list.
            _M_container.push_back(__value);

            // Force read the next symbol from the stream.
            __s.peek();
        }

        // Ensure that the list value is succefully de-serialized.
        if (__s.peek() != basic_value_type::end_token) {
            std::ostringstream __error;

            __error << "bencode::list::load the end of the list "
                "`e` expected, but `" << CharT(__s.peek()) << "` found\n";
            throw encoding_error(__error.str());
        }

        // Read the "e" symbol from the provided stream.
        __s.get();
    }

    /**
     *  @brief Iterator to the first element.
     *
     *  Returns read-write iterator that points to the first element in
     *  the %list.
     */
    iterator
    begin()
    { return _M_container.begin(); }

    /**
     *  @brief Iterator one past the last element.
     *
     *  Returs read-write iterator that points on past the last element
     *  in the %list.
     */
    iterator
    end()
    { return _M_container.end(); }

    /**
     *  @brief Constant iterator to the first element.
     *
     *  Returns read-only iterator that points to the first element in
     *  the %list.
     */
    const_iterator
    cbegin() const
    { return _M_container.cbegin(); }

    /**
     *  @brief Constant iterator to one past the last element.
     *
     *  Returns read-only iterator that points to one past the last
     *  element in the %list.
     */
    const_iterator
    cend() const
    { return _M_container.cend(); }

    /**
     *  @brief Subscript access to the data container in the %list.
     *  @param __index  The index of the element for which data should be
     *                  accessed.
     *  @return  Read/write reference to data.
     */
    value_ptr_type&
    operator[](std::size_t __index)
    { return _M_container.operator[](__index); }

    /**
     *  @brief Add data to the end of the %list.
     *  @param __value  Data to be added.
     *
     *  Push the provided element to the end of the list container.
     */
    iterator
    insert(const value_ptr_type& __value)
    { return _M_container.insert(_M_container.end(), __value); }

    /**
     *  @brief Inserts elements at the specified location in the container.
     *  @param __pos    Mutable iterator before which the content will be
     *                  inserted.
     *  @param __value  Element value to insert.
     */
    iterator
    insert(iterator __pos, const value_ptr_type& __value)
    { return _M_container.insert(__pos, __value); }


    /**
     *  @brief Inserts elements at the specified location in the container.
     *  @param __pos    Immutable iterator before which the content will be
     *                  inserted.
     *  @param __value  Element value to insert.
     */
    iterator
    insert(const_iterator __pos, const value_ptr_type& __value)
    { return _M_container.insert(__pos, __value); }

    /**
     *  @brief Removes the specified element from the container.
     *  @param __pos  Mutable iterator to the element to remove.
     */
    iterator
    erase(iterator __pos)
    { return _M_container.erase(__pos); }

    /**
     *  @brief Removes the specified element from the container.
     *  @param __pos  Immutable iterator to the element to remove.
     */
    iterator
    erase(const_iterator __pos)
    { return _M_container.erase(__pos); }

    /**
     *  @brief Returns the number of elements in the container.
     */
    size_type
    size()
    { return _M_container.size(); }

private:
    // The collections of the Bencode values.
    container_type _M_container;
};


typedef basic_list<char> list;


typedef basic_list<wchar_t> wlist;


} // namespace bencode

#endif // INCLUDE_bencode_list_hpp__
