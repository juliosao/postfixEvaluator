#pragma once

#include <string>
#include <exception>
#include <map>
#include <stack>
#include <functional>

namespace eval
{
    /**
     * This is the prototype that "plugins" require to match
    */
    typedef std::function<void(std::stack<std::string>&)> _operator;

    class evalException: public std::exception{
        public:
            evalException(const std::string& msg);
            const char* what();
        private:
            std::string msg;
    }; /**< Generic eval exception */

    /**
     * \class missingOperand
     * \brief Raise d when one or more operands are missing 
     */
    class missingOperand: public evalException{
        public:
            missingOperand(const std::string& op);
    }; 
    
    /**
     * \class notValidExpression
     * \brief Raised when a expression is not well-formed
     */
    class notValidExpression: public evalException{
        public:
            notValidExpression(std::stack<std::string>& st);
        private:
            static std::string parseStack(std::stack<std::string>& st);
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
            void defineOperator(const std::string& name, _operator implementation);

            /**
             * \fn addOperand(const std::string& value);
             * \brief Adds an operand to the evaluator stak (For debug purposes)
            */
            void evaluateToken(const std::string& token);

        private:
            std::stack<std::string> operands; /**< stack for data */
            std::map<std::string,_operator> validOperators; /**< valid operators registered in the evaluator */
    };

    /**
     * \fn eval(std::string src);
     * \brief This function is a shorthand function that evaluates a simple postfix expression without additions and returns a double with the result
    */
    std::string eval(std::string src);
}
