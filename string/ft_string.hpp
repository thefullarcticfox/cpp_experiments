#ifndef FT_STRING_HPP
#define FT_STRING_HPP

#include <string>
#include <vector>

/* ft_match			*/
bool		ft_match(std::string const &s1, std::string const &s2);

/* ft_splitstring	*/
typedef std::vector<std::string>	t_strvect;
t_strvect	ft_splitstring(std::string str, std::string const &delim);
t_strvect	ft_splitstringbyany(std::string str, std::string const &delim);

/* ft_tostring		*/
std::string			ft_tostring(int val);
std::string			ft_tostring(long val);
std::string			ft_tostring(long long val);
std::string			ft_tostring(unsigned val);
std::string			ft_tostring(unsigned long val);
std::string			ft_tostring(unsigned long long val);
std::string			ft_tostring(float val);
std::string			ft_tostring(double val);
std::string			ft_tostring(long double val);

/* ft_stringto		*/
int					ft_stoi(std::string const &str);
long				ft_stol(std::string const &str);
long long			ft_stoll(std::string const &str);
unsigned int		ft_stou(std::string const &str);
unsigned long		ft_stoul(std::string const &str);
unsigned long long	ft_stoull(std::string const &str);
float				ft_stof(std::string const &str);
double				ft_stod(std::string const &str);
long double			ft_stold(std::string const &str);

#endif