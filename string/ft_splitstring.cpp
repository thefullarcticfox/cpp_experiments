/*
**	ft_splitstring and ft_splitstringbyany
**	splits string into a vector of words by delimiters
**	first one splits by delim sequence
**	second one splits by any symbol in delim sequence
*/

#include <string>
#include <vector>

typedef std::vector<std::string>	t_strvect;

t_strvect	ft_splitstring(std::string str, std::string const &delim)
{
	t_strvect		split;
	size_t			pos = 0;
	std::string		tmp;

	while ((pos = str.find(delim)) != std::string::npos)
	{
		tmp = str.substr(0, pos);
		if (!tmp.empty())
			split.push_back(tmp);
		str.erase(0, pos + delim.length());
	}
	if (!str.empty())
		split.push_back(str);
	return (split);
}

t_strvect	ft_splitstringbyany(std::string str, std::string const &delim)
{
	t_strvect		split;
	size_t			pos = 0;
	std::string		tmp;

	while ((pos = str.find_first_of(delim)) != std::string::npos)
	{
		tmp = str.substr(0, pos);
		if (!tmp.empty())
			split.push_back(tmp);
		str.erase(0, pos + 1);
	}
	if (!str.empty())
		split.push_back(str);
	return (split);
}