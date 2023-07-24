
#ifndef DATATYPE_H
#define DATATYPE_H

#include <map>
#include <string>

enum Datatype
{
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING,
	TYPE_BOOL,
	TYPE_FILENAME,
	TYPE_FUNCTION,
	TYPE_UNKNOWN
};

const std::map<Datatype, std::string> DATATYPE_MAP =
{
	{ TYPE_INT,      "int"      },
	{ TYPE_DOUBLE,   "double"   },
	{ TYPE_STRING,   "string"   },
	{ TYPE_BOOL,     "bool"     },
	{ TYPE_FILENAME, "file"     },
	{ TYPE_FUNCTION, "function" }
};

const std::map<Datatype, int> DATATYPE_INT_MAP =
{
	{ TYPE_INT,      0 },
	{ TYPE_DOUBLE,   1 },
	{ TYPE_STRING,   2 },
	{ TYPE_BOOL,     3 },
	{ TYPE_FILENAME, 4 },
	{ TYPE_FUNCTION, 5 }
};

const std::map<std::string, Datatype> DATATYPE_STRING_MAP =
{
	{ "int",      TYPE_INT      },
	{ "double",   TYPE_DOUBLE   },
	{ "string",   TYPE_STRING   },
	{ "bool",     TYPE_BOOL     },
	{ "file",     TYPE_FILENAME },
	{ "function", TYPE_FUNCTION }
};

#endif