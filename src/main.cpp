#include <iostream>
#include "eval.h"

int main(int argc, char **argv)
{
    argc--;
    argv++;

    try
    {
        eval::evaluator ev;
        while (argc > 0)
        {            
            std::cout << ev.evaluate(*argv) << std::endl;
            argc--;
            argv++;
        }        
    }
    catch(eval::evalException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}