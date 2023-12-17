#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <cctype>
#include "eval.h"

namespace eval
{    
    enum tokenType {
        none,
        number,
        name,
        symbol,
        string
    };
        
    evalException::evalException(const std::string& m):
        msg(m)
    {}

    const char* evalException::what()
    {
        return msg.c_str();
    }

    missingOperand::missingOperand(const std::string& op):
        evalException("Not enough arguments for opcode: " + op)
    {}

    notValidExpression::notValidExpression(std::stack<std::string>& st):
        evalException(parseStack(st))
    {}

    std::string notValidExpression::parseStack(std::stack<std::string>& st)
    {
        std::string tmp = "Stack:\n";

        while(!st.empty())
        {
            tmp += "\t" + st.top() +"\n";
            st.pop();
        }
        return tmp;
    }

    void add (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand("add");

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();

        src.push( std::to_string(s1+s2) );
    }

    void sub (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand("sub");
        
        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();            

        src.push( std::to_string(s1-s2) );
    }

    void mul (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand("mul");

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();

        src.push( std::to_string(s1*s2) );
    }

    void div (std::stack<std::string>& src)
    {
        if(src.size() < 2)
            throw missingOperand("div");

        double s2 = atof(src.top().c_str());
        src.pop();

        double s1 = atof(src.top().c_str());
        src.pop();     

        src.push( std::to_string(s1/s2) );
    }

    void print(std::stack<std::string>& src)
    {
        if(src.size() < 1)
            throw missingOperand("print");

        auto top = src.top();        
        long number = atol(top.c_str());
        unsigned long writed = 0;
        src.pop();

        if(src.size() < number)
            throw missingOperand("print (" + top + " tokens)");
        
        while(number > 0)
        {
            top = src.top();
            std::cout << top;
            src.pop();
            writed += top.size();
            number--;
        }
        
        std::cout << std::endl;
        src.push(std::to_string(writed));
    }

    void pop(std::stack<std::string>& src)
    {
        if(src.size() < 1)
            throw missingOperand("pop");
        src.pop();     
    }

    void dup(std::stack<std::string>& src)
    {
        if(src.size() < 1)
            throw missingOperand("dup");
        src.push(src.top());
    }

    void read(std::stack<std::string>& src)
    {
        std::string s;
        std::cin >> s;
        src.push(s);
    }

    evaluator::evaluator():
        validOperators{
            {"+",eval::add},
            {"-",eval::sub},
            {"*",eval::mul},
            {"/",eval::div},
            {"read",eval::read},
            {"print",eval::print},
            {"pop",eval::pop},
            {"dup",eval::dup}},
        operands()
    {};


    void evaluator::evaluateToken(const std::string& token)
    {
        
        auto pos = validOperators.find(token);
        if(pos != validOperators.end())
            pos->second(operands);
        else
            operands.push(token);
    }


    void evaluator::defineOperator(const std::string& name, _operator implementation)
    {
        validOperators[name]=implementation;
    }

    std::string evaluator::evaluate(std::string src)
    {
        std::string tmp="";
        tokenType last = tokenType::none;

        for(char c: src)
        {
            //std::cout << "Tmp: '" << tmp << "' Curent: '" << c << "' last:" << last << std::endl;

            if(isdigit(c))
            {
                if(last == tokenType::symbol)
                {                    
                    if(tmp.size() != 0 && tmp != "-")
                    {                        
                        evaluateToken(tmp);
                        tmp.clear();                   
                    }

                    last = tokenType::number;
                }
                tmp += c;
            }
            else if(isalpha(c))
            {
                if(last != tokenType::name && last != tokenType::string)
                {
                    if(tmp.size() != 0 && tmp != "$")
                    {
                        evaluateToken(tmp);
                        tmp.clear();
                    }
                        
                    last = tokenType::name;
                }
                tmp += c;
            }
            else if(isblank(c))
            {
                if(last == tokenType::string)
                    tmp += c;
                else if(tmp.size() != 0)
                {
                    evaluateToken(tmp);
                    tmp.clear();
                    last = tokenType::none;
                }
            }
            else if(ispunct(c))
            {                
                switch (c)
                {
                case '"':
                    if(last != tokenType::string)
                    {
                        if(tmp.size() != 0)
                        {
                            evaluateToken(tmp);
                            tmp.clear();
                        }

                        last = tokenType::string;
                    }
                    else
                    {
                        evaluateToken(tmp);
                        tmp.clear();
                        last = tokenType::none;
                    }
                    break;                
                default:
                    if(last != tokenType::symbol)
                    {
                        if(tmp.size() != 0)
                        {
                            evaluateToken(tmp);
                            tmp.clear();
                        }

                        last = tokenType::symbol;
                    }
                    tmp += c;
                }
            }
        }

        if(tmp.size() != 0)
        {
            evaluateToken(tmp);
        }
        
        if(operands.size() > 1)
            throw notValidExpression(operands);

        return operands.top();
    }

    std::string eval(std::string src)
    {      
        eval::evaluator ev;  
        return ev.evaluate(src);
    }
}


