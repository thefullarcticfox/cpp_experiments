#include <functional>
#include <vector>

template< class T, class Hash = std::hash<T> >
class bloomfilter {
private:
	std::vector<bool>	_bits;
	unsigned short		_nhashes;
public:
	explicit
	bloomfilter(size_t size, short nhashes = 1) : _bits(size), _nhashes(nhashes) {}
	~bloomfilter() {}

	void	add(const T& data) {
		size_t	hash1 = Hash()(data) % 1000000;
		size_t	hash2 = Hash()(data) / 1000000;

		for (unsigned short i = 0; i < _nhashes; i++)
			_bits.at((hash1 + hash2 * i) % _bits.size()) = true;
	}

	bool	possiblyContains(const T& data) const {
		size_t	hash1 = Hash()(data) % 1000000;
		size_t	hash2 = Hash()(data) / 1000000;

		for (unsigned short i = 0; i < _nhashes; i++)
			if (!_bits.at((hash1 + hash2 * i) % _bits.size()))
				return false;
		return true;
	}
};
