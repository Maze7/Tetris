#include "FileIO.h"

/*
	Returns a string-vector containing the content of the given file.
*/
std::vector<std::string> FileIO::readFile(const std::string& filename)
{
	std::vector<std::string> v_input;
	std::string line;
	std::string input;

	std::ifstream fileIn(filename);

	if (fileIn.is_open())
	{
		// Add each line of the file to the input-string
		while (std::getline(fileIn, line))
		{
			input += line + "\n";
		}

		// Decrypt the string
		input = Utility::Encryption::XORencryption(input);

		// Use string to fill vector of substrings (string, targeted vector, delimiter)
		Utility::Converter::StringToVector(input, v_input, "\n"); 

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
void FileIO::writeFile(const std::string& output, const std::string& filename)
{
	std::ofstream fileOut;
	fileOut.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	try {
		fileOut.open(filename);
		fileOut << Utility::Encryption::XORencryption(output);

		std::cout << "Writing\n" << output << std::endl;
		fileOut.close();
	}
	catch (std::ofstream::failure const &e) {
		throw Exceptions::FileExceptions::FileWriteException("FileWriteException");
	}

}
