
#ifndef HEADER_H
#define HEADER_H

#include "..\variable\TypeChecker.h"

const std::string SOFTWARE_NAME           = "Conquer";
const std::string SOFTWARE_VERSION_STRING = "0.7.5.0";
const std::string SOFTWARE_VERSION_CODE   = "840";
const std::string SOFTWARE_AUTHOR         = "Daniel Puckowski";

TypeChecker gTypeChecker = TypeChecker();

inline void printSoftwareInformation()
{ 
	std::cout << SOFTWARE_NAME                            << std::endl;
	std::cout << "Version: "   << SOFTWARE_VERSION_STRING << std::endl;
	std::cout << "Author: "    << SOFTWARE_AUTHOR         << std::endl;
}

void run(std::string &code, bool readFromFile = false, bool decrementThreadCountWhenDone = false);
void runAsChild(std::string &code, std::thread::id parentId, bool readFromFile = false, bool decrementThreadCountWhenDone = false);

#endif