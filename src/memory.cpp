#include <memory.h>

#include <fstream>

using namespace std;

void Memory::load_program(string filename) {
	std::ifstream file(filename, ios::binary | ios::ate);

	int size = file.tellg();
	file.seekg(0, ios::beg);

	file.read((char*)memory, size);

	file.close();
}
