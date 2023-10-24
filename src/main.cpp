#include <iostream>
#include <cstdint>

#include <memory.h>

using namespace std;

int main(int argc, char **argv) {
	Memory *memory = new Memory;

	if (argc != 2) {
		cout << "You must input 1 file name\n";
		return 0;
	}
	memory->load_program(argv[1]);

	return 0;
}
