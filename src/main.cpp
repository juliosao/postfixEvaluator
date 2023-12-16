#include <iostream>
#include "eval.h"

void print(std::stack<std::string>& src)
{    
    std::cout << src.top() << std::endl;
}

void read(std::stack<std::string>& src)
{
    std::string s;
    std::cin >> s;
    src.push(s);
}

int main(int argc, char **argv)
{
    argc--;
    argv++;

    try
    {
        eval::evaluator ev;
        ev.defineOperator("print",print);
        ev.defineOperator("read",read);
        while (argc > 0)
        {            
            std::cout << ev.evaluate(*argv) << std::endl;
            argc--;
            argv++;
        }        
    }
    catch(char const* msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }

    return 0;
}