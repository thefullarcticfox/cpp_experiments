/*
**	ft_tostring
**	just a c++98 compatible conversion of numbers to strings
*/

#include <string>
#include <sstream>

std::string		ft_tostring(int val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(long val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(long long val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(unsigned val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(unsigned long val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(unsigned long long val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(float val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(double val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

std::string 	ft_tostring(long double val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}
