#include <computer.h>

using namespace std;

void Computer::run() {
	while(!step()) {}
}

bool Computer::step() {
	Instruction instruction = memory->fetch_instruction(registers.get_pc());
	registers.increase_pc();

	if (instruction.format == R_FORMAT) {
		if (instruction.funct == FT_SYSCALL) {
			return step_syscall();
		}
	} else {
		if (instruction.opcode == OP_ADDI) {
			step_addi(instruction);
		}
	}
	return 0;
}

void Computer::step_add(Instruction instruction) {
	(void)instruction;
}

void Computer::step_addi(Instruction instruction) {
	int32_t temp = 0;
	temp += registers.signed_get(instruction.rs);
	temp += (int16_t)instruction.immediate;
	registers.set(instruction.rt, temp);
}

void Computer::step_addiu(Instruction instruction) {
}

void Computer::step_addu(Instruction instruction) {
	(void)instruction;
}

void Computer::step_and(Instruction instruction) {
	(void)instruction;
}

void Computer::step_andi(Instruction instruction) {
}

void Computer::step_beq(Instruction instruction) {
}

void Computer::step_bne(Instruction instruction) {
}

void Computer::step_j(Instruction instruction) {
}

void Computer::step_jal(Instruction instruction) {
}

void Computer::step_jr(Instruction instruction) {
	(void)instruction;
}

void Computer::step_lbu(Instruction instruction) {
}

void Computer::step_lhu(Instruction instruction) {
}

void Computer::step_ll(Instruction instruction) {
}

void Computer::step_lui(Instruction instruction) {
}

void Computer::step_lw(Instruction instruction) {
}

void Computer::step_nor(Instruction instruction) {
	(void)instruction;
}

void Computer::step_or(Instruction instruction) {
	(void)instruction;
}

void Computer::step_ori(Instruction instruction) {
}

void Computer::step_slt(Instruction instruction) {
	(void)instruction;
}

void Computer::step_slti(Instruction instruction) {
}

void Computer::step_sltiu(Instruction instruction) {
}

void Computer::step_sltu(Instruction instruction) {
	(void)instruction;
}

void Computer::step_sll(Instruction instruction) {
	(void)instruction;
}

void Computer::step_srl(Instruction instruction) {
	(void)instruction;
}

void Computer::step_sb(Instruction instruction) {
}

void Computer::step_sh(Instruction instruction) {
}

void Computer::step_sw(Instruction instruction) {
}

void Computer::step_sub(Instruction instruction) {
	(void)instruction;
}

void Computer::step_subu(Instruction instruction) {
	(void)instruction;
}

void Computer::step_div(Instruction instruction) {
	(void)instruction;
}

void Computer::step_divu(Instruction instruction) {
	(void)instruction;
}

void Computer::step_mfhi(Instruction instruction) {
	(void)instruction;
}

void Computer::step_mflo(Instruction instruction) {
	(void)instruction;
}

void Computer::step_mult(Instruction instruction) {
	(void)instruction;
}

void Computer::step_multu(Instruction instruction) {
	(void)instruction;
}

void Computer::step_sra(Instruction instruction) {
	(void)instruction;
}

bool Computer::step_syscall() {
	switch (registers.unsigned_get(V0)) {
		case 1:		// print integer
			cout << registers.signed_get(A0);
			break;
		case 10:	// exit
			return true;
		case 11:	// print character
			cout << (char)registers.signed_get(A0);
			break;
	}
	return false;
}

