#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class Memory {
	public:
	void load_program(std::string filename);

	private:
	uint8_t memory[0xFFFFFFFF];
};

#endif
