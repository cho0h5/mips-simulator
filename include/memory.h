#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

#include <registers.h>

enum InstructionFormat {
	R_FORMAT,
	I_FORMAT,
	J_FORMAT,
};

enum OpCode {
	OP_ADD		= 0b000000,
	OP_ADDI		= 0b001000,
	OP_ADDIU	= 0b001001,
	OP_ADDU		= 0b000000,
	OP_AND		= 0b000000,
	OP_ANDI		= 0b001100,
	OP_BEQ		= 0b000100,
	OP_BNE		= 0b000101,
	OP_J		= 0b000010,
	OP_JAL		= 0b000011,
	OP_JR		= 0b000000,
	OP_LBU		= 0b100100,
	OP_LHU		= 0b100101,
	OP_LL		= 0b110000,
	OP_LUI		= 0b001111,
	OP_LW		= 0b100011,
	OP_NOR		= 0b000000,
	OP_OR		= 0b000000,
	OP_ORI		= 0b001101,
	OP_SLT		= 0b000000,
	OP_SLTI		= 0b001010,
	OP_SLTIU	= 0b001011,
	OP_SLTU		= 0b000000,
	OP_SLL		= 0b000000,
	OP_SRL		= 0b000000,
	OP_SB		= 0b101000,
	OP_SH		= 0b101001,
	OP_SW		= 0b101011,
	OP_SUB		= 0b000000,
	OP_SUBU		= 0b000000,
	OP_DIV		= 0b000000,
	OP_DIVU		= 0b000000,
	OP_MFHI		= 0b000000,
	OP_MFLO		= 0b000000,
	OP_MULT		= 0b000000,
	OP_MULTU	= 0b000000,
	OP_SRA		= 0b000000,
	OP_SYSCALL	= 0b000000,
};

enum Funct {
	FT_ADD		= 0b100000,
	FT_ADDU		= 0b100001,
	FT_AND		= 0b100100,
	FT_JR		= 0b001000,
	FT_NOR		= 0b100111,
	FT_OR		= 0b100101,
	FT_SLT		= 0b101010,
	FT_SLTU		= 0b101011,
	FT_SLL		= 0b000000,
	FT_SRL		= 0b000010,
	FT_SUB		= 0b100010,
	FT_SUBU		= 0b100011,
	FT_DIV		= 0b011010,
	FT_DIVU		= 0b011011,
	FT_MFHI		= 0b010000,
	FT_MFLO		= 0b010010,
	FT_MULT		= 0b011000,
	FT_MULTU	= 0b011001,
	FT_SRA		= 0b000011,
	FT_SYSCALL	= 0b001100,
};

struct Instruction {
	InstructionFormat	format;
	OpCode				opcode;
	RegisterName		rs;
	RegisterName		rt;
	RegisterName		rd;
	uint8_t				shamt;
	Funct				funct;
	uint16_t			immediate;
	uint32_t			address;
};

class Memory {
	public:
	bool load_program(std::string filename);
	Instruction fetch_instruction(int pc);
	static void print_instruction(Instruction instruction);

	private:
	uint8_t memory[0x100000000];

	static InstructionFormat categorize_format(OpCode opcode);
};

#endif
