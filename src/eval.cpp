#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <cctype>
#include "eval.h"

namespace eval
{    
    const int DIGIT=0;
    const int OPERATOR=1;
    
    void add (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand();

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();

        src.push( std::to_string(s1+s2) );
    }

    void sub (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand();
        
        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();            

        src.push( std::to_string(s1-s2) );
    }

    void mul (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand();

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();

        src.push( std::to_string(s1*s2) );
    }

    void div (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand();

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();     

        src.push( std::to_string(s1/s2) );
    }

    evaluator::evaluator():
        validOperators{{"+",eval::add},{"-",eval::sub},{"*",eval::mul},{"/",eval::div}},
        operands()
    {};


    void evaluator::runOperator(const std::string& operand)
    {
        auto pos = validOperators.find(operand);
        if(pos != validOperators.end())
            pos->second(operands);
        else
            throw invalidToken();
    }

    void evaluator::addOperand(const std::string& value)
    {
        operands.push(value);
    }

    void evaluator::defineOperator(const std::string& name, _operator implementation)
    {
        validOperators[name]=implementation;
    }

    std::string evaluator::evaluate(std::string src)
    {
        std::string tmp="";
        int last = DIGIT;

        for(char c: src)
        {
            if(isdigit(c))
            {                                
                if(last != DIGIT)
                {   
                    if(tmp.size() != 0)
                    {                 
                        runOperator(tmp);
                        tmp.clear();                    
                    }
                    last = DIGIT;
                }
                tmp += c;           
            }
            else if( c == ' ' )
            {
                if(tmp.size() != 0)
                {
                    if(last == DIGIT)
                    {
                        addOperand(tmp);
                    }
                    else if(tmp.size() != 0)
                        runOperator(tmp);
                    tmp.clear();
                }
            }
            else
            {                    
                if(last != OPERATOR)
                {
                    if(tmp.size() != 0)
                    {
                        addOperand(tmp);                    
                        tmp.clear();
                    }
                    last = OPERATOR;
                }
                tmp += c;
            }
        }

        if(tmp.size() != 0)
        {
            if(last == DIGIT)
                addOperand(tmp);
            else
                runOperator(tmp);
        }
        
        if(operands.size() > 1)
            throw notValidExpression();

        return operands.top();
    }

    double eval(std::string src)
    {      
        eval::evaluator ev;  
        return atof(ev.evaluate(src).c_str());
    }
}


