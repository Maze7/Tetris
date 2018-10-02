#pragma once
#include <string>
#include <vector>

namespace Utility
{
	class Converter
	{
	public:
		static void StringToVector(const std::string& str, std::vector<std::string>& list, const std::string& delimiter);
	};
}

