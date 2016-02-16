#ifndef INCLUDE_bencode_token_list_hpp__
#define INCLUDE_bencode_token_list_hpp__

#include <intializer_list>

#include <bencode/token/basic_token.hpp>



namespace bencode {
namespace token {

template<typename CharT,
         typename Traits,
         typename <typename, typename> class Container>
class list_token : public basic_token<CharT, Traits> {
private:
    Container <basic_token, std::allocator<basic_token>> value;

public:
    list_token(std::initializer_list<basic_token> l) : value(l) {
    }

    list_token();
};

} // namespace token
} // namespace bencode


#endif // INCLUDE_bencode_token_list_hpp__
