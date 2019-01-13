#include "FileIO.h"

/*
	Returns a string-vector containing the content of the given file.
*/
std::vector<std::string> FileIO::readFile(const std::string& filename) {
	std::string line;
	std::string input;

	std::ifstream fileIn(filename);

	if (fileIn.is_open()) {
		// Add each line of the file to the input-string
		while (std::getline(fileIn, line)) {
			input += line + "\n";
		}

		fileIn.close();

		// Decrypt the string
		input = Utility::Encryption::XORencryption(input);
	} else {
		throw Exceptions::FileExceptions::FileNotFoundException("FileNotFoundException");
	}

	// Return vector of the substrings (string, delimiter)
	return Utility::Converter::StringToVector(input, "\n");
}

/*
	Writes the given string to the given file
*/
void FileIO::writeFile(const std::string& output, const std::string& filename) {
	std::ofstream fileOut;
	fileOut.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	try {
		fileOut.open(filename);
		fileOut << Utility::Encryption::XORencryption(output);

		std::cout << "Writing\n" << output << std::endl;
		fileOut.close();
	} catch (std::ofstream::failure const &e) {
		throw Exceptions::FileExceptions::FileWriteException("FileWriteException");
	}
}
