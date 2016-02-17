#ifndef INCLUDE_bencode_token_list_hpp__
#define INCLUDE_bencode_token_list_hpp__

#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <utility>
#include <vector>

#include <bencode/token/basic_token.hpp>


namespace bencode {
namespace token {

template<
    typename CharT,
    typename Traits = std::char_traits<CharT>,
    template <typename T, typename Allocator = std::allocator<T> > class Container = std::vector>
class basic_list : public basic_token<CharT, Traits> {
private:
    Container<basic_token<CharT, Traits>*> container;

    // typedef std::iterator<typename Category,
    //     typename Tp, typename Distance,
    //     typename Pointer, typename Reference> _List_iterator;

public:
    basic_list() { }

    // Create a new list token from the initializer list.
    basic_list(std::initializer_list<basic_token<CharT, Traits>*> l)
    : container(l) { }

    // template <
    //     typename Class,
    //     typename Distance,
    //     typename Pointer,
    //     typename Reference>
    // basic_list(
    //     std::iterator<Class, basic_token<CharT, Traits>*, Distance, Pointer, Reference> begin,
    //     std::iterator<Class, basic_token<CharT, Traits>*, Distance, Pointer, Reference> end)
    // {
    //     this->container.insert(begin, end);
    // }

    // Serialize the list token to the specified output stream.
    void dump(std::basic_ostream<CharT, Traits> &s)
    {
        s << "l";

        std::for_each(this->container.begin(), this->container.end(),
            [&s](basic_token<CharT, Traits> *value) {

            value->dump(s);
        });

        s << "e";
    }

    // Deserialize the list token from the specified input stream.
    void load(std::basic_istream<CharT, Traits> &s)
    {
        // TBD
    }

    void push_back(basic_token<CharT, Traits> *value)
    {
        this->container.push_back(value);
    }
};


typedef basic_list<char> list;


typedef basic_list<wchar_t> wlist;

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_list_hpp__
