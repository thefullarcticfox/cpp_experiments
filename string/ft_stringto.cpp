/*
**	ft_sto*
**	just a c++98 compatible conversion of strings to numbers
*/

#include <string>
#include <sstream>
#include <limits>
#include <exception>

int					ft_stoi(const std::string& str)
{
	std::istringstream	iss(str);
	int					val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoi"));
	return (val);
}

long				ft_stol(const std::string& str)
{
	std::istringstream	iss(str);
	long				val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stol"));
	return (val);
}

long long			ft_stoll(const std::string& str)
{
	std::istringstream	iss(str);
	long long			val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoll"));
	return (val);
}

unsigned int		ft_stou(const std::string& str)
{
	std::istringstream	iss(str);
	unsigned int		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stou"));
	return (val);
}

unsigned long		ft_stoul(const std::string& str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoul"));
	return (val);
}

unsigned long long	ft_stoull(const std::string& str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		throw (std::out_of_range("stoull"));
	return (val);
}

float				ft_stof(const std::string& str)
{
	if (str.find("-nan") == 0)
		return (-std::numeric_limits<float>::quiet_NaN());
	if (str.find("nan") == 0 || str.find("+nan") == 0)
		return (std::numeric_limits<float>::quiet_NaN());
	if (str.find("-inf") == 0)
		return (-std::numeric_limits<float>::infinity());
	if (str.find("inf") == 0 || str.find("+inf") == 0)
		return (std::numeric_limits<float>::infinity());

	std::stringstream	iss;
	if (str.size() > 0 && str.at(str.size() - 1) == 'f')
		iss << str.substr(0, str.size() - 1);
	else
		iss << str;
	float				val = 0;

	if (!(iss >> val))	//	this fails on macOS for some reason if string contains f
		throw (std::invalid_argument("stof"));
	return (val);
}

double				ft_stod(const std::string& str)
{
	if (str.find("-nan") == 0)
		return (-std::numeric_limits<double>::quiet_NaN());
	if (str.find("nan") == 0 || str.find("+nan") == 0)
		return (std::numeric_limits<double>::quiet_NaN());
	if (str.find("-inf") == 0)
		return (-std::numeric_limits<double>::infinity());
	if (str.find("inf") == 0 || str.find("+inf") == 0)
		return (std::numeric_limits<double>::infinity());

	std::istringstream	iss(str);
	double				val = 0;

	if (!(iss >> val))
		throw (std::invalid_argument("stod"));
	return (val);
}

long double			ft_stold(const std::string& str)
{
	if (str.find("-nan") == 0)
		return (-std::numeric_limits<long double>::quiet_NaN());
	if (str.find("nan") == 0 || str.find("+nan") == 0)
		return (std::numeric_limits<long double>::quiet_NaN());
	if (str.find("-inf") == 0)
		return (-std::numeric_limits<long double>::infinity());
	if (str.find("inf") == 0 || str.find("+inf") == 0)
		return (std::numeric_limits<long double>::infinity());

	std::istringstream	iss(str);
	long double			val = 0;

	if (!(iss >> val))
		throw (std::invalid_argument("stold"));
	return (val);
}
