/*
**	template versions of ft_stringto and ft_tostring
**	just a c++98 compatible conversions
**	Usage:
**	string	str = ft_stringto_T(val);
**	type	val = ft_tostring_T<type>(str);
*/

#ifndef FT_STRNUM_IPP
#define FT_STRNUM_IPP

#include <string>
#include <sstream>

template <typename T>
std::string	ft_stringto_T(T val)
{
	std::ostringstream	oss;
	oss << val;
	return (oss.str());
}

template <typename T>
T			ft_tostring_T(const std::string& str)
{
	std::istringstream	iss(str);
	T	val = 0;

	if (!(iss >> val))
		return (0);
	return (val);
}

#endif
