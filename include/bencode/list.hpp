#ifndef INCLUDE_bencode_list_hpp__
#define INCLUDE_bencode_list_hpp__

#include <algorithm>
#include <iterator>
#include <sstream>
#include <initializer_list>
#include <bencode/value.hpp>
#include <iostream>


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
    // Define the list container allocator for the values.
    using allocator_type = Allocator<value_ptr_type>;

    // Define the list container type to keep the collection
    // of the Bencode values.
    using container_type = ListContainer<value_ptr_type, allocator_type>;

    // Define the list iterator as a functional
    // equivalent to the container iterator.
    using iterator = typename container_type::iterator;

    // Define the list constant iterator as a functional
    // equivalent to the container iterator.
    using const_iterator = typename container_type::const_iterator;

    basic_list()
    { }

    basic_list(const basic_value_type& __value)
    {
        auto __list = dynamic_cast<const basic_list&>(__value);
        // explicirly copy the containers content.
        _M_container = container_type(__list._M_container);
    }

    basic_list(const std::shared_ptr<basic_value_type&> __ptr)
    : basic_list(*__ptr)
    { }

    basic_list(std::size_t __count)
    :_M_container(__count)
    { }

    // Create a new list value from the initializer list.
    basic_list(std::initializer_list<value_ptr_type> l)
    : _M_container(l)
    { }

    basic_list(const_iterator cbegin, const_iterator cend)
    : _M_container(cbegin, cend)
    { }

    ~basic_list()
    { }

    // Serialize the list value to the specified output stream.
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

    // Deserialize the list value from the specified input stream.
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

    iterator
    begin()
    { return _M_container.begin(); }

    iterator
    end()
    { return _M_container.end(); }

    const_iterator
    cbegin() const
    { return _M_container.cbegin(); }

    const_iterator
    cend() const
    { return _M_container.cend(); }

    value_ptr_type&
    operator[](std::size_t __index)
    { return _M_container.operator[](__index); }

    void
    push_back(const value_ptr_type& __value)
    { _M_container.push_back(__value); }

private:
    // The collections of the Bencode values.
    container_type _M_container;
};


typedef basic_list<char> list;


typedef basic_list<wchar_t> wlist;


} // namespace bencode

#endif // INCLUDE_bencode_list_hpp__
