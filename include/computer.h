#ifndef COMPUTER_H
#define COMPUTER_H

#include <computer.h>
#include <memory.h>

class Computer {
	public:
	Computer(Memory *memory): memory(memory), pc(0) {}
	void run();
	bool step();

	private:
	Memory *memory;
	uint32_t registers[32];
	uint32_t pc;
}

#endif
