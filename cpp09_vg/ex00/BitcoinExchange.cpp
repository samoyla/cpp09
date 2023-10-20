#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): _date("Default"), _value("Default")
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if(this != &rhs)
	{
		_map = rhs._map;
		_date = rhs._date;
		_value = rhs._value;
	}
	return *this;
}

std::map<std::string, float> const &BitcoinExchange::getMap() const
{
	return this->_map;
}

BitcoinExchange::~BitcoinExchange(){}

bool BitcoinExchange::check_date()
{
	std::string year;
	std::string month;
	std::string day;
	std::string tmp;
	size_t pos;
	size_t ind;

	pos = _date.find('-');
	year = _date.substr(0, pos);
	tmp = _date.substr(pos + 1);
	pos = tmp.find('-');
	month = tmp.substr(0, pos);
	day = tmp.substr(pos + 1, 2);
	ind = _date.find_first_not_of("0123456789-");
	
	if (ind != std::string::npos)
		return false;
	else if (year.size() > 4 || month.size() > 2 || day.size() > 2)
		return false;
	else if (atoi(month.c_str()) < 1 || atoi(month.c_str()) > 12)
		return false;
	else if (atoi(month.c_str()) == 1 || atoi(month.c_str()) == 3 || atoi(month.c_str()) == 5 || atoi(month.c_str()) == 7
		|| atoi(month.c_str()) == 8 || atoi(month.c_str()) == 10 || atoi(month.c_str()) == 12)
	{
		if (atoi(day.c_str()) < 1 || atoi(day.c_str()) > 31)	
			return false;
	}
	else if (atoi(month.c_str()) == 4 || atoi(month.c_str()) ==  6 || atoi(month.c_str()) == 9 || atoi(month.c_str()) == 11)
	{
		if (atoi(day.c_str()) < 1 || atoi(day.c_str()) > 30)
			return false;
	}
	else if (atoi(month.c_str()) == 2)
	{
		if (atoi(day.c_str()) < 1 || atoi(day.c_str()) > 28)
		return false;
	}
	return true;
}

bool BitcoinExchange::check_value()
{
	size_t ind;

	ind = _value.find_first_not_of("0123456789.");
	if (ind != std::string::npos)
	{
		std::cout << "Error: not a number" << std::endl;
		return false;
	}
	else if(_value.size() > 10 || (_value.size() == 10 && atoi(_value.c_str()) > 2147483647))
	{
		std::cout << "Error: the number is too large" << std::endl;
		return false;
	}
	else if (atoi(_value.c_str()) < 0)
	{
		std::cout << "Error: not a positive number" << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::fillMap()
{
	std::ifstream data("data.csv");
	std::string line;
	size_t pos;

	if(data.is_open())
	{
		while (getline(data, line))
		{
			if (line.empty())
				continue ;
			else
			{
				pos = line.find(',');
				_date = line.substr(0, pos);
				_value = line.substr(pos + 1, std::string::npos);
				if (check_date() == false)
					continue ;
				if (check_value() == false)
					continue ;
				_map.insert(std::pair<std::string, float>(_date, atof(_value.c_str())));
			}
		}
	}
	else
		std::cout << "Error, could not open data file" << std::endl;
}

bool BitcoinExchange::check_value_input()
{
	size_t ind;
	ind = _value.find_first_not_of("0123456789.- ");

	if (ind != std::string::npos)
	{
		std::cout << "Error: not a number" << std::endl;
		return false;
	}
	_value.erase(std::remove_if(_value.begin(), _value.end(), ::isspace), _value.end());

	if(_value.empty())
	{
		std::cout << "Error : value is void" << std::endl;
		return false;
	}
	if(_value.size() > 10 || (_value.size() == 10 && atoi(_value.c_str()) > 2147483647))
	{
		std::cout << "Error: the number is too large" << std::endl;
		return false;
	}
	else if (atof(_value.c_str()) < 0)
	{
		if (_value[0] == '-')
		{
			std::cout << "Error: not a positive number" << std::endl;
			return false;
		}
		else
		{
			std::cout << "Error: not a number" << std::endl;
			return false;
		}
	}
	else if (atof(_value.c_str()) > 1000)
	{
		std::cout << "Error: the number is too large" << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::evaluate(std::string line)
{
	size_t pos;
	float res = 0;
	pos = line.find('|');
	if (line.find("|") == std::string::npos)
	{
			std::cout << "Error: bad input = > " << line << std::endl;
			return;
	}
	else{
		_date = line.substr(0, pos);
		_value = line.substr(pos + 1);
	}
	_date = line.substr(0, pos);
	_value = line.substr(pos + 1);
	_date.erase(std::remove_if(_date.begin(), _date.end(), ::isspace), _date.end());
	if (check_date() == false)
		std::cout << "Error: bad input = > " << line << std::endl;
	else if(check_value_input() == false)
		return ;
	else
	{
		std::string key = _date;
		if (this->_map.count(key))
		{
			float rate = _map[key];
			res = rate * atof(_value.c_str());
			std::cout << _date << " => " << _value << " = " << res << std::endl;
		}
		else
		{
			std::map<std::string, float>::iterator it;
			it = this->_map.lower_bound(this->_date);
			if (it == this->_map.begin())
				std::cout << "Error: no data before this date" << std::endl;
			else if (it == this->_map.end())
				std::cout << "Error: no data after this date" << std::endl;
			else
			{
				--it;
				res = it->second * atof(this->_value.c_str());
				std::cout << this->_date << " => " << this->_value << " = " << res << std::endl;
			}
		}
	}
		
}

void BitcoinExchange::affiche_map()
{
	for (std::map<std::string, float>::iterator it = _map.begin(); it != _map.end(); ++it)
	{
		std::cout << it->first << "   " << it->second << std::endl;
	}
}