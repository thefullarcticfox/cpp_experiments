#include <iostream>
#include <string>
#include <exception>
#include <sys/types.h>
#include <algorithm>
#include <vector>
#include <dirent.h>

struct stats {
	size_t	dirs;
	size_t	files;
	stats() : dirs(0), files(0) {}
	~stats() {}
};

void	recursedirread(const std::string& path, const std::string& offset, stats& s) {
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
			if (name != "." && name != "..")
				dirnames.push_back(name);
		} else
			filenames.push_back(name);
	}
	closedir(dir);

	//	sorting
	std::sort(dirnames.begin(), dirnames.end());
	std::sort(filenames.begin(), filenames.end());

	std::string	tmppath(path);
	if (tmppath.rbegin() != tmppath.rend() && *(tmppath.rbegin()) == '/')
		tmppath.resize(tmppath.size() - 1);

	//	recurse in dirs
	for (size_t i = 0; dirnames.size() > 0 && i < dirnames.size() - 1; i++) {
		std::cout << offset << "├── " << dirnames[i] << std::endl;
		recursedirread(tmppath + "/" + dirnames[i], offset + "│   ", s);
	}
	if (dirnames.size() > 0) {
		if (filenames.size() > 0) {
			std::cout << offset << "├── " << dirnames[dirnames.size() - 1] << std::endl;
			recursedirread(tmppath + "/" + dirnames[dirnames.size() - 1], offset + "│   ", s);
		} else {
			std::cout << offset << "└── " << dirnames[dirnames.size() - 1] << std::endl;
			recursedirread(tmppath + "/" + dirnames[dirnames.size() - 1], offset + "    ", s);
		}
	}

	//	print files
	for (size_t i = 0; filenames.size() > 0 && i < filenames.size() - 1; i++) {
		std::cout << offset << "├── " << filenames[i] << std::endl;
	}
	if (filenames.size() > 0)
		std::cout << offset << "└── " << filenames[filenames.size() - 1] << std::endl;

	s.dirs += dirnames.size();
	s.files += filenames.size();
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
		recursedirread(path, "", s);
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl << s.dirs << " directories, " << s.files << " files" << std::endl;
	return (0);
}
