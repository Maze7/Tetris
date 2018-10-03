#pragma once
#include <string>
#include <vector>

namespace Utility
{
	class Converter
	{
	public:
		static std::vector<std::string> StringToVector(const std::string& str, const std::string& delimiter);
	};
}

