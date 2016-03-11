#include <bencode/exception.hpp>


using namespace bencode;


// Construct a new instance of the base exception.
exception::exception(const std::string& __s)
: _M_msg(__s) { }


// Deconstruct an instance of the base exception.
exception::~exception()
{ }


// Pointer to a null-terminated string with explanatory information.
const char*
exception::what() const noexcept (true)
{ return _M_msg.c_str(); }


// Construct a new instance of the type exception.
type_error::type_error(const std::string& __s)
: exception(__s)
{ }


// Construct a new instance of the value exception.
value_error::value_error(const std::string& __s)
: exception(__s)
{ }


// Construct a new instance of the encoding exception.
encoding_error::encoding_error(const std::string& __s)
: exception(__s)
{ }
