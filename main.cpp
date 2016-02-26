#include <iostream>
#include <vector>
#include <utility>
#include <bencode.hpp>
#include <bencode/istream.hpp>
#include <bencode/ostream.hpp>


int main(int argc, char **argv)
{
    bencode::ostream bs(std::cout.rdbuf());

    auto s = bencode::string("hello");
    auto i = bencode::integer(42);

    auto l = bencode::list();
    l.push_back(std::make_shared<bencode::string>(s));
    l.push_back(std::make_shared<bencode::integer>(i));
    bs << l;

    std::stringstream ss("i-123e");
    bencode::istream bi(ss.rdbuf());

    bi >> i;

    std::cout << std::endl;
    bs << i;

    std::stringstream s1("5:olleh");
    s.load(s1);

    std::cout << std::endl;
    bs << s;

    std::stringstream s2("d5:first:i12345e6:second:5:helloe");
    bencode::istream bi1(s2.rdbuf());
    bencode::dict d1;

    bi1 >> d1;

    bs << d1;


    return 1;
}
