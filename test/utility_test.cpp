#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>
#include <bencode/utility.hpp>

using namespace bencode;


BOOST_AUTO_TEST_SUITE(TestUtility)


BOOST_AUTO_TEST_CASE(test_char_literal)
{
    BOOST_TEST_MESSAGE("--- Bencode value should be decoded "
        "from the char string literal.");

    auto val1 = "d5:first:i627237e6:second:5:valuee"_bencode;
    bencode::dict d1(val1);

    BOOST_CHECK(bencode::integer(d1["first"]) == int64_t(627237));
    BOOST_CHECK(bencode::string(d1["second"]) == "value");
}


BOOST_AUTO_TEST_CASE(test_wchar_literal)
{
    BOOST_TEST_MESSAGE("--- Bencode value should be decoded "
        "from the wide char string literal.");

    auto val1 = L"d5:first:i627237e6:second:5:valuee"_bencode;
    bencode::wdict d1(val1);

    BOOST_CHECK(bencode::winteger(d1[L"first"]) == int64_t(627237));
    BOOST_CHECK(bencode::wstring(d1[L"second"]) == L"value");
}


BOOST_AUTO_TEST_SUITE_END()
