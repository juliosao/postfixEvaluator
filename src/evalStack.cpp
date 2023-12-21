#include <evalStack.h>

namespace eval
{
    stack_exception::stack_exception():
        std::runtime_error("Empty stack")
    {}

    std::string eval_stack::pop()
    {
        if(empty())
            throw stack_exception();

        std::string data = back();
        pop_back();
        return data;
    }

    void eval_stack::push(const std::string& s)
    {
        push_back(s);
    }
};