#include "RPN.hpp"

int calculator(std::string arg)
{
    std::stack<int> stack;
	for (std::string::iterator it = arg.begin(); it != arg.end(); ++it)
	{
		//std::cout << *it << std::endl;
		if(isdigit(*it))
			stack.push(*it - 48);
		else if (*it == ' ')
				continue;
		else if(stack.size() >= 2)
		{
			int op;
			if((*it) == '+')
			{
				op = stack.top();
				stack.pop();
				stack.top() = op + stack.top();
			}
			else if((*it) == '-')
			{
				op = stack.top();
				stack.pop();
				stack.top() = stack.top() - op;
			}
			else if((*it) == '*')
			{
				op = stack.top();
				stack.pop();
				stack.top() = op * stack.top();
			}
			else if((*it) == '/')
			{
				op = stack.top();
				stack.pop();
				if (op == 0)
				{
					std::cout << "When we try to divide by zero, things stop making sense" << std::endl;
					return EXIT_FAILURE;
				}
				else
					stack.top() = stack.top() / op;
			}
		}
		else
		{
			std::cout << "Error 1" << std::endl;
			return EXIT_FAILURE;
		}
	}
	if(stack.size() == 1)
	{
		std::cout << "Result : " << std::endl;
		std::cout << stack.top() << std::endl;
		return EXIT_SUCCESS;
	}
	std::cout << "Error 2" << std::endl;
    return EXIT_FAILURE;
}