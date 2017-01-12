#include "Expression.hpp"

#include <sstream>

#include "Exception.hpp"

namespace dbr
{
    namespace algebra
    {
        /////////////////////////////////////////////////////
        // addition
        /////////////////////////////////////////////////////
        static double plus(double lhs, double rhs)
        {
            return lhs + rhs;
        }

        Expression operator+(Variable lhs, double rhs)
        {
            return VariableDouble(lhs, rhs, plus);
        }

        Expression operator+(Variable lhs, Expression rhs)
        {
            return VariableExpression(lhs, rhs, plus);
        }

        Expression operator+(Variable lhs, Variable rhs)
        {
            return VariableVariable(lhs, rhs, plus);
        }

        Expression operator+(Expression lhs, double rhs)
        {
            return ExpressionDouble(lhs, rhs, plus);
        }

        Expression operator+(Expression lhs, Variable rhs)
        {
            return ExpressionVariable(lhs, rhs, plus);
        }

        Expression operator+(Expression lhs, Expression rhs)
        {
            return ExpressionExpression(lhs, rhs, plus);
        }

        Expression operator+(double lhs, Variable rhs)
        {
            return doubleVariable(lhs, rhs, plus);
        }

        Expression operator+(double lhs, Expression rhs)
        {
            return doubleExpression(lhs, rhs, plus);
        }
        /////////////////////////////////////////////////////

        /////////////////////////////////////////////////////
        // subtraction
        /////////////////////////////////////////////////////
        static double minus(double lhs, double rhs)
        {
            return lhs - rhs;
        }

        Expression operator-(Variable lhs, double rhs)
        {
            return VariableDouble(lhs, rhs, minus);
        }

        Expression operator-(Variable lhs, Expression rhs)
        {
            return VariableExpression(lhs, rhs, minus);
        }

        Expression operator-(Variable lhs, Variable rhs)
        {
            return VariableVariable(lhs, rhs, minus);
        }

        Expression operator-(Expression lhs, double rhs)
        {
            return ExpressionDouble(lhs, rhs, minus);
        }

        Expression operator-(Expression lhs, Variable rhs)
        {
            return ExpressionVariable(lhs, rhs, minus);
        }

        Expression operator-(Expression lhs, Expression rhs)
        {
            return ExpressionExpression(lhs, rhs, minus);
        }

        Expression operator-(double lhs, Variable rhs)
        {
            return doubleVariable(lhs, rhs, minus);
        }

        Expression operator-(double lhs, Expression rhs)
        {
            return doubleExpression(lhs, rhs, minus);
        }
        /////////////////////////////////////////////////////

        /////////////////////////////////////////////////////
        // multiplication
        /////////////////////////////////////////////////////
        static double mult(double lhs, double rhs)
        {
            return lhs * rhs;
        }

        Expression operator*(Variable lhs, double rhs)
        {
            return VariableDouble(lhs, rhs, mult);
        }

        Expression operator*(Variable lhs, Expression rhs)
        {
            return VariableExpression(lhs, rhs, mult);
        }

        Expression operator*(Variable lhs, Variable rhs)
        {
            return VariableVariable(lhs, rhs, mult);
        }

        Expression operator*(Expression lhs, double rhs)
        {
            return ExpressionDouble(lhs, rhs, mult);
        }

        Expression operator*(Expression lhs, Variable rhs)
        {
            return ExpressionVariable(lhs, rhs, mult);
        }

        Expression operator*(Expression lhs, Expression rhs)
        {
            return ExpressionExpression(lhs, rhs, mult);
        }

        Expression operator*(double lhs, Variable rhs)
        {
            return doubleVariable(lhs, rhs, mult);
        }

        Expression operator*(double lhs, Expression rhs)
        {
            return doubleExpression(lhs, rhs, mult);
        }
        /////////////////////////////////////////////////////

        /////////////////////////////////////////////////////
        // division
        /////////////////////////////////////////////////////
        static double div(double lhs, double rhs)
        {
            return lhs / rhs;
        }

        Expression operator/(Variable lhs, double rhs)
        {
            return VariableDouble(lhs, rhs, div);
        }

        Expression operator/(Variable lhs, Expression rhs)
        {
            return VariableExpression(lhs, rhs, div);
        }

        Expression operator/(Variable lhs, Variable rhs)
        {
            return VariableVariable(lhs, rhs, div);
        }

        Expression operator/(Expression lhs, double rhs)
        {
            return ExpressionDouble(lhs, rhs, div);
        }

        Expression operator/(Expression lhs, Variable rhs)
        {
            return ExpressionVariable(lhs, rhs, div);
        }

        Expression operator/(Expression lhs, Expression rhs)
        {
            return ExpressionExpression(lhs, rhs, div);
        }

        Expression operator/(double lhs, Variable rhs)
        {
            return doubleVariable(lhs, rhs, div);
        }

        Expression operator/(double lhs, Expression rhs)
        {
            return doubleExpression(lhs, rhs, div);
        }
        /////////////////////////////////////////////////////

        /////////////////////////////////////////////////////
        // exponent
        /////////////////////////////////////////////////////
        Expression pow(Variable lhs, double rhs)
        {
            return VariableDouble(lhs, rhs, std::pow);
        }

        Expression pow(Variable lhs, Expression rhs)
        {
            return VariableExpression(lhs, rhs, std::pow);
        }

        Expression pow(Variable lhs, Variable rhs)
        {
            return VariableVariable(lhs, rhs, std::pow);
        }

        Expression pow(Expression lhs, double rhs)
        {
            return ExpressionDouble(lhs, rhs, std::pow);
        }

        Expression pow(Expression lhs, Variable rhs)
        {
            return ExpressionVariable(lhs, rhs, std::pow);
        }

        Expression pow(Expression lhs, Expression rhs)
        {
            return ExpressionExpression(lhs, rhs, std::pow);
        }

        Expression pow(double lhs, Variable rhs)
        {
            return doubleVariable(lhs, rhs, std::pow);
        }

        Expression pow(double lhs, Expression rhs)
        {
            return doubleExpression(lhs, rhs, std::pow);
        }
        /////////////////////////////////////////////////////
        
        double Expression::operator()(const Values& values) const
        {
            return expression(values);
        }
        
        Expression VariableDouble(Variable lhs, double rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.emplace(lhs);
            ret.expression = [=](const Values& values)
            {
                auto it = values.find(lhs);
                if(it != values.end())
                {
                    return op(it->second, rhs);
                }
                else
                {
                    std::ostringstream ss;
                    ss << lhs << " is missing.";
                    throw Exception{ss.str()};
                }
            };

            return ret;
        }

        Expression VariableExpression(Variable lhs, Expression rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.emplace(lhs);
            ret.variables.insert(rhs.variables.begin(), rhs.variables.end());

            ret.expression = [=](const Values& values)
            {
                auto it = values.find(lhs);
                if(it != values.end())
                {
                    return op(it->second, rhs(values));
                }
                else
                {
                    std::ostringstream ss;
                    ss << lhs << " is missing.";
                    throw Exception{ss.str()};
                }
            };

            return ret;
        }

        Expression VariableVariable(Variable lhs, Variable rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.emplace(lhs);
            ret.variables.emplace(rhs);

            ret.expression = [=](const Values& values)
            {
                auto itL = values.find(lhs);
                auto itR = values.find(rhs);
                const Variable* missing = nullptr;

                if(itL == values.end())
                    missing = &lhs;
                
                if(itR == values.end())
                    missing = &rhs;

                if(missing != nullptr)
                {
                    std::ostringstream ss;
                    ss << *missing << " is missing.";
                    throw Exception{ss.str()};
                }

                return op(itL->second, itR->second);
            };

            return ret;
        }

        Expression ExpressionDouble(Expression lhs, double rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.insert(lhs.variables.begin(), lhs.variables.end());

            ret.expression = [=](const Values& values)
            {
                return op(lhs(values), rhs);
            };

            return ret;
        }
        
        Expression ExpressionVariable(Expression lhs, Variable rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.emplace(rhs);
            ret.variables.insert(lhs.variables.begin(), lhs.variables.end());

            ret.expression = [=](const Values& values)
            {
                auto it = values.find(rhs);
                if(it != values.end())
                {
                    return op(lhs(values), it->second);
                }
                else
                {
                    std::ostringstream ss;
                    ss << rhs << " is missing.";
                    throw Exception{ss.str()};
                }
            };

            return ret;
        }

        Expression ExpressionExpression(Expression lhs, Expression rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.insert(lhs.variables.begin(), lhs.variables.end());
            ret.variables.insert(rhs.variables.begin(), rhs.variables.end());

            ret.expression = [=](const Values& values)
            {
                return op(lhs(values), rhs(values));
            };

            return ret;
        }
        
        Expression doubleVariable(double lhs, Variable rhs, Expression::Op op)
        {
            Expression ret;

            ret.variables.emplace(rhs);
            ret.expression = [=](const Values& values)
            {
                auto it = values.find(rhs);
                if(it != values.end())
                {
                    return op(lhs, it->second);
                }
                else
                {
                    std::ostringstream ss;
                    ss << rhs << " is missing.";
                    throw Exception{ss.str()};
                }
            };

            return ret;
        }

        Expression doubleExpression(double lhs, Expression rhs, Expression::Op op)
        {
            Expression ret;
            
            ret.variables.insert(rhs.variables.begin(), rhs.variables.end());

            ret.expression = [=](const Values& values)
            {
                return op(lhs , rhs(values));
            };

            return ret;
        }
    }
}
