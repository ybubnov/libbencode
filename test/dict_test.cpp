#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bencode

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bencode.hpp>


BOOST_AUTO_TEST_SUITE(TestDict)


BOOST_AUTO_TEST_CASE(test_load)
{
    BOOST_TEST_MESSAGE("--- Dictionary value should be decoded "
        "from the byte characters.");
    std::stringstream ss1("d5:first:i-4987357e6:second:8:homotopye");
    bencode::dict d1;

    d1.load(ss1);
    BOOST_CHECK(bencode::integer(d1["first"]) == int64_t(-4987357));
    BOOST_CHECK(bencode::string(d1["second"]) == "homotopy");


    BOOST_TEST_MESSAGE("--- Dictionary value should be decoded "
        "from the wide characters.");
    std::wstringstream ss2(L"d4:kind:13:Switch-Router5:count:i6573ee");
    bencode::wdict d2;

    d2.load(ss2);
    BOOST_CHECK(bencode::wstring(d2[L"kind"]) == L"Switch-Router");
    BOOST_CHECK(bencode::winteger(d2[L"count"]) == int64_t(6573));
}


BOOST_AUTO_TEST_CASE(test_load_exceptions)
{
    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid beginning of the dictionary encoding.");
    std::stringstream ss1("D6:number:i456ee");
    bencode::dict d1;

    BOOST_CHECK_EXCEPTION(d1.load(ss1), bencode::type_error,
        [](bencode::type_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "does not contain interpretable bencode dictionary");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "missing key-value separator symbol.");
    std::stringstream ss2("d3:key5:valuee");
    bencode::dict d2;

    BOOST_CHECK_EXCEPTION(d1.load(ss2), bencode::encoding_error,
        [](bencode::encoding_error const &exception) {
            auto pos = std::string(exception.what()).find(
                "after the key a `:` delimiter expected, but `5` found");
            return pos != std::string::npos;
        });


    BOOST_TEST_MESSAGE("--- Exception should be raised on "
        "invalid ending of the dictionary encoding.");
    std::stringstream ss3("d4:key1:i97357e");
    bencode::dict d3;

    BOOST_CHECK_EXCEPTION(d3.load(ss3), bencode::encoding_error,
        [](bencode::encoding_error const& exception) {
            auto pos = std::string(exception.what()).find(
                "the end of the dictionary `e` expected, but `\xff` found");
            return pos != std::string::npos;
        });
}


BOOST_AUTO_TEST_CASE(test_dump)
{
    BOOST_TEST_MESSAGE("--- Dictionary value should be encoded "
        "into the byte characters.");
    std::stringstream ss1;
    bencode::dict d1;

    d1["length"] = bencode::make_integer(19);
    d1["type"] = bencode::make_string("input");
    d1["value"] = bencode::make_string("Beam me up, Scotty!");
    // Validate that it is possible to save the null-pointer,
    // but it would not be a part of the destination encoding.
    d1["nullable"] = nullptr;

    d1.dump(ss1);
    BOOST_CHECK(ss1.str() ==
        "d6:length:i19e4:type:5:input5:value:19:Beam me up, Scotty!e");


    BOOST_TEST_MESSAGE("--- Dictionary value should be encoded "
        "into wide characters.");
    std::wstringstream ss2;
    bencode::wdict d2;

    d2[L"hoplimit"] = bencode::make_integer<wchar_t>(255);
    d2[L"saddr"] = bencode::make_string<wchar_t>(L"2001:db8::1");
    d2[L"daddr"] = bencode::make_string<wchar_t>(L"2001:db8::2");
    d2[L"nullable"] = nullptr;

    d2.dump(ss2);
    BOOST_CHECK(ss2.str() ==
        L"d5:daddr:11:2001:db8::28:hoplimit:i255e5:saddr:11:2001:db8::1e");
}


BOOST_AUTO_TEST_SUITE_END()
