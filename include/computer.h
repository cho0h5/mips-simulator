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

	void step_add(Instruction instruction);
	void step_addi(Instruction instruction);
	void step_addiu(Instruction instruction);
	void step_addu(Instruction instruction);
	void step_and(Instruction instruction);
	void step_andi(Instruction instruction);
	void step_beq(Instruction instruction);
	void step_bne(Instruction instruction);
	void step_j(Instruction instruction);
	void step_jal(Instruction instruction);
	void step_jr(Instruction instruction);
	void step_lbu(Instruction instruction);
	void step_lhu(Instruction instruction);
	void step_lui(Instruction instruction);
	void step_lw(Instruction instruction);
	void step_nor(Instruction instruction);
	void step_or(Instruction instruction);
	void step_ori(Instruction instruction);
	void step_slt(Instruction instruction);
	void step_slti(Instruction instruction);
	void step_sltiu(Instruction instruction);
	void step_sltu(Instruction instruction);
	void step_sll(Instruction instruction);
	void step_srl(Instruction instruction);
	void step_sb(Instruction instruction);
	void step_sh(Instruction instruction);
	void step_sw(Instruction instruction);
	void step_sub(Instruction instruction);
	void step_subu(Instruction instruction);
	void step_div(Instruction instruction);
	void step_divu(Instruction instruction);
	void step_mfhi(Instruction instruction);
	void step_mflo(Instruction instruction);
	void step_mult(Instruction instruction);
	void step_multu(Instruction instruction);
	void step_sra(Instruction instruction);
	bool step_syscall();
};

#endif
