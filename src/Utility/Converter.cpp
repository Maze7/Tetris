#include "Converter.h"

/*
	Returns a vector filled by the substrings of the given string divided with the given delimiter.
*/
std::vector<std::string> Utility::Converter::StringToVector(const std::string& str, const std::string& delimiter)
{
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	std::vector<std::string> result;

	// Iterate over the string, build substrings and push them to the result vector
	while ((pos = str.find(delimiter, prev)) != std::string::npos) {
		result.push_back(str.substr(prev, pos - prev));
		prev = pos + delimiter.size();
	}

	return result;
}
