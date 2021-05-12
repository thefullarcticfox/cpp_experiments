#include <iostream>
#include <memory>

class widget {
private:
	std::unique_ptr<int>	_data;
public:
	explicit
	widget(const int size = 1) { _data = std::make_unique<int>(size); }

	//	rule of five is not needed here but i have it just to test
	//	the rule of five states tha
	//	setting copy ctor as = default cause compilation warning/error:
	//	explicitly defaulted copy constructor is implicitly deleted
	widget(const widget& other)	{	*this = other;				}	//	copy constructor
	widget(widget&& other)		{	*this = std::move(other);	}	//	move constructor

	widget&	operator=(const widget& other) {			//	copy assign
		if (this != &other)
			_data = std::make_unique<int>(*(other._data));
		return *this;
	}

	widget&	operator=(widget&& other) {					//	move assign
		if (this != &other)
			_data = std::move(other._data);
		return *this;
	}

	virtual	~widget() = default;						//	default destructor

	void	do_something() {
		std::cout << *_data << std::endl;
	}

	//	deleted operator new prevents widget from being dynamically allocated
	void*	operator new(std::size_t) = delete;
};

void	functionUsingWidget() {
	widget	w(1000000);				//	lifetime automatically tied to enclosing scope
									//	constructs w, including the w._data gadget member
	w.do_something();

	widget	wmoved(std::move(w));	//	converting to rvalue to test move ctor
	wmoved.do_something();

	w = wmoved;						//	copy assign because after move w has invalid ptr (it calls reset)
	w.do_something();
}	//	automatic destruction and deallocation for w and w.data

int		main() {
	functionUsingWidget();
}
