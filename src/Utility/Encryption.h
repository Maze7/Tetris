#pragma once
#include <string>

namespace Utility
{
	class Encryption
	{
	public:
		static std::string XORencryption(const std::string& toEncrypt);
	};
}