
#ifndef MAIN_CPP
#define MAIN_CPP

#include <vector>

#include "vlasm.h"
#include "../etc/utils.h"

using namespace violet;

int main(int argc, char *argv[])
{
	const std::vector<std::string> source = utils::load_source_file(argv[1]);
	
	auto t1 = utils::getTime();
	const std::vector<uint32_t> program = vlasm::parse_source(source);
	auto t2 = utils::getTime();
	utils::printTimeDifferenceAll(t1, t2);
	
	return utils::write_program_file(argv[2], program);
}

#endif // MAIN_CPP