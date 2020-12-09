/*
**	ft_sto*
**	just a c++98 compatible conversion of strings to numbers
*/

#include <string>
#include <sstream>

int					ft_stoi(std::string const &str)
{
	std::istringstream	iss(str);
	int					val = 0;

	if (!(iss >> val))
		return (0);
	return (val);
}

long				ft_stol(std::string const &str)
{
	std::istringstream	iss(str);
	long				val = 0;

	if (!(iss >> val))
		return (0L);
	return (val);
}

long long			ft_stoll(std::string const &str)
{
	std::istringstream	iss(str);
	long long			val = 0;

	if (!(iss >> val))
		return (0LL);
	return (val);
}

unsigned int		ft_stou(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned int		val = 0;

	if (!(iss >> val))
		return (0U);
	return (val);
}

unsigned long		ft_stoul(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		return (0UL);
	return (val);
}

unsigned long long	ft_stoull(std::string const &str)
{
	std::istringstream	iss(str);
	unsigned long		val = 0;

	if (!(iss >> val))
		return (0ULL);
	return (val);
}

float				ft_stof(std::string const &str)
{
	std::istringstream	iss(str);
	float				val = 0;

	if (!(iss >> val))
		return (0.0F);
	return (val);
}

double				ft_stod(std::string const &str)
{
	std::istringstream	iss(str);
	double				val = 0;

	if (!(iss >> val))
		return (0.0);
	return (val);
}

long double			ft_stold(std::string const &str)
{
	std::istringstream	iss(str);
	long double			val = 0;

	if (!(iss >> val))
		return (0.0L);
	return (val);
}
