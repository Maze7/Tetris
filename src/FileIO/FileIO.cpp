#include "FileIO.h"

/*
	Returns a string-vector containing the content of the given file.
*/
std::vector<std::string> FileIO::readFile(std::string filename)
{
	std::vector<std::string> v_input;
	std::string line;

	std::ifstream fileIn(filename);

	if (fileIn.is_open())
	{
		// Add each line of the file to the vector
		while (std::getline(fileIn, line))
		{
			v_input.push_back(line);
		}

		fileIn.close();
	}
	else
	{
		throw Exceptions::FileExceptions::FileNotFoundException("FileNotFoundException");
	}

	return v_input;
}

/*
	Writes the given string to the given file
*/
void FileIO::writeFile(std::string output, std::string filename)
{
	std::ofstream fileOut;
	fileOut.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	try {
		fileOut.open(filename);
		fileOut << output;
		fileOut.close();
	}
	catch (std::ofstream::failure const &e) {
		throw Exceptions::FileExceptions::FileWriteException("FileWriteException");
	}

}
