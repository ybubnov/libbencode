#ifndef INCLUDE_bencode_list_hpp__
#define INCLUDE_bencode_list_hpp__

#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <vector>
#include <bencode/basic_value.hpp>


namespace bencode
{


template
< typename CharT
, typename Traits = std::char_traits<CharT>
, template
< typename T
> class Allocator = std::allocator
, template
< typename T
, typename Allocator > class Container = std::vector
> class basic_list : public basic_value<CharT, Traits>
{
private:
    // Define the list value alias.
    typedef basic_value<CharT, Traits> _Value;

    typedef std::shared_ptr<_Value> _Value_Ptr;

    // Define the list container allocator for the values.
    typedef Allocator<_Value_Ptr> _Alloc;

    // Define the list container type to keep the collection
    // of the Bencode values.
    typedef Container<_Value_Ptr, _Alloc> _List_container;

    // Define the list iterator as a functional
    // equivalent to the container iterator.
    typedef typename _List_container::iterator iterator;

    // Define the list constant iterator as a functional
    // equivalent to the container iterator.
    typedef typename _List_container::const_iterator const_iterator;

    // The collections of the Bencode values.
    _List_container _M_container;

public:
    basic_list() { }

    // Create a new list value from the initializer list.
    basic_list(std::initializer_list<_Value_Ptr> l)
    : _M_container(l) { }

    basic_list(const_iterator cbegin, const_iterator cend)
    : _M_container(cbegin, cend) { }

    ~basic_list() { }

    // Serialize the list value to the specified output stream.
    void
    dump(std::basic_ostream<CharT, Traits>& __s) const
    {
        __s << _Value::list_type;

        std::for_each(_M_container.begin(), _M_container.end(),
            [&__s](_Value_Ptr value) {

            value->dump(__s);
        });

        __s << _Value::end_type;
    }

    // Deserialize the list value from the specified input stream.
    void
    load(std::basic_istream<CharT, Traits>& __s) const
    {
        if (__s.peek() != _Value::list_type) {
            throw type_error(
                "bencode::list::load the specified stream does "
                "not contain interpretable bencode list value\n");
        }
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

    void
    push_back(_Value_Ptr value)
    { _M_container.push_back(value); }
};


typedef basic_list<char> list;


typedef basic_list<wchar_t> wlist;


} // namespace bencode

#endif // INCLUDE_bencode_list_hpp__
