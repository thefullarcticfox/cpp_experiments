#include <iostream>
#include <string>
#include <exception>
#include <sys/types.h>
#include <dirent.h>

struct stats {
	size_t	dirs;
	size_t	files;
	stats() : dirs(0), files(0) {}
	~stats() {}
};

void	recursedirread(const std::string& path, const std::string& offset, stats& s) {
	DIR*		dir = opendir(path.c_str());
	std::string	fname;
	if (!dir)
		throw std::runtime_error("diropen error");

	dirent*	entry = readdir(dir);
	while (entry) {
		fname = entry->d_name;
		if (entry->d_type == DT_DIR) {
			std::string	nextdir(entry->d_name);
			if (nextdir == "." || nextdir == "..") {
				entry = readdir(dir);
				continue;
			}
			nextdir = path + "/" + nextdir;
			entry = readdir(dir);
			if (entry)
				std::cout << offset << " " << fname << std::endl;
			else
				std::cout << offset.substr(0, offset.size() - 9) << "└── " << fname << std::endl;
			recursedirread(nextdir, "│   " + offset, s);
			++s.dirs;
			if (!entry) {
				closedir(dir);
				return;
			}
			continue;
		}
		entry = readdir(dir);
		if (!entry)
			break;
		std::cout << offset << " " << fname << std::endl;
		++s.files;
	}
	std::cout << offset.substr(0, offset.size() - 9) << "└── " << fname << std::endl;
	++s.files;
	closedir(dir);
}

int		main(int ac, char** av) {
	std::string	path;
	if (ac > 1)
		path = av[1];
	if (path.empty())
		path = "./";
	std::cout << path << std::endl;
	stats		s;
	recursedirread(path, "├──", s);
	std::cout << std::endl << s.dirs << " directories, " << s.files << " files" << std::endl;
	return (0);
}
