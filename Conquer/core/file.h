
#ifndef FILE_H
#define FILE_H

#include <string>
#include <sstream>
#include <fstream>

inline std::string readFile(const std::string &filename)
{
	std::ifstream t(filename);

	std::stringstream buffer;
	buffer << t.rdbuf();
	
	return buffer.str();
}

#endif