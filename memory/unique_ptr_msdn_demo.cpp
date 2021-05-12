#include <iostream>
#include <utility>
#include <string>
#include <memory>
#include <vector>

class Song {
public:
	std::wstring	artist;
	std::wstring	title;
	Song(const std::wstring& artist, const std::wstring& title) : artist(artist), title(title) {}
};

std::unique_ptr<Song>	SongFactory(const std::wstring& artist, const std::wstring& title) {
	//	Implicit move operation into the variable that stores the result
	return std::make_unique<Song>(artist, title);
}

void	MakeSongs()
{
	//	Create a new unique_ptr with a new object
	auto song = std::make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

	//	Use the unique_ptr
	std::vector<std::wstring> titles = { song->title };

	//	Move raw pointer from one unique_ptr to another
	std::unique_ptr<Song> song2 = std::move(song);

	//	Obtain unique_ptr from function that returns by value
	auto	song3 = SongFactory(L"Michael Jackson", L"Beat It");
}

void	SongVector()
{
    std::vector<std::unique_ptr<Song>> songs;

    //	Create a few new unique_ptr<Song> instances and add them to vector using implicit move semantics
    songs.push_back(std::make_unique<Song>(L"Namie Amuro", L"Funky Town"));
    songs.push_back(std::make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de"));
    songs.push_back(std::make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));
    songs.push_back(std::make_unique<Song>(L"Hako Yamazaki", L"Sasurai"));

    for (const auto& song : songs)
        std::wcout << L"Artist: " << song->artist << L"	Title: " << song->title << std::endl;
}

void	ArrayUniquePtr() {
	//	Create a unique_ptr to an array of 5 integers
	auto	p = std::make_unique<int[]>(5);

	//	Initialize the array
	for (int i = 0; i < 5; ++i) {
		p[i] = i;
		std::wcout << p[i] << " ";
	}
	std::wcout << std::endl;
}

int		main() {
	MakeSongs();
	SongVector();
	ArrayUniquePtr();
}
