/*
**	https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic
*/

#include <iostream>
#include <limits>
#include <vector>
#include <stdexcept>
using uint = unsigned int;

std::vector<uint>	bigfactorial(const uint factorial_limit, const uint base = 10) {
	std::vector<uint>	digits(1, 1);			//	The big number starts with 1
	digits.reserve(1000);

	for (uint n = 1; n <= factorial_limit; n++) {
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

int		main() {
	uint				factorial_limit = 35;
	std::vector<uint>	res = bigfactorial(factorial_limit, 10);

	std::cout << std::endl << factorial_limit << "! = ";
	for (auto digit : res)
		std::cout << digit;
	std::cout << std::endl;

	return (0);
}
