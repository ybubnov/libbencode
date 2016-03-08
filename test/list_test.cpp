#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>


BOOST_AUTO_TEST_SUITE(TestList)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- List value should be decoded "
        "from the byte array.");
    std::stringstream ss1("li4687327e20:internationalizatione");
    bencode::list l1;

    l1.load(ss1);
    auto first = l1[0];
    auto second = l1[1];

    BOOST_CHECK(bencode::integer(*first) == int64_t(4687327));
    BOOST_CHECK(bencode::string(*second) == "internationalization");
}


BOOST_AUTO_TEST_CASE(test_load_exceptions)
{
    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid beginning of the list encoding.");
    std::stringstream ss1("Li4987ee");
    bencode::list l1;

    BOOST_CHECK_EXCEPTION(l1.load(ss1), bencode::type_error,
        [](bencode::type_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "does not contain interpretable bencode list");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid ending of the list encoding.");
    std::stringstream ss2("li4987576e");
    bencode::list l2;

    BOOST_CHECK_EXCEPTION(l2.load(ss2), bencode::encoding_error,
        [](bencode::encoding_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the end of the list `e` expected, but `\xff` found");
            return pos != std::string::npos;
        });
}


BOOST_AUTO_TEST_CASE(test_dump)
{
    BOOST_TEST_MESSAGE("--- List value should be encoded "
        "into the byte characters.");
    std::stringstream ss1;
    bencode::list l1;

    l1.push_back(bencode::make_integer(4687327));
    l1.push_back(bencode::make_string("Decimal data"));

    l1.dump(ss1);
    BOOST_CHECK(ss1.str() == "li4687327e12:Decimal datae");


    BOOST_TEST_MESSAGE("--- List value should be encoded "
        "into wide characters.");
    std::wstringstream ss2;
    bencode::wlist l2;

    l2.push_back(bencode::make_integer<wchar_t>(65732498));
    l2.push_back(bencode::make_string<wchar_t>(
        L"Persistence homology classes"));

    l2.dump(ss2);
    BOOST_CHECK(ss2.str() == L"li65732498e28:Persistence homology classese");
}


BOOST_AUTO_TEST_SUITE_END()
