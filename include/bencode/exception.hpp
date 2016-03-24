#ifndef INCLUDE_bencode_exception_hpp__
#define INCLUDE_bencode_exception_hpp__


#include <stdexcept>


namespace bencode
{


/**
 *  @brief Base class for all library exceptions.
 *
 *  This is the base class for all exceptions thrown by the bencode
 *  encoding library.
 */
class exception : public std::exception
{
private:
    std::string _M_msg;

public:
    /**
     *  @brief Construct exception using a string message.
     */
    explicit
    exception(const std::string& __s);

    /**
     *  @brief Destroy exception instance.
     *
     *  Release memory and free resources occupied by the exception
     *  instance.
     */
    virtual
    ~exception();

    /**
     *  @brief Explanatory string.
     *
     *  Pointer to a null-terminated string with explanatory information.
     */
    virtual const char*
    what() const noexcept (true);
};


// Construct a new instance of the base exception.
inline
exception::exception(const std::string& __s)
: _M_msg(__s) { }


// Deconstruct an instance of the base exception.
inline
exception::~exception()
{ }


// Pointer to a null-terminated string with explanatory information.
inline
const char*
exception::what() const noexcept (true)
{ return _M_msg.c_str(); }


/**
 *  @brief Type exception class.
 *
 *  Define a type of object to be thrown as exception on invalid type.
 *  Exceptions of this type will be raised on invalid type of parser
 *  used to decode the bencoded string. E.g. on attempt to decode
 *  "i132e" using basic_string decoder an exception of type_error
 *  will be raised.
 */
class type_error : public exception
{
public:
    /**
     *  @brief Construct exception using string message.
     *  @param __s  Exception message string.
     */
    explicit
    type_error(const std::string& __s);
};


// Construct a new instance of the type exception.
inline
type_error::type_error(const std::string& __s)
: exception(__s)
{ }


/**
 *  @brief Value exception class.
 *
 *  Define a type of object to be thrown as exception on invalid value.
 *  Exceptions of this type will be raised on invalid encoded value, e.g.
 *  "i12$e" for integer type.
 */
class value_error : public exception
{
public:
    /**
     *  @brief Construct exception using string message.
     *  @param __s  Exception message string.
     */
    explicit
    value_error(const std::string& __s);
};


// Construct a new instance of the value exception.
inline
value_error::value_error(const std::string& __s)
: exception(__s)
{ }


/**
 *  @brief Encoding exception class.
 *
 *  Define a type of object to be thrown as exception on invalid
 *  encoding. E.g. if the integer value encoding is not starting
 *  from the "i" letter or the ending value is not "e" (in case
 *  of the integer), this exception will be thrown. The respective
 *  validations would be performed for each supporting type.
 */
class encoding_error : public exception
{
public:
    /**
     *  @brief Construct exception using string message.
     *  @param __s  Exception message string.
     */
    explicit
    encoding_error(const std::string &__s);
};


// Construct a new instance of the encoding exception.
inline
encoding_error::encoding_error(const std::string& __s)
: exception(__s)
{ }


} // namespace bencode


#endif // INCLUDE_bencode_exception_hpp__
