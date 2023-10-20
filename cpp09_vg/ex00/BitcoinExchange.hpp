#ifndef BITCOINEXCHNGE_HPP
#define BITCOINEXCHNGE_HPP
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <algorithm>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &rhs);
		~BitcoinExchange();

		std::map<std::string, float> const &getMap(void) const;
		bool check_date();
		bool check_value();
		bool check_value_input();
		void fillMap();
		void evaluate(std::string line);
		void affiche_map();

	private:
		std::map<std::string, float> _map;
		std::string _date;
		std::string _value;
};

#endif