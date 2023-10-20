/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:20:37 by masamoil          #+#    #+#             */
/*   Updated: 2023/04/17 12:28:28 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cout << "This progam needs one argument, which must be a file !" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::ifstream myfile(av[1]);
	if(!myfile)
	{
		std::cout << "Error : could not open the file !" << std::endl;
	}
	else
	{
		std::string line;
		BitcoinExchange data = BitcoinExchange();
		data.fillMap();
		while(getline(myfile, line))
		{
			if (line.empty())
				continue ;
			else	
				data.evaluate(line);
		}
	}
	myfile.close();
	return 0;
}
