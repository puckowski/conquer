
#ifndef STRINGS_H
#define STRINGS_H

int countSubstringExcludingQuotes(std::string str, const std::string& sub)
{
	std::string beforeQuote, afterQuote;
	int quoteIndex, secondQuoteIndex, temporaryQuoteIndex;

	const int subLength = sub.length();

	while (str.find("\"") != std::string::npos)
	{
		quoteIndex = str.find_first_of("\"");
		secondQuoteIndex = str.find("\"", quoteIndex + 1);

		if (secondQuoteIndex > 0)
		{
			temporaryQuoteIndex = secondQuoteIndex;

			while (str.at(temporaryQuoteIndex - 1) == '\\') {
				temporaryQuoteIndex = str.find_first_of("\"", temporaryQuoteIndex + 1);

				if (temporaryQuoteIndex < 1)
					break;

				secondQuoteIndex = temporaryQuoteIndex;
			}

			// Get a substring... from the start of str to the first quote, excluding the first quote itself
			beforeQuote = str.substr(0, quoteIndex);
			afterQuote = str.substr(secondQuoteIndex + 1, str.length());

			// Rebuild str
			str = beforeQuote + afterQuote;
		}
		else
		{
			beforeQuote = str.substr(0, quoteIndex);
			afterQuote = str.substr(quoteIndex + 1, str.length());

			str = beforeQuote + afterQuote;
		}
	}

	int count = 0;

	for (std::size_t pos = str.find(sub); pos != std::string::npos;
		pos = str.find(sub, pos + subLength))
	{
		++count;
	}

	return count;
}

int countSubstring(const std::string& str, const std::string& sub)
{
	const int substringLength = sub.length();

	int count = 0;

	for (std::size_t pos = str.find(sub); pos != std::string::npos;
		pos = str.find(sub, pos + substringLength))
	{
		++count;
	}

	return count;
}

inline bool stringEndsWith(std::string const &fullString, std::string const &ending) {
	const int fullStringLength = fullString.length(), endingLength = ending.length();

	if (fullStringLength >= endingLength)
		return (0 == fullString.compare(fullStringLength - endingLength, endingLength, ending));
	else
		return false;
}

inline bool stringStartsWith(const std::string &text, const std::string substring)
{
	return (text.compare(0, substring.length(), substring) == 0);
}

template <typename T, typename K>
bool startsWithString(const std::string &code, const std::map<T, K> &map)
{
	for (const auto &elem : map)
		if (stringStartsWith(code, elem.second))
			return true;

	return false;
}

inline void removeWhitespace(std::string &code)
{
	code.erase(std::remove(code.begin(), code.end(), ' '), code.end());
}

inline void removeAllFromString(std::string &code, const char toRemove)
{
	code.erase(std::remove(code.begin(), code.end(), toRemove), code.end());
}

void removeAllCharExcludingQuotes(std::string &code, const char toRemove)
{
	std::vector<std::string> codeStringVector;
	std::string beforeQuote, afterQuote, quoteString;
	int quoteIndex, temporaryQuoteIndex;

	while (code.find("\"") != std::string::npos)
	{
		quoteIndex = code.find_first_of("\"");
		
		beforeQuote = code.substr(0, quoteIndex);
		code = code.substr(quoteIndex);

		quoteIndex = code.find_first_of("\"", 1);
		temporaryQuoteIndex = quoteIndex;

		bool run = false;

		while (code.at(temporaryQuoteIndex - 1) == '\\') {
			run = true;

			temporaryQuoteIndex = code.find_first_of("\"", temporaryQuoteIndex + 1);
			
			if (temporaryQuoteIndex < 1)
				break;

			quoteString = code.substr(0, temporaryQuoteIndex + 1);
			quoteIndex = temporaryQuoteIndex;
		} 

		if (run == false)
			quoteString = code.substr(0, quoteIndex + 1);

		afterQuote = code.substr(quoteIndex + 1);

		removeAllFromString(beforeQuote, toRemove);

		codeStringVector.push_back(beforeQuote);
		codeStringVector.push_back(quoteString);

		code = afterQuote;
	}

	removeAllFromString(code, toRemove);
	codeStringVector.push_back(code);

	code = "";

	for (const auto &elem : codeStringVector)
		code.append(elem);
}

void replaceSubstring(std::string &s, const std::string &search, const std::string &replace) 
{
	const int searchLength = search.length();

	std::size_t pos = s.find(search);
		
	if (pos != std::string::npos) 
	{ 
		s.erase(pos, searchLength);
		s.insert(pos, replace);
	}
}

void replaceAllSubstrings(std::string &s, const std::string &search, const std::string &replace) 
{
	const int searchLength = search.length(), replaceLength = replace.length();

	for (std::size_t pos = 0;; pos += replaceLength) 
	{
		// Locate the substring to replace
		pos = s.find(search, pos);

		if (pos == std::string::npos) break;

		// Replace by erasing and inserting
		s.erase(pos, searchLength);
		s.insert(pos, replace);
	}
}

void replaceAllSubstrings(std::string &s, const std::string &search, const char replace) 
{
	const int searchLength = search.length();
	const std::string replaceString = std::to_string(replace);

	for (std::size_t pos = 0;; pos += 1) 
	{
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == std::string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, searchLength);
		s.insert(pos, replaceString);
	}
}

template <typename T, typename K>
std::string removeStringFromMap(std::string &text, const std::map<T, K> &map, std::string &str)
{
	for (const auto &elem : map)
	{
		if (stringStartsWith(text, elem.second))
		{
			replaceSubstring(text, elem.second, "");
			// Set pass by reference return value... send back the removed string
			str = elem.second;

			// Remove only one string
			break;
		}
	}

	return text;
}

template <typename T, typename K>
std::string removeStringFromMap(std::string &text, const std::map<T, K> &map, std::string &str, const int &maxStringLength)
{
	for (const auto &elem : map)
	{
		if (stringStartsWith(text, elem.second))
		{
			// Set pass by reference return value... send back the removed string
			str = elem.second;

			if (str.length() == maxStringLength)
				break;
		}
	}

	replaceSubstring(text, str, "");

	return text;
}

#endif