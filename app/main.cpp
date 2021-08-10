#include <iostream>
#include "program.hpp"


int main(int argc, char const *argv[])
{
    Compiler::Program::Main({argv + 1, argc + argv});
    return 0;
}
