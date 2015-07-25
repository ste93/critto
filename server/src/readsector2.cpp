#include <fstream>
#include <cerrno>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <iostream>

int readsector(char *diskName, uint32_t sector) {
	// Which disk?
	std::string diskError = std::string() + diskName + ": ";

	// Open device file
	std::ifstream disk(diskName, std::ios_base::binary);

	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));

	// Seek to 54321'th sector
	disk.seekg(512 * sector);
	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));

	// Read in one sector
	std::vector<char> buffer(512);
	disk.read(&buffer[0], 512);
	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));
}


int writesector(char *diskName, uint32_t sector) {
	// Which disk?
	std::string diskError = std::string() + diskName + ": ";

	// Open device file
	std::ifstream disk(diskName, std::ios_base::binary);

	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));

	// Seek to 54321'th sector
	disk.seekg(512 * sector);
	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));

	// Read in one sector
	std::vector<char> buffer(512);
	disk.write(&buffer[0], 512);
	if(!disk)
		throw(std::runtime_error(diskError + std::strerror(errno)));
}

int main() {
	readsector
}
