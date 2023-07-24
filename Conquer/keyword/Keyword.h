
#ifndef KEYWORD_H
#define KEYWORD_H

#include <map>
#include <string>

const int MAXIMUM_KEYWORD_LENGTH = 7;

enum Keyword
{
	KEYWORD_CALL,
	KEYWORD_IF,
	KEYWORD_WHILE,
	KEYWORD_IMPORT,
	KEYWORD_PRINT,
	KEYWORD_PRINTLN,
	KEYWORD_DETACH,
	KEYWORD_JOIN,
	KEYWORD_READLN,
	KEYWORD_DELETE,
	KEYWORD_SYSTEM,
	KEYWORD_LOCK,
	KEYWORD_UNLOCK,
	KEYWORD_PUSH,
	KEYWORD_POP
};

const std::map<Keyword, std::string> KEYWORD_MAP =
{
	{ KEYWORD_CALL,    "call"    },
	{ KEYWORD_IF,      "if"      },
	{ KEYWORD_WHILE,   "while"   },
	{ KEYWORD_IMPORT,  "import"  },
	{ KEYWORD_PRINT,   "print"   },
	{ KEYWORD_PRINTLN, "println" },
	{ KEYWORD_DETACH,  "detach"  },
	{ KEYWORD_JOIN,    "join"    },
	{ KEYWORD_READLN,  "readln"  },
	{ KEYWORD_DELETE,  "delete"  },
	{ KEYWORD_SYSTEM,  "system"  },
	{ KEYWORD_LOCK,    "lock"    },
	{ KEYWORD_UNLOCK,  "unlock"  },
	{ KEYWORD_PUSH,    "push"    },
	{ KEYWORD_POP,     "pop"     }
};

const std::map< std::string, Keyword> KEYWORD_STRING_MAP =
{
	{ "call",    KEYWORD_CALL    },
	{ "if",      KEYWORD_IF      },
	{ "while",   KEYWORD_WHILE   },
	{ "import",  KEYWORD_IMPORT  },
	{ "print",   KEYWORD_PRINT   },
	{ "println", KEYWORD_PRINTLN },
	{ "detach",  KEYWORD_DETACH  },
	{ "join",    KEYWORD_JOIN    },
	{ "readln",  KEYWORD_READLN  },
	{ "delete",  KEYWORD_DELETE  },
	{ "system",  KEYWORD_SYSTEM  },
	{ "lock",    KEYWORD_LOCK    },
	{ "unlock",  KEYWORD_UNLOCK  },
	{ "push",    KEYWORD_PUSH    },
	{ "pop",     KEYWORD_POP     }
};

#endif