#include <memory.h>

#include <fstream>

using namespace std;

bool Memory::load_program(string filename) {
	std::ifstream file(filename, ios::binary | ios::ate);

	if (file) {
		int size = file.tellg();
		file.seekg(0, ios::beg);

		file.read((char*)memory, size);

		file.close();
		return 0;
	}
	return 1;
}
