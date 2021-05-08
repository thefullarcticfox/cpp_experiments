#include "bloomfilter.hpp"
#include <iostream>
#include <string>

int		main() {
	{
		bloomfilter<std::string>	bloom(128);

		bloom.add("hello");
		std::cout << bloom.possiblyContains("hello") << std::endl;

		std::cout << bloom.possiblyContains("blablabla") << std::endl;
		bloom.add("blablabla");
		std::cout << bloom.possiblyContains("blablabla") << std::endl;
	}

	std::cout << "----------" << std::endl;

	{
		bloomfilter<std::string>	bloom2(128, 2);

		bloom2.add("hello");
		std::cout << bloom2.possiblyContains("hello") << std::endl;

		std::cout << bloom2.possiblyContains("blablabla") << std::endl;
		bloom2.add("blablabla");
		std::cout << bloom2.possiblyContains("blablabla") << std::endl;
	}
}
