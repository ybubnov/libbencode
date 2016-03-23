#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>
#include <bencode/ostream.hpp>
#include <iostream>


BOOST_AUTO_TEST_SUITE(TestOutputStream)


BOOST_AUTO_TEST_CASE(test_put)
{
    BOOST_TEST_MESSAGE("--- Bencode values should be encoded into the "
        "char output stream.");

    std::stringstream ss1;
    bencode::ostream bs1(ss1.rdbuf());

    bencode::integer bv1(67318765);
    bencode::string bv2("exasperate contestant");
    bencode::list bv3(2);
    bencode::dict bv4;

    bv3[0] = bencode::make_string("screwdriver");
    bv3[1] = bencode::make_string("racketeering");

    bv4["lymphatic"] = bencode::make_string("majesty");
    bv4["symbolism"] = bencode::make_string("predestination");

    bs1 << bv1 << bv2 << bv3 << bv4;

    BOOST_CHECK(ss1.str() == "i67318765e"
        "21:exasperate contestantl11:screwdriver12:racketeeringed9:"
        "lymphatic:7:majesty9:symbolism:14:predestinatione");
}


BOOST_AUTO_TEST_CASE(test_wchar_put)
{
    BOOST_TEST_MESSAGE("--- Bencode values should be encoded into the "
        "wide char output stream.");

    std::wstringstream ss1;
    bencode::wostream bs1(ss1.rdbuf());

    bencode::winteger bv1(168574327454);
    bencode::wstring bv2(L"frizziest perspiration");
    bencode::wlist bv3(2);
    bencode::wdict bv4;

    bv4[L"appreciable"] = bencode::make_string<wchar_t>(L"trapezoid");
    bv4[L"remedial"] = bencode::make_string<wchar_t>(L"crackpot");

    bv3[0] = bencode::make_string<wchar_t>(L"persistence");
    bv3[1] = bencode::make_string<wchar_t>(L"rosemary");

    bs1 << bv1 << bv2 << bv3 << bv4;

    std::wcout << ss1.str();
    BOOST_CHECK(ss1.str() == L"i168574327454e"
        "22:frizziest perspirationl11:persistence8:rosemaryed11:"
        "appreciable:9:trapezoid8:remedial:8:crackpote");
}

BOOST_AUTO_TEST_SUITE_END()
