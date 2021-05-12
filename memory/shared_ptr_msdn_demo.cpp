#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct MediaAsset {
	virtual ~MediaAsset() = default;	//	make it polymorphic
};

struct Song : public MediaAsset {
	std::wstring	artist;
	std::wstring	title;
	Song(const std::wstring& artist_, const std::wstring& title_) :
		artist{ artist_ }, title{ title_ } {}
};

struct Photo : public MediaAsset {
	std::wstring	date;
	std::wstring	location;
	std::wstring	subject;
	Photo(const std::wstring& date, const std::wstring& location, const std::wstring& subject) :
		date(date), location(location), subject(subject) {}
};

int		main() {
	//	Example 1
	//	Use make_shared function when possible
	auto	sp1 = std::make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

	//	Ok, but slightly less efficient.
	//	Note: Using new expression as constructor argument creates no named variable for other code to access
	std::shared_ptr<Song>	sp2(new Song(L"Lady Gaga", L"Just Dance"));

	//	When initialization must be separate from declaration, e.g. class members,
	//	initialize with nullptr to make your programming intent explicit.
	std::shared_ptr<Song>	sp5(nullptr);	//	Equivalent to: std::shared_ptr<Song> sp5;

	sp5 = std::make_shared<Song>(L"Elton John", L"I'm Still Standing");


	//	Example 2
	auto	sp3(sp2);	//	Initialize with copy constructor. Increments ref count
	auto	sp4 = sp2;	//	Initialize via assignment. Increments ref count
	sp1.swap(sp2);		//	Initialize with another shared_ptr. sp1 and sp2 swap pointers as well as ref counts
	std::shared_ptr<Song>	sp7(nullptr);	//	Initialize with nullptr. sp7 is empty


	//	Example 3
	std::vector<std::shared_ptr<Song>>	v{
		std::make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
		std::make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
		std::make_shared<Song>(L"Thalia", L"Entre El Mar y Una Estrella")
	};

	std::vector<std::shared_ptr<Song>>	v2;
	remove_copy_if(v.begin(), v.end(), back_inserter(v2),
		[] (std::shared_ptr<Song> s) {	return s->artist.compare(L"Bob Dylan") == 0; });

	for (const auto& s : v2)
		std::wcout << s->artist << L":" << s->title << std::endl;


	//	Example 4
	std::vector<std::shared_ptr<MediaAsset>>	assets {
		std::make_shared<Song>(L"Himesh Reshammiya", L"Tera Surroor"),
		std::make_shared<Song>(L"Penaz Masani", L"Tu Dil De De"),
		std::make_shared<Photo>(L"2011-04-06", L"Redmond, WA", L"Soccer field at Microsoft.")
	};

	std::vector<std::shared_ptr<MediaAsset>>	photos;

	copy_if(assets.begin(), assets.end(), back_inserter(photos),
		[] (std::shared_ptr<MediaAsset> p) -> bool {
			//	Use dynamic_pointer_cast to test whether element is a std::shared_ptr<Photo>.
			std::shared_ptr<Photo>	temp = std::dynamic_pointer_cast<Photo>(p);
			return temp.get() != nullptr;
		});

	//	We know that the photos vector contains only
	//	shared_ptr<Photo> objects, so use static_cast.
	for (const auto&  p : photos)
		std::wcout << "Photo location: " << (std::static_pointer_cast<Photo>(p))->location << std::endl;


	//	Example 5
	//	Initialize two separate raw pointers.
	//	Note that they contain the same values.
	auto	song1 = new Song(L"Village People", L"YMCA");
	auto	song2 = new Song(L"Village People", L"YMCA");

	//	Create two unrelated shared_ptrs.
	std::shared_ptr<Song>	p1(song1);
	std::shared_ptr<Song>	p2(song2);

	//	Unrelated shared_ptrs are never equal.
	std::wcout << "p1 < p2 = " << std::boolalpha << (p1 < p2) << std::endl;
	std::wcout << "p1 == p2 = " << std::boolalpha <<(p1 == p2) << std::endl;

	//	Related shared_ptr instances are always equal.
	std::shared_ptr<Song>	p3(p2);
	std::wcout << "p3 == p2 = " << std::boolalpha << (p3 == p2) << std::endl;

	std::wcout << "Use counts p1, p2, p3, sp1, sp2, sp3, sp4, sp5, sp7:" << std::endl;
	std::wcout << p1.use_count() << " " << p2.use_count() << " " << p3.use_count() << " " <<
					sp1.use_count() << " " << sp2.use_count() << " " << sp3.use_count() << " " <<
					sp4.use_count() << " " << sp5.use_count() << " " << sp7.use_count() << std::endl;
}
