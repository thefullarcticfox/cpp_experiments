#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include <climits>

struct s_stats {
	const bool	nodot;
	size_t		dirs;
	size_t		files;
	s_stats(bool nodot = true) : nodot(nodot), dirs(0), files(0) {}
	~s_stats() {}
};

void	recursedirread(const std::string& path, const std::string& offset, s_stats& s) {
	DIR*		dir = opendir(path.c_str());
	if (!dir)
		throw std::runtime_error(path + " [error opening dir]");

	dirent*		entry = NULL;
	std::vector<std::string>	dirnames;
	std::vector<std::string>	filenames;
	dirnames.reserve(200);
	filenames.reserve(200);
	while ((entry = readdir(dir))) {
		std::string	name = entry->d_name;
		if (entry->d_type == DT_DIR) {
			if (name != "." && name != ".." && !(s.nodot && name[0] == '.'))
				dirnames.push_back(name);
		} else if (!(s.nodot && name[0] == '.'))
			filenames.push_back(name);
	}
	closedir(dir);

	//	sorting
	std::sort(dirnames.begin(), dirnames.end());
	std::sort(filenames.begin(), filenames.end());

	//	recurse in dirs
	for (size_t i = 0; dirnames.size() > 0 && i < dirnames.size() - 1; i++) {
		std::cout << offset << "├── " << dirnames[i] << std::endl;
		recursedirread(path + "/" + dirnames[i], offset + "│   ", s);
	}
	if (dirnames.size() > 0) {
		if (filenames.size() > 0) {
			std::cout << offset << "├── " << dirnames[dirnames.size() - 1] << std::endl;
			recursedirread(path + "/" + dirnames[dirnames.size() - 1], offset + "│   ", s);
		} else {
			std::cout << offset << "└── " << dirnames[dirnames.size() - 1] << std::endl;
			recursedirread(path + "/" + dirnames[dirnames.size() - 1], offset + "    ", s);
		}
	}

	//	print files
	for (size_t i = 0; filenames.size() > 0 && i < filenames.size() - 1; i++)
		std::cout << offset << "├── " << filenames[i] << std::endl;
	if (filenames.size() > 0)
		std::cout << offset << "└── " << filenames[filenames.size() - 1] << std::endl;

	//	stats update
	s.dirs += dirnames.size();
	s.files += filenames.size();
}

int		main(int ac, char** av) {
	std::string	path;
	bool		nodot = true;

	for (int i = 1; i < ac; i++) {
		std::string	arg(av[i]);
		if (arg == "-a")
			nodot = false;
		else if (arg == "-h" || arg == "--help") {
			std::cout << "usage: " << av[0] << " [-a] [-h|--help] [directory]" << std::endl <<
				"  -a\t\tAll files are listed." << std::endl <<
				"  -h|--help\tPrint usage and this help message and exit." << std::endl;
			return (0);
		}
		else if (path.empty())
			path = arg;
	}

	if (path.empty())
		path = ".";
	s_stats		s(nodot);

	try {
		struct	stat	c_stat;
		if (stat(path.c_str(), &c_stat) != 0 || !S_ISDIR(c_stat.st_mode))
			throw std::runtime_error(path + " [error opening dir]");

		char	resolved[4096];
		if (realpath(path.c_str(), resolved))
			path = resolved;

		size_t	lastnonslash = path.find_last_not_of('/');
		if (lastnonslash != std::string::npos && lastnonslash + 1 != path.size())
			path.resize(lastnonslash + 1);
		std::cout << path << std::endl;
		recursedirread(path, "", s);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl << s.dirs << " directories, " << s.files << " files" << std::endl;
	return (0);
}
