#pragma once
#include "BasicException.h"

class FileNotFoundException : public BasicException
{
public:
	FileNotFoundException() { setErrorMessage("File not found."); }
	~FileNotFoundException();
};

