#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>


BOOST_AUTO_TEST_SUITE(TestList)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- Char list value should be decoded.");
    std::stringstream ss1("li4687327e20:internationalizatione");
    bencode::list l1;

    l1.load(ss1);
    auto first = l1[0];
    auto second = l1[1];

    BOOST_CHECK(bencode::integer(*first) == int64_t(4687327));
    BOOST_CHECK(bencode::string(*second) == "internationalization");
}


BOOST_AUTO_TEST_CASE(test_dump)
{
}


BOOST_AUTO_TEST_SUITE_END()
