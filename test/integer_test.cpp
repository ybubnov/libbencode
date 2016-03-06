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


    BOOST_TEST_MESSAGE("--- Zero value should be decoded.");
    std::stringstream ss2("i0e");
    bencode::integer i2;

    i2.load(ss2);
    BOOST_CHECK(i2 == int64_t(0));


    BOOST_TEST_MESSAGE("--- Negative value should be decoded.");
    std::stringstream ss3("i-1657324813743e");
    bencode::integer i3;

    i3.load(ss3);
    BOOST_CHECK(i3 == int64_t(-1657324813743));


    BOOST_TEST_MESSAGE("--- WChar integer value should be decoded. ");
    std::wstringstream ss4(L"i1864795134e");
    bencode::winteger i4;

    i4.load(ss4);
    BOOST_CHECK(i4 == int64_t(1864795134));
}


BOOST_AUTO_TEST_CASE(test_load_exceptions)
{
    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid beginning of the integer encoding.");
    std::stringstream ss1("I316857451e");
    bencode::integer i1;

    BOOST_CHECK_EXCEPTION(i1.load(ss1), bencode::type_error,
        [](bencode::type_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "does not contain interpretable bencode integer");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid ending of the integer encoding.");
    std::stringstream ss2("i643248732E");
    bencode::integer i2;

    BOOST_CHECK_EXCEPTION(i2.load(ss2), bencode::encoding_error,
        [](bencode::encoding_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the end of the integer `e` expected, but `E` found");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "missing of the ending of the integer encoding.");
    std::stringstream ss3("i316874327");
    bencode::integer i3;

    BOOST_CHECK_EXCEPTION(i3.load(ss3), bencode::encoding_error,
        [](bencode::encoding_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the end of the integer `e` expected, but `7` found");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid integer value.");
    std::stringstream ss5("iI am Vegane");
    bencode::integer i5;

    BOOST_CHECK_EXCEPTION(i5.load(ss5), bencode::value_error,
        [](bencode::value_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the specified value is not a number");
            return pos != std::string::npos;
        });
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
