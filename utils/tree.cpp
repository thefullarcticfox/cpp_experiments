#include <iostream>
#include <string>
#include <exception>
#include <sys/types.h>
#include <sys/stat.h>
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
		throw std::runtime_error(path + " [error opening dir]");

	dirent*	entry = readdir(dir);
	while (entry) {
		fname = entry->d_name;
		if (entry->d_type == DT_DIR) {
			std::string	nextdir(entry->d_name);
			if (nextdir == "." || nextdir == "..") {
				entry = readdir(dir);
				if (!entry) {
					closedir(dir);
					return;
				}
				continue;
			}
			nextdir = path + "/" + nextdir;
			entry = readdir(dir);
			std::string tmp = "│   " + offset;
			if (entry)
				std::cout << offset << " " << fname << std::endl;
			else {
			//	tmp = "    " + offset;
				std::cout << offset.substr(0, offset.rfind("├")) << "└── " << fname << std::endl;
			}
			recursedirread(nextdir, tmp, s);
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
	std::cout << offset.substr(0, offset.rfind("├")) << "└── " << fname << std::endl;
	++s.files;
	closedir(dir);
}

int		main(int ac, char** av) {
	std::string	path;
	if (ac > 1)
		path = av[1];
	if (path.empty())
		path = "./";
	stats		s;
	std::cout << path << std::endl;
	try {
		recursedirread(path, "├──", s);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl << s.dirs << " directories, " << s.files << " files" << std::endl;
	return (0);
}
