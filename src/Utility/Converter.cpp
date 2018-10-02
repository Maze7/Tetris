#include "Converter.h"

/*
	Takes a string, uses the given delimiter to create substrings and pushes the substrings to the given vector.
*/
void Utility::Converter::StringToVector(const std::string& str, std::vector<std::string>& list, const std::string& delimiter)
{
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = str.find(delimiter, prev)) != std::string::npos) {
		list.push_back(str.substr(prev, pos - prev));
		prev = pos + delimiter.size();
	}
}
