#include "Variable.hpp"

#include <ostream>

namespace dbr
{
    namespace algebra
    {
        bool operator<(Variable lhs, Variable rhs)
        {
            return lhs.id < rhs.id;
        }

        std::ostream& operator<<(std::ostream& os, Variable var)
        {
            return os << "Variable[" << var.id << "]";
        }
    }
}

