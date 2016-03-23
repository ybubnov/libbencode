#include <iostream>
#include <vector>
#include <utility>
#include <bencode.hpp>
#include <bencode/istream.hpp>
#include <bencode/ostream.hpp>
#include <bencode/utility.hpp>


using namespace bencode;


int main(int argc, char **argv)
{
    ostream bs(std::cout.rdbuf());

    auto bint = "i666e"_bencode;
    bs << *bint;

    bencode::list l1(2);

    return 0;
}
