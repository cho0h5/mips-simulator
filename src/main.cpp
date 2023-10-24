#include <iostream>
#include <cstdint>

using namespace std;

class Memory {
	uint8_t memory[0xFFFFFFFF];
};

int main() {
	Memory memory;
	cout << "asdf\n";

	return 0;
}
