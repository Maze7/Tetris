#pragma once
#include <stdexcept>
#include <string>

namespace Exceptions
{
	namespace FileExceptions
	{
		struct FileNotFoundException : public std::runtime_error 
		{
			FileNotFoundException(std::string const& message) : std::runtime_error(message + "was thrown.") {}

			// overwrite
			const char* what() const throw() {
				return "File could not be found or is inaccessible.";
			}
		};

		struct FileWriteException : public std::runtime_error
		{
			FileWriteException(std::string const& message) : std::runtime_error(message + "was thrown.") {}

			// overwrite
			const char* what() const throw() {
				return "Could not write to file.";
			}
		};
	}
}