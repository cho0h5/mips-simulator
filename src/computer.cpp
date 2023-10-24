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
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs + rt);
}

void Computer::step_addi(Instruction instruction) {
	int32_t value;
	value = registers.signed_get(instruction.rs);
	value += (int16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_addiu(Instruction instruction) {
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value += (int16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_addu(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs + rt);
}

void Computer::step_and(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs & rt);
}

void Computer::step_andi(Instruction instruction) {
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value &= (uint16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_beq(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);

	if (rs == rt) {
		registers.i_format_jump((int16_t)instruction.immediate);
	}
}

void Computer::step_bne(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);

	if (rs != rt) {
		registers.i_format_jump((int16_t)instruction.immediate);
	}
}

void Computer::step_j(Instruction instruction) {
	registers.j_format_jump((uint32_t)instruction.address);
}

void Computer::step_jal(Instruction instruction) {
	uint32_t pc = registers.get_pc();
	registers.set(RA, pc);
	registers.j_format_jump((uint32_t)instruction.address);
}

void Computer::step_jr(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	registers.set_pc(rs);
}

void Computer::step_lbu(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint8_t value = memory->load_byte_unsigned(address);
	registers.set(instruction.rt, value);
}

void Computer::step_lhu(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint16_t value = memory->load_halfword_unsigned(address);
	registers.set(instruction.rt, value);
}

void Computer::step_lui(Instruction instruction) {
	int32_t value = 0;
	value += (uint16_t)instruction.immediate;
	value = value << 16;
	registers.set(instruction.rt, value);
}

void Computer::step_lw(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t value = memory->load_word(address);
	registers.set(instruction.rt, value);
}

void Computer::step_nor(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, ~(rs | rt));
}

void Computer::step_or(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs | rt);
}

void Computer::step_ori(Instruction instruction) {
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value |= (uint16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_slt(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs < rt);
}

void Computer::step_slti(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t compare = rs < (int16_t)instruction.immediate;
	registers.set(instruction.rt, compare);
}

void Computer::step_sltiu(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t compare = rs < (uint16_t)instruction.immediate;
	registers.set(instruction.rt, compare);
}

void Computer::step_sltu(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs < rt);
}

void Computer::step_sll(Instruction instruction) {
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rt << instruction.shamt);
}

void Computer::step_srl(Instruction instruction) {
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rt >> instruction.shamt);
}

void Computer::step_sb(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_byte(address, (uint8_t)rt);
}

void Computer::step_sh(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_halfword(address, (uint16_t)rt);
}

void Computer::step_sw(Instruction instruction) {
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_word(address, (uint32_t)rt);
}

void Computer::step_sub(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs - rt);
}

void Computer::step_subu(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs - rt);
}

void Computer::step_div(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set_lo(rs / rt);
	registers.set_hi(rs % rt);
}

void Computer::step_divu(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set_lo(rs / rt);
	registers.set_hi(rs % rt);
}

void Computer::step_mfhi(Instruction instruction) {
	uint32_t hi = registers.get_hi();
	registers.set(instruction.rd, hi);
}

void Computer::step_mflo(Instruction instruction) {
	uint32_t lo = registers.get_lo();
	registers.set(instruction.rd, lo);
}

void Computer::step_mult(Instruction instruction) {
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	int64_t value = rs * rt;
	registers.set_lo(value >> 32);
	registers.set_hi((uint32_t)value);
}

void Computer::step_multu(Instruction instruction) {
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	uint64_t value = rs * rt;
	registers.set_lo(value >> 32);
	registers.set_hi((uint32_t)value);
}

void Computer::step_sra(Instruction instruction) {
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rt >> instruction.shamt);
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

