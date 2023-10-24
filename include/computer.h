#ifndef COMPUTER_H
#define COMPUTER_H

#include <computer.h>
#include <memory.h>
#include <registers.h>

class Computer {
	public:
	Computer(Memory *memory): memory(memory) {}
	void run();
	bool step();

	private:
	Memory *memory;
	Registers registers;

	bool step_syscall();
	void step_addi(Instruction instruction);
};

#endif
