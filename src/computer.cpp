#include <computer.h>

using namespace std;

void Computer::run() {
	while(!step()) {}
}

bool Computer::step() {
	Instruction instruction = memory->fetch_instruction(registers.get_pc());
	registers.increase_pc();

	memory->print_instruction(instruction);

	if (instruction.format == R_FORMAT) {
		if (instruction.funct == FT_SYSCALL) {
			return step_syscall();
		}
	} else {
		if (instruction.opcode == OP_ADDI) {
			step_addi(instruction);
		}
	}
	cout << "debug A0: " << registers.unsigned_get(A0) << '\n';
	cout << "debug V0: " << registers.unsigned_get(V0) << '\n';
	return 0;
}

bool Computer::step_syscall() {
	if (registers.unsigned_get(V0) == 1) {
		cout << registers.signed_get(A0);
	}
	return false;
}

void Computer::step_addi(Instruction instruction) {
	int32_t temp = 0;
	temp += registers.signed_get(instruction.rs);
	temp += instruction.immediate;
	registers.set(instruction.rt, temp);
}
