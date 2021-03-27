#ifndef FT_STRING_HPP
#define FT_STRING_HPP

#include <string>
#include <vector>

/* ft_match			*/
bool				ft_match(const std::string& s1, const std::string& s2);

/* ft_splitstring	*/
typedef std::vector<std::string>	t_strvect;
t_strvect			ft_splitstring(std::string str, const std::string& delim);
t_strvect			ft_splitstringbyany(std::string str, const std::string& delim);

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
int					ft_stoi(const std::string& str);
long				ft_stol(const std::string& str);
long long			ft_stoll(const std::string& str);
unsigned int		ft_stou(const std::string& str);
unsigned long		ft_stoul(const std::string& str);
unsigned long long	ft_stoull(const std::string& str);
float				ft_stof(const std::string& str);
double				ft_stod(const std::string& str);
long double			ft_stold(const std::string& str);

#endif
