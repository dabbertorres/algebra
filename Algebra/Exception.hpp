#ifndef DBR_ALGEBRA_EXCEPTION_HPP
#define DBR_ALGEBRA_EXCEPTION_HPP

#include <stdexcept>

namespace dbr
{
    namespace algebra
    {
        class Exception : public std::logic_error
        {
        public:
            using std::logic_error::logic_error;
        };
    }
}

#endif

