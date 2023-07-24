
#ifndef RESERVED_H
#define RESERVED_H

#include <map>
#include <string>

enum Reserved
{
	RESERVED_OPEN_COMMENT,
	RESERVED_CLOSE_COMMENT,
	RESERVED_ENDL
};

const std::map<Reserved, std::string> RESERVED_MAP =
{
	{ RESERVED_OPEN_COMMENT,  "/*"   },
	{ RESERVED_CLOSE_COMMENT, "*/"   },
	{ RESERVED_ENDL,          "endl" }
};

#endif