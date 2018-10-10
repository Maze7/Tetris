#include "Encryption.h"

namespace Utility {

/*
	XOR-Encryption
*/
std::string Encryption::XORencryption(const std::string& toEncrypt) {

	char key[4] = { 'A', 'B', 'C', 'D' };
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}

} /* namespace Utility */
