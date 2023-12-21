#include <iostream>
#include <vector>
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
        

    missingOperand::missingOperand(const std::string& op):
        std::runtime_error("Not enough arguments for opcode: " + op)
    {}

    notValidExpression::notValidExpression():
        std::runtime_error("Not valid expression")
    {}

/*
    std::string notValidExpression::parseStack(eval_stack& st)
    {
        std::string tmp = "Stack:\n";

        while(!st.empty())
        {
            tmp += "\t" + st.top() +"\n";
            st.pop();
        }
        return tmp;
    }
*/

    void add (eval_stack& src)
    {
        double s2 = atof(src.pop().c_str());
        double s1 = atof(src.pop().c_str());
        src.push( std::to_string(s1+s2) );
    }

    void sub (eval_stack& src)
    {   
        double s2 = atof(src.pop().c_str());
        double s1 = atof(src.pop().c_str());
        src.push( std::to_string(s1-s2) );
    }

    void mul (eval_stack& src)
    {
        double s2 = atof(src.pop().c_str());
        double s1 = atof(src.pop().c_str());
        src.push( std::to_string(s1*s2) );
    }

    void div (eval_stack& src)
    {
        double s2 = atof(src.pop().c_str());
        double s1 = atof(src.pop().c_str());
        src.push( std::to_string(s1/s2) );
    }

    void print(eval_stack& src)
    {   
        long number = atol(src.pop().c_str());
        unsigned long writed = 0;

        while(number > 0)
        {
            auto top = src.pop();
            std::cout << top;
            writed += top.size();
            number--;
        }
        
        std::cout << std::endl;
        src.push(std::to_string(writed));
    }

    void pop(eval_stack& src)
    {
        auto number = atol(src.pop().c_str());
        while(number > 0)
        {
            src.pop();
            number --;
        }
    }

    void dup(eval_stack& src)
    {
        auto number = atol(src.pop().c_str());
        auto target = src.pop();
        number -= 1;

        while(number > 0)
        {
            src.push(target);
            number --;
        }
    }

    void read(eval_stack& src)
    {
        std::string s;
        std::getline(std::cin,s);
        src.push(s);
    }

    void swap(eval_stack& src)
    {
        std::string a = src.pop();
        std::string b = src.pop();

        src.push(a);
        src.push(b);
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
            {"dup",eval::dup},
            {"swap",eval::swap}},
        operands()
    {};

    unsigned long int evaluator::getStackSize()
    {
        return operands.size();
    }

    void evaluator::evaluateToken(const std::string& token)
    {        
        auto pos = validOperators.find(token);
        if(pos != validOperators.end())
        {
            if(debugMode)
                std::cout << "Execute: " << token << std::endl;  
            pos->second(operands);
        }
        else
        {
            if(debugMode)
                std::cout << "Push: " << token << std::endl;  
            operands.push(token);            
        }
    
        if(debugMode)
        {
            std::string notUsed;
            std::getline(std::cin,notUsed);
        }
    }


    void evaluator::defineOperator(const std::string& name, const _operator& implementation)
    {
        validOperators[name]=implementation;
    }

    std::string evaluator::evaluate(std::string src)
    {
        std::string tmp="";
        tokenType last = tokenType::none;

        while(!operands.empty())
            operands.pop();

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
            throw notValidExpression();

        return operands.pop();
    }

    void evaluator::setDebug(bool v)
    {
        debugMode = v;
    }

    std::string eval(std::string src)
    {      
        eval::evaluator ev;  
        return ev.evaluate(src);
    }
}


