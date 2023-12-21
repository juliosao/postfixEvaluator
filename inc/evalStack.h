#pragma once

#include <stdexcept>
#include <vector>
#include <string>

namespace eval
{
    class stack_exception: public std::runtime_error{
        public:
            stack_exception();
    };

    class eval_stack: public std::vector<std::string>
    {
        public:
            std::string pop();
            void push(const std::string& so );
    };

}
