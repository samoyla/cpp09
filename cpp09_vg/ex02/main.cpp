#include "PmergeMe.hpp"

int main(int ac, char** av)
{
    if (ac < 2)
    {
        std::cout << "Error" <<std::endl;
        return EXIT_FAILURE;
    }
    std::deque<int> args;
    for (int i = 1; i < ac; ++i)
    {
        std::string argv(av[i]);
		if (!argv.size() || argv.find_first_not_of("0123456789 +") != std::string::npos || argv.size() > 10
			|| (argv.size() == 10 && atoi(argv.c_str()) > 2147483647) || atoi(argv.c_str()) < 0)
		{
			std::cout << "Error" << std::endl;
			return EXIT_FAILURE;
		}
		if (argv.find(' ') != std::string::npos)
		{
			std::cout << "Error" << std::endl;
			return EXIT_FAILURE;
		}
		args.push_back(std::atoi(argv.c_str()));
    }
    return MergeInsertSort(args);
}