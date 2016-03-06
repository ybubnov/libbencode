#ifndef INCLUDE_bencode_exception_hpp__
#define INCLUDE_bencode_exception_hpp__


#include <stdexcept>


namespace bencode
{


class exception : public std::exception
{
private:
    std::string _M_msg;

public:
    explicit
    exception(const std::string& __s);

    virtual
    ~exception();

    virtual const char*
    what() const noexcept (true);
};


class type_error : public exception
{
public:
    explicit
    type_error(const std::string& __s);

    virtual
    ~type_error();
};


class value_error : public exception
{
public:
    explicit
    value_error(const std::string& __s);

    virtual
    ~value_error();
};


class encoding_error : public exception
{
public:
    explicit
    encoding_error(const std::string &__s);

    virtual
    ~encoding_error();
};


}


#endif // INCLUDE_bencode_exception_hpp__
