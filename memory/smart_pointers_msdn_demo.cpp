#include <string>
#include <memory>

class Song {
public:
	std::wstring	artist;
	std::wstring	title;
	Song(const std::wstring& artist, const std::wstring& title) : artist(artist), title(title) {}
};

void	UseRawPointer() {
	//	Using a raw pointer -- not recommended.
	Song*	pSong = new Song(L"Bruno Mars", L"Nothing on You");

	//	Don't forget to delete!
	delete pSong;
}

void	UseSmartPointer() {
	//	Declare a smart pointer on stack and pass it the raw pointer
	std::unique_ptr<Song>	song2(new Song(L"Bruno Mars", L"Nothing on You"));
	std::unique_ptr<Song>	song2make = std::make_unique<Song>(L"Bruno Mars", L"Nothing on You");

	std::wstring	s = song2->title;
	std::wstring	sm = song2make->title;
}	//	song2 is deleted automatically here

class LargeObject {
public:
	void	DoSomething() {}
};

void	ProcessLargeObject(const LargeObject& lo) { (void)lo; }
void	SmartPointerDemo1() {
	//	Create the object and pass it to a smart pointer
	std::unique_ptr<LargeObject> pLarge(new LargeObject());

	//	Call a method on the object
	pLarge->DoSomething();

	//	Pass a reference to a method
	ProcessLargeObject(*pLarge);

}	//	pLarge is deleted automatically when function block goes out of scope

void	SmartPointerDemo2() {
	//	Create the object and pass it to a smart pointer
	std::unique_ptr<LargeObject> pLarge(new LargeObject());

	//	Call a method on the object
	pLarge->DoSomething();

	//	Free the memory before we exit function block
	pLarge.reset();
}

void	LegacyLargeObjectFunction(const LargeObject* lo) { (void)lo; }
void	SmartPointerDemo3() {
	//	Create the object and pass it to a smart pointer
	std::unique_ptr<LargeObject> pLarge(new LargeObject());

	//	Call a method on the object
	pLarge->DoSomething();

	//	Pass raw pointer to a legacy API
	LegacyLargeObjectFunction(pLarge.get());
}

int		main() {
	UseRawPointer();
	UseSmartPointer();

	SmartPointerDemo1();
	SmartPointerDemo2();
	SmartPointerDemo3();
}
