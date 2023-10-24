#include <computer.h>

void Computer::run() {
	while(!step()) {}
}

bool Computer::step() {
	Instruction instruction = memory->fetch_instruction(pc);
	pc += 4;

	if (instruction.format == R_FORMAT) {
		if (instruction.funct == FT_SYSCALL) {
			return step_syscall(instruction);
		}
	} else {
		if (instruction.opcode == OP_ADDI) {
			step_addi(instruction);
		}
	}
	return 0;
}

bool Computer::step_syscall(Instruction instruction) {
	(void)instruction;
	(void)registers;
	return false;
}

void Computer::step_addi(Instruction instruction) {
	(void)instruction;
}
