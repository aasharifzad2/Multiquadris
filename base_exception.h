
#ifndef __BASE_EXCEPTION_H__
#define __BASE_EXCEPTION_H__

#include <string>


class base_exception
{
    virtual std::string message() const noexcept = 0;

    public:
    base_exception();
    ~base_exception();
};

#endif
