#include <iostream>
#include <fstream>

using namespace std;

void generate_file(int n, unsigned int *instructions);

int main() {
	unsigned int instructions[100];
	instructions[0] = 0b00100000000001000000010011000010;
	instructions[1] = 0b00100000000001000000000000000001;
	instructions[2] = 0b00000000000000000000000000001100;

	printf("0x%08x\n", instructions[0]);
	printf("0x%08x\n", instructions[1]);
	printf("0x%08x\n", instructions[2]);

	generate_file(3, instructions);

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
