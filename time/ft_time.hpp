#ifndef FT_TIME_HPP
#define FT_TIME_HPP

#include <ctime>	// time_t, struct tm

struct tm*	ft_gmtime(const time_t* rawtime);
struct tm*	ft_localtime(const time_t* rawtime);

#endif
