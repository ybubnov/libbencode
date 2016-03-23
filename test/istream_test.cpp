#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>
#include <bencode/istream.hpp>


BOOST_AUTO_TEST_SUITE(TestInputStream)


BOOST_AUTO_TEST_CASE(test_get)
{
    BOOST_TEST_MESSAGE("--- Bencode values should be decoded from the "
        "char input stream.");

    std::stringstream ss1("i168574327454e"
        "22:frizziest perspirationl11:persistence8:rosemaryed11:"
        "appreciable:9:trapezoid8:remedial:8:crackpote");
    bencode::istream bs1(ss1.rdbuf());

    bencode::integer bv1;
    bencode::string bv2;
    bencode::list bv3;
    bencode::dict bv4;

    bs1 >> bv1 >> bv2 >> bv3 >> bv4;

    BOOST_CHECK(bv1 == int64_t(168574327454));
    BOOST_CHECK(bv2 == "frizziest perspiration");

    BOOST_CHECK(bencode::string(bv3[0]) == "persistence");
    BOOST_CHECK(bencode::string(bv3[1]) == "rosemary");

    BOOST_CHECK(bencode::string(bv4["appreciable"]) == "trapezoid");
    BOOST_CHECK(bencode::string(bv4["remedial"]) == "crackpot");
}


BOOST_AUTO_TEST_CASE(test_wchar_get)
{
    BOOST_TEST_MESSAGE("--- Bencode values should be decoded from the "
        "wide char input stream.");

    std::wstringstream ss1(L"i67318765e"
        "21:exasperate contestantl11:screwdriver12:racketeeringed9:"
        "lymphatic:7:majesty9:symbolism:14:predestinatione");
    bencode::wistream bs1(ss1.rdbuf());

    bencode::winteger bv1;
    bencode::wstring bv2;
    bencode::wlist bv3;
    bencode::wdict bv4;

    bs1 >> bv1 >> bv2 >> bv3 >> bv4;

    BOOST_CHECK(bv1 == int64_t(67318765));
    BOOST_CHECK(bv2 == L"exasperate contestant");

    BOOST_CHECK(bencode::wstring(bv3[0]) == L"screwdriver");
    BOOST_CHECK(bencode::wstring(bv3[1]) == L"racketeering");

    BOOST_CHECK(bencode::wstring(bv4[L"lymphatic"]) == L"majesty");
    BOOST_CHECK(bencode::wstring(bv4[L"symbolism"]) == L"predestination");
}


BOOST_AUTO_TEST_SUITE_END()
