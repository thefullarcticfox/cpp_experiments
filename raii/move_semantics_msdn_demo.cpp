#include <iostream>
#include <vector>
#include <algorithm>

class MemoryBlock {
public:
	//	Simple constructor that initializes the resource
	explicit MemoryBlock(size_t length) : _length(length), _data(new int[length])
	{
		std::cout << "In MemoryBlock(size_t). length = "
				<< _length << "." << std::endl;
	}

	//	Destructor
	~MemoryBlock()
	{
		std::cout << "In ~MemoryBlock(). length = " << _length << ".";

		if (_data != nullptr) {
			std::cout << " Deleting resource.";
			delete[] _data;		//	Delete the resource
		}

		std::cout << std::endl;
	}

	//	Copy constructor
	MemoryBlock(const MemoryBlock& other) : _length(other._length), _data(new int[other._length])
	{
		std::cout << "In MemoryBlock(const MemoryBlock&). length = "
				<< other._length << ". Copying resource." << std::endl;

		std::copy(other._data, other._data + _length, _data);
	}

	//	Copy assignment operator
	MemoryBlock& operator=(const MemoryBlock& other)
	{
		std::cout << "In operator=(const MemoryBlock&). length = "
					<< other._length << ". Copying resource." << std::endl;

		if (this != &other) {
			delete[] _data;		//	Free the existing resource

			_length = other._length;
			_data = new int[_length];

			std::copy(other._data, other._data + _length, _data);
		}
		return *this;
	}

	//	Move constructor
	MemoryBlock(MemoryBlock&& other) noexcept : _length(0), _data(nullptr)
	{
		std::cout << "In MemoryBlock(MemoryBlock&&). length = "
				<< other._length << ". Moving resource." << std::endl;

		//	Copy the data pointer and its length from the source object
		_data = other._data;
		_length = other._length;

		//	Release the data pointer from the source object so that
		//	the destructor does not free the memory multiple times.
		other._data = nullptr;
		other._length = 0;

		//	DRY solution: *this = std::move(other);
	}

	//	Move assignment operator
	MemoryBlock& operator=(MemoryBlock&& other) noexcept
	{
		std::cout << "In operator=(MemoryBlock&&). length = "
					<< other._length << "." << std::endl;

		if (this != &other) {
			delete[] _data;		// Free the existing resource

			//	Copy the data pointer and its length from the source object
			_data = other._data;
			_length = other._length;

			//	Release the data pointer from the source object so that
			//	the destructor does not free the memory multiple times.
			other._data = nullptr;
			other._length = 0;
		}
		return *this;
	}

	//	Retrieves the length of the data resource.
	size_t	Length() const	{	return _length;	}

private:
	size_t	_length;	//	The length of the resource
	int*	_data;		//	The resource
};

int		main() {
	//	Create a vector object and add a few elements to it
	std::vector<MemoryBlock> v;

	std::cout << ">>>>>> v.push_back(MemoryBlock(25));" << std::endl;
	v.push_back(MemoryBlock(25));
	std::cout << "\n>>>>>> v.push_back(MemoryBlock(75));" << std::endl;
	v.push_back(MemoryBlock(75));

	std::cout << "\n>>>>>> v.insert(v.begin() + 1, MemoryBlock(50));" << std::endl;
	//	Insert a new element into the second position of the vector
	v.insert(v.begin() + 1, MemoryBlock(50));

	std::cout << "\n>>>>>> Destructors are called" << std::endl;
}

/*	without move semantics
>>>>>> v.push_back(MemoryBlock(25));
In MemoryBlock(size_t). length = 25.
In MemoryBlock(const MemoryBlock&). length = 25. Copying resource.
In ~MemoryBlock(). length = 25. Deleting resource.

>>>>>> v.push_back(MemoryBlock(75));
In MemoryBlock(size_t). length = 75.
In MemoryBlock(const MemoryBlock&). length = 75. Copying resource.
In MemoryBlock(const MemoryBlock&). length = 25. Copying resource.
In ~MemoryBlock(). length = 25. Deleting resource.
In ~MemoryBlock(). length = 75. Deleting resource.

>>>>>> v.insert(v.begin() + 1, MemoryBlock(50));
In MemoryBlock(size_t). length = 50.
In MemoryBlock(const MemoryBlock&). length = 50. Copying resource.
In MemoryBlock(const MemoryBlock&). length = 25. Copying resource.
In MemoryBlock(const MemoryBlock&). length = 75. Copying resource.
In ~MemoryBlock(). length = 25. Deleting resource.
In ~MemoryBlock(). length = 75. Deleting resource.
In ~MemoryBlock(). length = 50. Deleting resource.

>>>>>> Destructors are called
In ~MemoryBlock(). length = 25. Deleting resource.
In ~MemoryBlock(). length = 50. Deleting resource.
In ~MemoryBlock(). length = 75. Deleting resource.
*/

/*	with move semantics
>>>>>> v.push_back(MemoryBlock(25));
In MemoryBlock(size_t). length = 25.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.

>>>>>> v.push_back(MemoryBlock(75));
In MemoryBlock(size_t). length = 75.
In MemoryBlock(MemoryBlock&&). length = 75. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.

>>>>>> v.insert(v.begin() + 1, MemoryBlock(50));
In MemoryBlock(size_t). length = 50.
In MemoryBlock(MemoryBlock&&). length = 50. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
In MemoryBlock(MemoryBlock&&). length = 75. Moving resource.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.

>>>>>> Destructors are called
In ~MemoryBlock(). length = 25. Deleting resource.
In ~MemoryBlock(). length = 50. Deleting resource.
In ~MemoryBlock(). length = 75. Deleting resource.
*/

//	vector uses move semantics to perform insertion efficiantly by moving element instead of copying
//	copy does std::copy when move just copies the pointer
