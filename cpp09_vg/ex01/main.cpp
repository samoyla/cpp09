#include "RPN.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return EXIT_FAILURE;
    }
    else
        return calculator(std::string(av[1]));
}