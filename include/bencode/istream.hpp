#ifndef INCLUDE_bencode_istream_hpp__
#define INCLUDE_bencode_istream_hpp__

#include <ostream>
#include <streambuf>
#include <bencode/typedef.hpp>


namespace bencode {


template
< typename CharT
, typename Traits = std::char_traits<CharT>
> class basic_istream
{
protected:
    std::basic_istream<CharT, Traits> _M_istream;

    typedef basic_value<CharT, Traits> _Value;

    typedef basic_integer<CharT, Traits> _Integer;

    typedef basic_list<CharT, Traits> _List;

    typedef basic_dict<CharT, Traits> _Dict;

    typedef basic_string<CharT, Traits> _String;

public:
    explicit
    basic_istream(std::basic_streambuf<CharT, Traits>* sb)
    : _M_istream(sb) { }

    basic_istream&
    get(_Value &__v)
    { __v.load(_M_istream); return *this; }

    std::shared_ptr<_Value>
    get()
    {
        std::shared_ptr<_Value> __ptr;

        switch (_M_istream.peek())
        {
        case _Value::int_type:
            __ptr = std::make_shared<_Integer>(new _Integer());
        case _Value::list_type:
            __ptr = std::make_shared<_List>(new _List());
        case _Value::dict_type:
            __ptr = std::make_shared<_Dict>(new _Dict());
        default:
            __ptr = std::make_shared<_String>(new _String());
        }

        get(*__ptr);
        return __ptr;
    }

    basic_istream&
    operator>>(_Value &__v)
    { return get(__v); }

    // Synchronizes the input buffer with the associated data source.
    int
    sync()
    { return _M_istream.sync(); }
};


typedef basic_istream<char> istream;


typedef basic_istream<wchar_t> wistream;


} // namespace bencode

#endif // INCLUDE_bencode_istream_hpp__
