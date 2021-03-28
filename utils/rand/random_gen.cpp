/*
**	thanks to https://kt48.wordpress.com/2015/07/13/random-number-generator-without-rand-function/
**	and https://stackoverflow.com/a/7603688
*/

#include <iostream>
#include <climits>

class random_gen {
private:
	unsigned long	lfsr, bit, t;
	unsigned long	start, end;
public:
	explicit
	random_gen(unsigned long start = 0, unsigned long end = 0UL - 1) :
		lfsr(0xACE1u), bit(0), t(0), start(start), end(end) {}

	unsigned long	getnum() {
		if (start == end)
			return start;

		int*	p = new int;
		t = t ^ (unsigned long)(p);

		bit		= ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
		lfsr	= ((bit << 15) | (lfsr >> 1) | t) % end;

		while (lfsr < start)
			lfsr = lfsr + end - start;

		delete (p);
		return (lfsr);
	}
};

int main()
{
	random_gen	gen(0, 0U - 1);
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
	std::cout << gen.getnum() << std::endl;
    return (0);
}
