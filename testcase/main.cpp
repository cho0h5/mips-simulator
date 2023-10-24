#include <iostream>
#include <fstream>

using namespace std;

void generate_file(int n, unsigned int *instructions);

int main() {
	int n = 20;
	unsigned int instructions[100] = {
		0b00100000000001000000010011010010,	// a0 = 1234
		0b00100000000000100000000000000001,	// v0 = 1
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000000001010,	// a0 = '\n'
		0b00100000000000100000000000001011,	// v0 = 11
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000001101000,	// a0 = 'h'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000001100101,	// a0 = 'e'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000001101100,	// a0 = 'l'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000001101100,	// a0 = 'l'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000001101111,	// a0 = 'o'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000001000000000000001010,	// a0 = '\n'
		0b00000000000000000000000000001100,	// syscall
											//
		0b00100000000000100000000000001010,	// v0 = 10
		0b00000000000000000000000000001100,	// syscall
	};

	for (int i = 0; i < n; i++)
		printf("0x%08x\n", instructions[i]);

	generate_file(n, instructions);

	return 0;
}

void generate_file(int n, unsigned int *instructions) {
	ofstream file("print_1218.bin", ios::binary);
	for (int i = 0; i < n; i++) {
		file.write(((char *)&instructions[i]) + 3, 1);
		file.write(((char *)&instructions[i]) + 2, 1);
		file.write(((char *)&instructions[i]) + 1, 1);
		file.write(((char *)&instructions[i]) + 0, 1);
	}
	file.close();
}
