#include <bencode/exception.hpp>


using namespace bencode;


exception::exception(const std::string& __s)
: _M_msg(__s) { }


exception::~exception()
{ }


const char*
exception::what() const noexcept (true)
{ return _M_msg.c_str(); }


type_error::type_error(const std::string& __s)
: exception(__s) { }


type_error::~type_error() { }


value_error::value_error(const std::string& __s)
: exception(__s) { }


value_error::~value_error() { }


encoding_error::encoding_error(const std::string& __s)
: exception(__s) { }


encoding_error::~encoding_error() { }
