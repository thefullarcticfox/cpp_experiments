/*
**	https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic
*/

#include <iostream>
#include <limits>
#include <vector>
#include <stdexcept>
using uint = unsigned int;

std::vector<uint>	bigfactorial(unsigned int factorial_limit) {
	const unsigned int	limit = 1000;
	const unsigned int	base = 10;

	uint				last = 0;
	std::vector<uint>	digits(limit, 0);
	digits.at(last) = 1;						//	The big number starts with 1

	for (uint n = 1; n <= factorial_limit; n++) {
		uint carry = 0;							//	Start a multiply by n
		for (uint i = 0; i <= last; i++) {		//	Step along every digit
			uint d = digits.at(i) * n + carry;	//	The classic multiply
			digits.at(i) = d % base;			// 	The low-order digit of the result
			carry = d / base;					//	The carry to the next digit
		}
		while (carry > 0) {						//	Store the carry in the big number
			if (++last >= limit)
				throw std::overflow_error("Overflow");
			digits.at(last) = carry % base;		//	Placed
			carry /= base;						//	The carry reduced
		}										//	With n >bBase, maybe > 1 digit extra

		for (uint i = last; i != std::numeric_limits<uint>::max(); --i) {
			std::cout << digits.at(i);
		}
		std::cout << " = " << n << "!" << std::endl;
	}

	return (std::vector<uint>(digits.rbegin() + (limit - last - 1), digits.rend()));
}

int		main() {
	uint				factorial_limit = 35;
	std::vector<uint>	res = bigfactorial(factorial_limit);

	std::cout << std::endl << factorial_limit << "! = ";
	for (auto digit : res)
		std::cout << digit;
	std::cout << std::endl;
	return (0);
}
