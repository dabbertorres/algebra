#ifndef DBR_ALGEBRA_EXPRESSION_HPP
#define DBR_ALGEBRA_EXPRESSION_HPP

#include <set>
#include <map>
#include <functional>

#include "Variable.hpp"

namespace dbr
{
    namespace algebra
    {
        using Variables = std::set<Variable>;
        using Values = std::map<Variable, double>;

        class Expression
        {
        public:
            /////////////////////////////////////////////////////
            // addition
            /////////////////////////////////////////////////////
            friend Expression operator+(Variable lhs, double rhs);
            friend Expression operator+(Variable lhs, Expression rhs);
            friend Expression operator+(Variable lhs, Variable rhs);

            friend Expression operator+(Expression lhs, double rhs);
            friend Expression operator+(Expression lhs, Variable rhs);
            friend Expression operator+(Expression lhs, Expression rhs);

            friend Expression operator+(double lhs, Variable rhs);
            friend Expression operator+(double lhs, Expression rhs);
            /////////////////////////////////////////////////////

            /////////////////////////////////////////////////////
            // subtraction
            /////////////////////////////////////////////////////
            friend Expression operator-(Variable lhs, double rhs);
            friend Expression operator-(Variable lhs, Expression rhs);
            friend Expression operator-(Variable lhs, Variable rhs);

            friend Expression operator-(Expression lhs, double rhs);
            friend Expression operator-(Expression lhs, Variable rhs);
            friend Expression operator-(Expression lhs, Expression rhs);

            friend Expression operator-(double lhs, Variable rhs);
            friend Expression operator-(double lhs, Expression rhs);
            /////////////////////////////////////////////////////

            /////////////////////////////////////////////////////
            // multiplication
            /////////////////////////////////////////////////////
            friend Expression operator*(Variable lhs, double rhs);
            friend Expression operator*(Variable lhs, Expression rhs);
            friend Expression operator*(Variable lhs, Variable rhs);

            friend Expression operator*(Expression lhs, double rhs);
            friend Expression operator*(Expression lhs, Variable rhs);
            friend Expression operator*(Expression lhs, Expression rhs);

            friend Expression operator*(double lhs, Variable rhs);
            friend Expression operator*(double lhs, Expression rhs);
            /////////////////////////////////////////////////////

            /////////////////////////////////////////////////////
            // division
            /////////////////////////////////////////////////////
            friend Expression operator/(Variable lhs, double rhs);
            friend Expression operator/(Variable lhs, Expression rhs);
            friend Expression operator/(Variable lhs, Variable rhs);

            friend Expression operator/(Expression lhs, double rhs);
            friend Expression operator/(Expression lhs, Variable rhs);
            friend Expression operator/(Expression lhs, Expression rhs);

            friend Expression operator/(double lhs, Variable rhs);
            friend Expression operator/(double lhs, Expression rhs);
            /////////////////////////////////////////////////////

            /////////////////////////////////////////////////////
            // exponent
            /////////////////////////////////////////////////////
            friend Expression pow(Variable lhs, double rhs);
            friend Expression pow(Variable lhs, Expression rhs);
            friend Expression pow(Variable lhs, Variable rhs);

            friend Expression pow(Expression lhs, double rhs);
            friend Expression pow(Expression lhs, Variable rhs);
            friend Expression pow(Expression lhs, Expression rhs);

            friend Expression pow(double lhs, Variable rhs);
            friend Expression pow(double lhs, Expression rhs);
            /////////////////////////////////////////////////////

            double operator()(const Values& values) const;

        private:
            using Op = double(*)(double, double);

            Expression() = default;

            friend Expression VariableDouble(Variable lhs, double rhs, Op op);
            friend Expression VariableExpression(Variable lhs, Expression rhs, Op op);
            friend Expression VariableVariable(Variable lhs, Variable rhs, Op op);

            friend Expression ExpressionDouble(Expression lhs, double rhs, Op op);
            friend Expression ExpressionVariable(Expression lhs, Variable rhs, Op op);
            friend Expression ExpressionExpression(Expression lhs, Expression rhs, Op op);

            friend Expression doubleVariable(double lhs, Variable rhs, Op op);
            friend Expression doubleExpression(double lhs, Expression rhs, Op op);

            std::function<double(const Values&)> expression;
            Variables variables;
        };
    }
}

#endif
