#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>


BOOST_AUTO_TEST_SUITE(TestInteger)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- Char integer value should be decoded.");
    std::stringstream ss1("i291346e");
    bencode::integer i1;

    i1.load(ss1);
    BOOST_CHECK(i1 == int64_t(291346));

    BOOST_TEST_MESSAGE("--- WChar integer value should be decoded. ");
    std::wstringstream ss2(L"i1864795134e");
    bencode::winteger i2;

    i2.load(ss2);
    BOOST_CHECK(i2 == int64_t(1864795134));
}


BOOST_AUTO_TEST_CASE(test_dump)
{
    BOOST_TEST_MESSAGE("--- Integer value should be encoded into Char.");
    std::stringstream ss1;
    bencode::integer i1(64234973249);

    i1.dump(ss1);
    BOOST_CHECK(ss1.str() == "i64234973249e");

    BOOST_TEST_MESSAGE("--- Integer values should be encoded into WChar.");
    std::wstringstream ss2;
    bencode::winteger i2(16756911);

    i2.dump(ss2);
    BOOST_CHECK(ss2.str() == L"i16756911e");
}


BOOST_AUTO_TEST_SUITE_END()
