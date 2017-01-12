#ifndef DBR_ALGEBRA_VARIABLE_HPP
#define DBR_ALGEBRA_VARIABLE_HPP

#include <iosfwd>

namespace dbr
{
    namespace algebra
    {
        struct Variable
        {
        public:
            using Id = unsigned long long;

            explicit constexpr Variable(Id id)
                : id{id}
            {}

            const Id id;
        };

        bool operator<(Variable lhs, Variable rhs);

        std::ostream& operator<<(std::ostream& os, Variable var);

        namespace literals
        {
            constexpr Variable operator"" _var(Variable::Id id)
            {
                return Variable{id};
            }
        }
    }
}

#endif
