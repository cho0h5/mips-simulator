#include <iostream>
#include <cstdint>

#include <memory.h>
#include <computer.h>

using namespace std;

int main(int argc, char **argv) {
	Memory *memory = new Memory;

	if (argc != 2) {
		cout << "[error] you must input 1 file name\n";
		return 0;
	}

	if (memory->load_program(argv[1])) {
		cout << "[error] failed to load program\n";
	}
	cout << "[info] program loaded\n";

	Computer computer(memory);
	computer.step();
	computer.step();
	computer.step();

	return 0;
}
