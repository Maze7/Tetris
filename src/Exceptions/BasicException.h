#pragma once
#include <string>
class BasicException
{

protected: 
	std::string m_description;

public:
	BasicException() : m_description("Exception") {}
	~BasicException();

	const std::string getErrorMessage() { return m_description; }
	void setErrorMessage(std::string description) { m_description = description; }
};

