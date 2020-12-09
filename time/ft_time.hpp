#ifndef FT_TIME_HPP
#define FT_TIME_HPP

#include <ctime>	// time_t, struct tm

struct tm	*ft_gmtime(time_t const *rawtime);
struct tm	*ft_localtime(time_t const *rawtime);

#endif