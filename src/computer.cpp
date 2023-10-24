#include <computer.h>

void Computer::run() {
	while(!step()) {}
}

bool step() {
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
}

void Computer::step_addi(Instruction instruction) {
}
