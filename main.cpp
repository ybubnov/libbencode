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
    auto s = bencode::string("hello");
    auto i = bencode::integer(42);

    auto l = bencode::list();
    l.push_back(std::make_shared<bencode::string>(s));
    l.push_back(std::make_shared<bencode::integer>(i));
    w.write(l);

    std::stringstream ss("i-123");

    i = bencode::integer();
    i.load(ss);

    std::cout << std::endl;
    w.write(i);

    //bencode::list l1 = {&s, &i};
    ////w.write(l1);

    //bencode::list l2(v.cbegin(), v.cend());
    ////w.write(l2);

    //bencode::dict d1 = {{bencode::string("bbb"), &l1}, {bencode::string("aaa"), &s}};
    //d1.insert(std::make_pair(s, &i));
    //w.write(d1);

    return 1;
}
