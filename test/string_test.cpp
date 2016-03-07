#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>


BOOST_AUTO_TEST_SUITE(TestString)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- Char string value should be decoded.");
    std::stringstream ss1("20:internationalization");
    bencode::string s1;

    s1.load(ss1);
    BOOST_CHECK(s1 == "internationalization");

    BOOST_TEST_MESSAGE("--- Wchar string value should be decoded.");
    std::wstringstream ss2(L"19:интернационализация");
    bencode::wstring s2;

    s2.load(ss2);
    BOOST_CHECK(s2 == L"интернационализация");
}


BOOST_AUTO_TEST_CASE(test_load_exceptions)
{
    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "missing the delimiter symbol.");
    std::stringstream ss1("44The randomness comes from atmospheric noise");
    bencode::string s1;

    BOOST_CHECK_EXCEPTION(s1.load(ss1), bencode::encoding_error,
        [](bencode::encoding_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the delimiter `:` expected, but `e` found");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid string length.");
    std::stringstream ss2("inf:This should be an infinite string");
    bencode::string s2;

    BOOST_CHECK_EXCEPTION(s2.load(ss2), bencode::value_error,
        [](bencode::value_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the specified string length is not a number");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "negative string length.");
    std::stringstream ss3("-29:Each string should be unique");
    bencode::string s3;

    BOOST_CHECK_EXCEPTION(s3.load(ss3), bencode::value_error,
        [](bencode::value_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the length of the string value must be a "
                "positive integer: `-29`");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "too small string length.");
    std::stringstream ss4("100:This string should be much longer.");
    bencode::string s4;

    BOOST_CHECK_EXCEPTION(s4.load(ss4), bencode::value_error,
        [](bencode::value_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "decoded length is not equal to the real one: `100` != `34`");
            return pos != std::string::npos;
        });
}


BOOST_AUTO_TEST_CASE(test_operators)
{
    BOOST_TEST_MESSAGE("--- Validate string comparison operators.");
    bencode::string s1("The forward heat shield, or apex cover, is "
        "made of brazed stainless steel honeycomb and covered with "
        "ablative material.");

    BOOST_CHECK(s1 == "The forward heat shield, or apex cover, is "
        "made of brazed stainless steel honeycomb and covered with "
        "ablative material.");

    BOOST_CHECK(s1 == std::string("The forward heat shield, or apex "
        "cover, is made of brazed stainless steel honeycomb and covered "
        "with ablative material."));
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
