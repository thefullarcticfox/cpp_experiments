/*
**	simple match
**	find out if s1 matches wildcard mask s2
*/

#include <string>

bool	ft_match(const std::string& s1, const std::string& s2)
{
	if (s1[0] == '\0' && s2[0] == '*')
		return (ft_match(s1, s2.substr(1)));
	if (s1[0] != '\0' && s2[0] == '*')
		return (ft_match(s1.substr(1), s2) || ft_match(s1, s2.substr(1)));
	if (s1[0] == s2[0] && s1[0] != '\0' && s1[0] != '\0')
		return (ft_match(s1.substr(1), s2.substr(1)));
	if (s1[0] == s2[0] && s1[0] == '\0' && s2[0] == '\0')
		return (true);
	return (false);
}
