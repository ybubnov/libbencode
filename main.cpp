#include <iostream>
#include <vector>
#include <utility>
#include <bencode.hpp>


template<typename CharT,
         typename Traits>
class writer {
private:
    std::basic_ostream<CharT, Traits> &ostream;

public:

    writer(std::basic_ostream<CharT, Traits> &s) : ostream(s) { }

    void write(bencode::basic_value<CharT, Traits> &t)
    {
        t.dump(this->ostream);
    }
};


int main(int argc, char **argv)
{
    writer<char, std::char_traits<char>> w(std::cout);
    auto s = bencode::string(std::string("hello"));
    auto i = bencode::integer(42);

    auto l = bencode::list();
    l.push_back(&s);
    l.push_back(&i);
    //w.write(l);

    auto v = std::vector<bencode::basic_value<char>*>();
    v.push_back(&s);

    bencode::list l1 = {&s, &i};
    //w.write(l1);

    bencode::list l2(v.cbegin(), v.cend());
    //w.write(l2);

    auto d1 = bencode::dict();
    d1.insert(std::pair<bencode::basic_string, bencode::basic_value*>(s, &i));
    w.write(d1);

    return 1;
}
