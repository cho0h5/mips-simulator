#ifndef COMPUTER_H
#define COMPUTER_H

#include <computer.h>
#include <memory.h>
#include <registers.h>

class Computer {
	public:
	Computer(Memory *memory): memory(memory), pc(0) {}
	void run();
	bool step();

	private:
	Memory *memory;
	Registers registers;
	uint32_t pc;

	bool step_syscall(Instruction instruction);
	void step_addi(Instruction instruction);
};

#endif
