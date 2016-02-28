#include <iostream>
#include <vector>
#include <utility>
#include <bencode.hpp>
#include <bencode/istream.hpp>
#include <bencode/ostream.hpp>


int main(int argc, char **argv)
{
    bencode::ostream bs(std::cout.rdbuf());

    std::stringstream s1("d5:first:i12345e6:second:5:helloe");
    bencode::istream bi1(s1.rdbuf());
    bencode::dict d1;

    bi1 >> d1;
    bs << d1;

    std::stringstream s2("l5:firsti12345e6:second5:helloe");
    bencode::istream bi2(s2.rdbuf());
    bencode::list l1;

    bi2 >> l1;
    bs << l1;

    bencode::integer i1(123);
    std::cout << i1;

    return 0;
}
