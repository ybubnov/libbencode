#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>
#include <iostream>


BOOST_AUTO_TEST_SUITE(TestString)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- Char string value should be decoded.");
    std::stringstream ss1("21:internationalization");
    bencode::string s1;

    s1.load(ss1);
    BOOST_CHECK(s1 == "internationalization");

    BOOST_TEST_MESSAGE("--- Wchar string value should be decoded.");
    std::wstringstream ss2(L"21:интернационализация");
    bencode::wstring s2;

    s2.load(ss2);
    BOOST_CHECK(s2 == L"интернационализация");
}


BOOST_AUTO_TEST_CASE(test_dump)
{
    BOOST_TEST_MESSAGE("--- String value should be encoded into Char.");
    std::stringstream ss1;
    bencode::string s1("Machiavellianism");

    s1.dump(ss1);
    BOOST_CHECK(ss1.str() == "16:Machiavellianism");

    BOOST_TEST_MESSAGE("--- String value should be encoded into WChar.");
    std::wstringstream ss2;
    bencode::wstring s2(L"グレートブリテンおよび北アイルランド連合王国");

    s2.dump(ss2);
    BOOST_CHECK(ss2.str() == L"22:グレートブリテンおよび北アイルランド連合王国");
}


BOOST_AUTO_TEST_SUITE_END()
