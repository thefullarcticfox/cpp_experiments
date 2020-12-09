#ifndef FT_STRNUM_IPP
#define FT_STRNUM_IPP

#include <string>
#include <sstream>

template <typename T>
std::string	ft_numtostr(T val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

template <typename T>
T			ft_strtonum(std::string const &str)
{
	std::istringstream	iss(str);
	T	val = 0;

	if (!(iss >> val))
		return (0);
	return (val);
}

#endif