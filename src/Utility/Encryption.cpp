#include "Encryption.h"

/*
	XOR-Encryption
*/
std::string Utility::Encryption::XORencryption(const std::string& toEncrypt)
{

	char key[4] = { 'A', 'B', 'C', 'D' };
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}
