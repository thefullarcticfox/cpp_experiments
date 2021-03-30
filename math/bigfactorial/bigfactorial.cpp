/*
**	Compile:	clang++ -g -Wall -Wextra -Werror -std=c++11 bigfactorial.cpp
**	Run:		./a.out <factorial> <base>
**	Default factorial is 35:	if not passed or value < 0 or value > 1000
**	Default base is 10:			if not passed or value < 2 or > 1000
**	*** Reference material ***
**	https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic
*/

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <stdexcept>
using uint = unsigned int;

std::vector<uint>	bigfactorial(const uint factorial, const uint base) {
	std::vector<uint>	digits(1, 1);			//	The big number starts with 1
	digits.reserve(1000);

	for (uint n = 1; n <= factorial; n++) {
		uint carry = 0;
		for (auto& digit : digits) {			//	Step along every digit
			uint d = digit * n + carry;			//	The classic multiply
			digit = d % base;					// 	The low-order digit of the result
			carry = d / base;					//	The carry to the next digit
		}

		while (carry > 0) {						//	Store the carry in the big number
			digits.push_back(carry % base);		//	Place
			carry /= base;						//	The carry reduced
		}

		for (auto it = digits.rbegin(); it != digits.rend(); it++)
			std::cout << *it;
		std::cout << " = " << n << "!" << std::endl;
	}

	return (std::vector<uint>(digits.rbegin(), digits.rend()));
}

std::vector<char>	generatealpha() {
	std::vector<char>	alpha;
	alpha.reserve('z' - 'a' + 11);
	for (int i = 0; i < 10; i++)
		alpha.push_back('0' + i);
	for (char c = 'a'; c <= 'z'; c++)
		alpha.push_back(c);
	return (alpha);
}

int		main(int ac, char** av) {
	uint	factorial = 35;
	uint	base = 10;

	if (ac > 1) {
		size_t	tmp = std::stoul(av[1]);
		if (tmp <= 1000)
			factorial = static_cast<uint>(tmp);
	}
	if (ac > 2) {
		size_t	tmp = std::stoul(av[2]);
		if (tmp > 1 && tmp <= 1000)
			base = static_cast<uint>(tmp);
	}

	std::vector<uint>	res = bigfactorial(factorial, base);

	std::cout << std::endl << factorial << "! = ";
	std::vector<char>	alpha = generatealpha();
	for (auto digit : res) {
		if (base <= alpha.size())
			std::cout << alpha.at(digit);
		else
			std::cout << digit << " ";
	}
	std::cout << std::endl;
	return (0);
}
