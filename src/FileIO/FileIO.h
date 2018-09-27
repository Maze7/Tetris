#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Exceptions/FileExceptions.h"

class FileIO
{
public:
	FileIO() {}
	~FileIO() {}

	static std::vector<std::string> readFile(std::string filename);
	static void writeFile(std::string output, std::string filename);
};

