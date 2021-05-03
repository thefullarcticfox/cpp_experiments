#include "hashtable.hpp"
#include <iostream>
#include <unordered_map>

int		main() {
	std::hash<std::string>	hashfunc;

	std::cout << hashfunc("hello") << std::endl;
	std::cout << hashfunc("hello") << std::endl;
	std::cout << hashfunc("hello2") << std::endl;
}
