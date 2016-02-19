#include <iostream>
#include <vector>
#include <utility>

#include <bencode.hpp>
#include <bencode/token.hpp>


template<typename CharT,
         typename Traits>
class writer {
private:
    std::basic_ostream<CharT, Traits> &ostream;

public:

    writer(std::basic_ostream<CharT, Traits> &s) : ostream(s) { }

    void write(bencode::token::basic_token<CharT, Traits> &t)
    {
        t.dump(this->ostream);
    }
};


int main(int argc, char **argv)
{
    writer<char, std::char_traits<char>> w(std::cout);
    auto s = bencode::token::string(std::string("hello"));
    auto i = bencode::token::integer(42);

    auto l = bencode::token::list();
    l.push_back(&s);
    l.push_back(&i);
    //w.write(l);

    auto v = std::vector<bencode::token::basic_token<char>*>();
    v.push_back(&s);

    bencode::token::list l1 = {&s, &i};
    //w.write(l1);

    bencode::token::list l2(v.cbegin(), v.cend());
    //w.write(l2);

    auto d1 = bencode::token::dictionary();
    d1.insert(std::pair<bencode::token::string, bencode::token::basic_token*>(s, &i));
    w.write(d1);

    return 1;
}
