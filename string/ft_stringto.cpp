/*
**	ft_sto*
**	just a c++98 compatible conversion of strings to numbers
*/

#include <string>
#include <sstream>
#include <exception>

int					ft_stoi(std::string const &str)
{
	std::istringstream	iss(str);
	int					val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoi"));
	return (val);
}

long				ft_stol(std::string const &str)
{
	std::istringstream	iss(str);
	long				val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stol"));
	return (val);
}

long long			ft_stoll(std::string const &str)
{
	std::istringstream	iss(str);
	long long			val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoll"));
	return (val);
}

unsigned int		ft_stou(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned int		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stou"));
	return (val);
}

unsigned long		ft_stoul(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoul"));
	return (val);
}

unsigned long long	ft_stoull(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoull"));
	return (val);
}

float				ft_stof(std::string const &str)
{
	std::stringstream	iss;
	if (str.size() > 0 && str.at(str.size() - 1) == 'f')
		iss << str.substr(0, str.size() - 1);
	else
		iss << str;
	float				val = 0;

	if (!(iss >> val))	//	this fails on macOS for some reason if string contains f
		throw (std::out_of_range("stof"));
	return (val);
}

double				ft_stod(std::string const &str)
{
	std::istringstream	iss(str);
	double				val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stod"));
	return (val);
}

long double			ft_stold(std::string const &str)
{
	std::istringstream	iss(str);
	long double			val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stold"));
	return (val);
}
