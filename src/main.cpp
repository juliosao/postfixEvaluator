#include <iostream>
#include "eval.h"

const std::string argDebug("-d");

void help(eval::eval_stack& src)
{
    std::cout << "Valid operators:" << std::endl;
    std::cout << "help: Print this" << std::endl;
    std::cout << "A B +: Adds A and B and push result" << std::endl;
    std::cout << "A B -: Substract B from A and push result" << std::endl;
    std::cout << "A B *: Miltiplies B and A and push result" << std::endl;
    std::cout << "A B *: Divides A by B and push result" << std::endl;
    std::cout << "read: Reads line from STDIN and push result" << std::endl;
    std::cout << "<A elements> A print: Prints A element from the stack and push bytes written" << std::endl;
    std::cout << "<A elements> A pop: Removes A elements from the stack" << std::endl;
    std::cout << "A B dup: Push A B times into stack" << std::endl;
    std::cout << "A B swap: Push A after B into stack" << std::endl;    
}

int main(int argc, char **argv)
{
    bool debug=false;
    argc--;
    argv++;

    while(argc>0)
    {
        if( argDebug == *argv )
            debug = true;

        argc--;
        argv++;
    }

    try
    {    
        eval::evaluator ev; 
        ev.defineOperator("help",help);
        ev.setDebug(debug);
        
        while(std::cin.good())
        {        
            std::string line; 
            std::getline(std::cin,line);
            std::cout <<  ev.evaluate(line) << std::endl;
        }
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}