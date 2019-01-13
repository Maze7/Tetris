#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utility/Converter.h"
#include "../Utility/Encryption.h"
#include "../Exceptions/FileExceptions.h"

class FileIO {
public:
	FileIO() {}
	~FileIO() {}

	static std::vector<std::string> readFile(const std::string& filename);
	static void writeFile(const std::string& output, const std::string& filename);
};

