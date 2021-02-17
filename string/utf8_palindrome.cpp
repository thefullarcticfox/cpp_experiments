/*
**	pretty stupid palindrome checker
**	works only with latin and cyrillic utf8
*/

#include <iostream>
#include <string>
#include <vector>

unsigned short	utf8_2bytechartoint(const std::string& bytes)
{
	unsigned short	ucode = static_cast<unsigned char>(bytes[0]);
	ucode = (ucode << 8) | static_cast<unsigned char>(bytes[1]);
	return (ucode);
}

void			isutf8palindrome(const std::string& str)
{
	std::vector<unsigned short>		istr;

	for (size_t i = 0; i < str.size(); i++)
		if (str[i] >> 7)
			istr.push_back(utf8_2bytechartoint(str.substr(i++, 2)));
		else
			istr.push_back(str[i]);

	//	toupper
	for (size_t i = 0; i < istr.size(); i++)
	{
		if ((istr[i] >= utf8_2bytechartoint("а") &&
			istr[i] <= utf8_2bytechartoint("я")) ||
			(istr[i] >= 'a' && istr[i] <= 'z'))
		{
			if (istr[i] & (1 << 8))
				istr[i] -= 192;
			istr[i] -= 32;
		}
	}

	size_t	i = 0;
	size_t	j = istr.size() - 1;
	std::cout << "\"" << str << "\" is ";
	while (i != j && i < istr.size() && j > 0)
		if (istr[i++] != istr[j--])
		{
			std::cout << "not ";
			break ;
		}
	std::cout << "a palindrome" << std::endl;
}

int			main(int ac, char **av)
{
	std::cout << "А-Я is " << utf8_2bytechartoint("А") << "-" << utf8_2bytechartoint("Я") << std::endl;
	std::cout << "а-я is " << utf8_2bytechartoint("а") << "-" << utf8_2bytechartoint("я") << std::endl;
	isutf8palindrome("мАдаМ");
	isutf8palindrome("АдДа");
	isutf8palindrome("mАDаM");
	isutf8palindrome("АдДа");
	isutf8palindrome("комод");
	isutf8palindrome("Дом мод");
	isutf8palindrome("мм,.ада.,мм");
	isutf8palindrome("Рм,.ада.,мр");

	return (0);
}
