/*
**	localtime function replacement (does not support dst timezones yet)
**	made it in case i ever needed to convert from unix timestamp to tm struct
**	compile with:
**	clang++ -g -Wall -Wextra -Werror ft_localtime.cpp -o ft_localtime && ./ft_localtime
*/

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>	// time_t, struct tm, localtime, strftime

#define TZ_OFFSET	3
#define	TZ_NAME		"MSK"

struct tm	*ft_localtime(time_t const *rawtime, int gmtoff = TZ_OFFSET, char const *tzname = TZ_NAME)
{
	struct tm	*res = new struct tm;

	res->tm_sec = 0;		// Seconds.			[0-60] (1 leap second)
	res->tm_min = 0;		// Minutes.			[0-59]
	res->tm_hour = 0;		// Hours.			[0-23]
	res->tm_mday = 0;		// Day.				[1-31]
	res->tm_mon = 0;		// Month.			[0-11]
	res->tm_year = 70;		// Year	- 1900.		[1970-...]
	res->tm_wday = 4;		// Day of week.		[0-6]
	res->tm_yday = 0;		// Days in year.	[0-365]
	res->tm_isdst = 0;		// DST.				[-1/0/1]
	#if defined(__USE_MISC) || defined(__DARWIN_STRUCT_STAT64)
		res->tm_hour = gmtoff;				// If supports timezones.
		res->tm_gmtoff = 3600L * gmtoff;	// Seconds east of UTC.
		res->tm_zone = tzname;				// Timezone abbreviation.
	#endif

	if (*rawtime < 0)
		return (res);
	time_t	timepart = (*rawtime) % 86400;
	time_t	datepart = (*rawtime) / 86400;

	res->tm_sec += timepart % 60;
	timepart /= 60;
	res->tm_min += timepart % 60;
	timepart /= 60;
	res->tm_hour += timepart;
	if (res->tm_hour > 23)
		datepart++;
	if (res->tm_hour < 0)
	{
		res->tm_hour += 23;
		datepart--;
	}
	res->tm_hour %= 24;

	res->tm_wday = (datepart + 4) % 7;
	int	daysinmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while (datepart > 0)
	{
		/*
			if (year is not divisible by 4) then (it is a common year)
			else if (year is not divisible by 100) then (it is a leap year)
			else if (year is not divisible by 400) then (it is a common year)
			else (it is a leap year)
		*/
		if (res->tm_year % 4 != 0)
			daysinmonth[1] = 28;
		else if (res->tm_year % 100 != 0)
			daysinmonth[1] = 29;
		else if (res->tm_year % 400 != 0)
			daysinmonth[1] = 28;
		else
			daysinmonth[1] = 29;

		int yday = 0;
		int month = -1;
		while (++month < 12 && daysinmonth[month] < datepart)
		{
			yday += daysinmonth[month];
			datepart -= daysinmonth[month];
		}
		if (month < 12 && datepart <= daysinmonth[month])
		{
			res->tm_mon = month;
			if (datepart < daysinmonth[month])
				res->tm_mday = datepart % daysinmonth[month];
			else
				res->tm_mday = datepart;
			res->tm_yday = yday + datepart - 1;
			break ;
		}
		res->tm_year++;
	}

	return (res);
}

int			main(void)
{
	time_t	rawtime = time(NULL);
	while (rawtime > 0 && rawtime < 1777777777)
	{
		char		str1[100], str2[100];
		struct tm	*res1, *res2;

		std::cout << "rawtime: " << rawtime << std::endl;
		res1 = localtime(&rawtime);
		if (strftime(str1, sizeof(str1), "%a, %d %b %Y %T %z", res1))
			std::cout << str1 << std::endl;
		res2 = ft_localtime(&rawtime);
		if (strftime(str2, sizeof(str2), "%a, %d %b %Y %T %z", res2))
			std::cout << str2 << std::endl;

		std::stringstream	ss1, ss2;
		ss1 << res1->tm_sec << " " << res1->tm_min << " " << res1->tm_hour << " " <<
			res1->tm_mday << " " << res1->tm_mon << " " << res1->tm_year << " " << res1->tm_wday << " " <<
			res1->tm_yday << " " << res1->tm_isdst << " " << res1->tm_gmtoff << " " << res1->tm_zone;
		ss2 << res2->tm_sec << " " << res2->tm_min << " " << res2->tm_hour << " " <<
			res2->tm_mday << " " << res2->tm_mon << " " << res2->tm_year << " " << res2->tm_wday << " " <<
			res2->tm_yday << " " << res2->tm_isdst << " " << res2->tm_gmtoff << " " << res2->tm_zone;
		delete(res2);

		if (ss1.str() != ss2.str())
		{
			std::cerr << "errored at " << rawtime << std::endl <<
				ss1.str() << std::endl << ss2.str() << std::endl;
			return (1);
		}
		rawtime += 123;
		std::cout << "-------------------------------" << std::endl;
	}

	return (0);
}
