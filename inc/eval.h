#pragma once

#include <string>
#include <stdexcept>
#include <map>
#include <vector>
#include <functional>

#include "evalStack.h"

namespace eval
{    
    /**
     * This is the prototype that "plugins" require to match
    */
    typedef std::function<void(eval_stack&)> _operator;

    /**
     * \class missingOperand
     * \brief Raise d when one or more operands are missing 
     */
    class missingOperand: public std::runtime_error{
        public:
            missingOperand(const std::string& op);
    }; 
    
    /**
     * \class notValidExpression
     * \brief Raised when a expression is not well-formed
     */
    class notValidExpression: public std::runtime_error{
        public:
            notValidExpression();
    }; 

    /**
     * \class evaluator
     * \brief A postfix evaluator class
     * This class evaluates math expression in postfix notation
    */
    class evaluator
    {
        public:
            /**
             * \fn evaluator
             * \brief Class constructor
            */
            evaluator();

            /**
             * \fn evaluate
             * \brief Evaluates a expression contained into a string
             * \param src Expression to evaluate
             * The expression must ve a valid postfix expression like "2 2 + 3 *"
            */
            std::string evaluate(std::string src);

            /**
             * \fn defineOperator(const std::string& name, _operator implementation);
             * \brief Adds a function to the evaluator
             * \param name The name of the function (For evaluation purposes)
             * \param implementation A function matching _evaluator typedef. This function will be called when its name is find into a expression
            */
            void defineOperator(const std::string& name, const _operator& implementation);

            /**
             * \fn addOperand(const std::string& value);
             * \brief Adds an operand to the evaluator stak (For debug purposes)
            */
            void evaluateToken(const std::string& token);

            /**
             * \fn setDebug(boolean v)
             * \brief Enables or disables debug mode
             * \param v Debug mode status (true: active, false:inactive)
            */
            void setDebug(bool v);

            /**
             * \fn push(std::string v);
             * \brief Pushes a value into stack
             * \param v Value to push
            */
            void push(std::string v);

            /**
             * \fn pop()
             * \brief Pops a value from the stack
             * \return The value obtained
            */
            std::string pop();

            /**
             * \fn getStackSize()
             * \return The number of values in the stack
            */
            unsigned long getStackSize();

            
        private:
            eval_stack operands; /**< stack for data */
            std::map<std::string,_operator> validOperators; /**< valid operators registered in the evaluator */
            bool debugMode;
        };  

    /**
     * \fn eval(std::string src);
     * \brief This function is a shorthand function that evaluates a simple postfix expression without additions and returns a double with the result
    */
    std::string eval(std::string src);
}
