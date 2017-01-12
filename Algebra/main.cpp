#include <iostream>

#include "Expression.hpp"

using namespace dbr;
using namespace dbr::algebra::literals;

int main(int argc, char** argv)
{
    algebra::Expression exp = algebra::pow(5 * algebra::pow(0_var, 2) - 3, 1_var);

    algebra::Values values;

    for(int i = -5; i <= 5; ++i)
    {
        values[0_var] = i;
        values[1_var] = i * 1.3;

        std::cout << 0_var << " = " << i << ": " << exp(values) << '\n';
    }

    return 0;
}
