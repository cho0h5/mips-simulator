#include <memory.h>

#include <fstream>

using namespace std;

bool Memory::load_program(string filename) {
	std::ifstream file(filename, ios::binary | ios::ate);

	if (file) {
		int size = file.tellg();
		file.seekg(0, ios::beg);

		file.read((char*)memory, size);

		file.close();
		return 0;
	}
	return 1;
}

Instruction Memory::fetch_instruction(int pc) {
	uint32_t word = 0;
	Instruction instruction;
	word |= memory[pc + 0] << 24;
	word |= memory[pc + 1] << 16;
	word |= memory[pc + 2] << 8;
	word |= memory[pc + 3] << 0;

	instruction.opcode = (OpCode)(word >> 26);
	instruction.format = categorize_format(instruction.opcode);
	if (instruction.format == R_FORMAT) {
		instruction.rs = (RegisterName)((word >> 21) & 0b11111);
		instruction.rt = (RegisterName)((word >> 16) & 0b11111);
		instruction.rd = (RegisterName)((word >> 11) & 0b11111);
		instruction.shamt = (word >> 6) & 0b11111;
		instruction.funct = (Funct)((word >> 0) & 0b111111);
	} else if (instruction.format == I_FORMAT) {
		instruction.rs = (RegisterName)((word >> 21) & 0b11111);
		instruction.rt = (RegisterName)((word >> 16) & 0b11111);
		instruction.immediate = (word >> 0) & 0xFFFF;
	} else {
		instruction.address = word & 0x03FFFFFF;
	}

	return instruction;
}

void Memory::print_instruction(Instruction instruction) {
	printf("opcode: 0x%02x\n", instruction.opcode);
	printf("format: %d\n", instruction.format);
	if (instruction.format == R_FORMAT) {
		printf("rs: %d\n", instruction.rs);
		printf("rt: %d\n", instruction.rt);
		printf("rd: %d\n", instruction.rd);
		printf("shamt: %d\n", instruction.shamt);
		printf("funct: %d\n", instruction.funct);
	} else if (instruction.format == I_FORMAT) {
		printf("rs: %d\n", instruction.rs);
		printf("rt: %d\n", instruction.rt);
		printf("immediate: %d\n", instruction.immediate);
	} else {
		printf("address: %d\n", instruction.address);
	}
}

InstructionFormat Memory::categorize_format(OpCode opcode) {
	if (opcode == 0b000000)
		return R_FORMAT;
	if (opcode == OP_J)
		return J_FORMAT;
	if (opcode == OP_JAL)
		return J_FORMAT;
	return I_FORMAT;
}

uint8_t Memory::load_byte_unsigned(uint32_t address) {
	return memory[address];
}

uint16_t Memory::load_halfword_unsigned(uint32_t address) {
	uint16_t temp = 0;
	temp |= memory[address + 0] << 8;
	temp |= memory[address + 1] << 0;
	return temp;
}

uint32_t Memory::load_word(uint32_t address) {
	uint32_t temp = 0;
	temp |= memory[address + 0] << 24;
	temp |= memory[address + 1] << 16;
	temp |= memory[address + 2] << 8;
	temp |= memory[address + 3] << 0;
	return temp;
}

void Memory::store_byte(uint32_t address, uint8_t value) {
	memory[address] = value;
}

void Memory::store_halfword(uint32_t address, uint16_t value) {
	memory[address + 0] = value >> 8;
	memory[address + 1] = value >> 0;
}

void Memory::store_word(uint32_t address, uint32_t value) {
	memory[address + 0] = value >> 24;
	memory[address + 1] = value >> 16;
	memory[address + 2] = value >> 8;
	memory[address + 3] = value >> 0;
}
