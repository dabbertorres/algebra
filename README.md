# algebra
Simplistic algebraic expression library in C++ 14

Designed to be used as if one were naturally typing out an expression.

# Simple example
```cpp
#include "Expression.hpp"

using namespace dbr;
using namespace dbr::algebra::literals;

int main()
{
	algebra::Expression exp = algebra::pow(5 * algebra::pow(0_var, 2) - 3, 1_var);
	
	algebra::Values vals;
	vals[0_var] = 3.2;
	vals[1_var] = -2.8;
	
	return exp(vals);
}

```
