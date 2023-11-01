#include <computer.h>

using namespace std;

void Computer::run() {
	while(!step()) {}
}

bool Computer::step() {
	Instruction instruction = memory->fetch_instruction(registers.get_pc());
	registers.increase_pc();

	if (instruction.format == R_FORMAT) {
		switch (instruction.funct) {
			case FT_ADD:
				step_add(instruction);
				break;
			case FT_ADDU:
				step_addu(instruction);
				break;
			case FT_AND:
				step_and(instruction);
				break;
			case FT_JR:
				step_jr(instruction);
				break;
			case FT_NOR:
				step_nor(instruction);
				break;
			case FT_OR:
				step_or(instruction);
				break;
			case FT_SLT:
				step_slt(instruction);
				break;
			case FT_SLTU:
				step_sltu(instruction);
				break;
			case FT_SLL:
				step_sll(instruction);
				break;
			case FT_SRL:
				step_srl(instruction);
				break;
			case FT_SUB:
				step_sub(instruction);
				break;
			case FT_SUBU:
				step_subu(instruction);
				break;
			case FT_DIV:
				step_div(instruction);
				break;
			case FT_DIVU:
				step_divu(instruction);
				break;
			case FT_MFHI:
				step_mfhi(instruction);
				break;
			case FT_MFLO:
				step_mflo(instruction);
				break;
			case FT_MULT:
				step_mult(instruction);
				break;
			case FT_MULTU:
				step_multu(instruction);
				break;
			case FT_SRA:
				step_sra(instruction);
				break;
			case FT_SYSCALL:
				return step_syscall();
				break;
		}
	} else {
		switch (instruction.opcode) {
			case OP_ADDI:
				step_addi(instruction);
				break;
			case OP_ADDIU:
				step_addiu(instruction);
				break;
			case OP_ANDI:
				step_andi(instruction);
				break;
			case OP_BEQ:
				step_beq(instruction);
				break;
			case OP_BNE:
				step_bne(instruction);
				break;
			case OP_J:
				step_j(instruction);
				break;
			case OP_JAL:
				step_jal(instruction);
				break;
			case OP_LBU:
				step_lbu(instruction);
				break;
			case OP_LHU:
				step_lhu(instruction);
				break;
			case OP_LUI:
				step_lui(instruction);
				break;
			case OP_LW:
				step_lw(instruction);
				break;
			case OP_ORI:
				step_ori(instruction);
				break;
			case OP_SLTI:
				step_slti(instruction);
				break;
			case OP_SLTIU:
				step_sltiu(instruction);
				break;
			case OP_SB:
				step_sb(instruction);
				break;
			case OP_SH:
				step_sh(instruction);
				break;
			case OP_SW:
				step_sw(instruction);
				break;
			default:
				break;
		}
	}
	return 0;
}

void Computer::step_add(Instruction instruction) {
	cout << "[debug] add\n";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs + rt);
}

void Computer::step_addi(Instruction instruction) {
	cout << "[debug] addi ";
	int32_t value;
	value = registers.signed_get(instruction.rs);
	value += (int16_t)instruction.immediate;
	registers.set(instruction.rt, value);
	cout << value << '\n';
}

void Computer::step_addiu(Instruction instruction) {
	cout << "[debug] addiu\n";
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value += (int16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_addu(Instruction instruction) {
	cout << "[debug] addu\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs + rt);
}

void Computer::step_and(Instruction instruction) {
	cout << "[debug] and\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs & rt);
}

void Computer::step_andi(Instruction instruction) {
	cout << "[debug] andi\n";
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value &= (uint16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_beq(Instruction instruction) {
	cout << "[debug] beq\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);

	if (rs == rt) {
		registers.i_format_jump((int16_t)instruction.immediate);
	}
}

void Computer::step_bne(Instruction instruction) {
	cout << "[debug] bne\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);

	if (rs != rt) {
		registers.i_format_jump((int16_t)instruction.immediate);
	}
}

void Computer::step_j(Instruction instruction) {
	cout << "[debug] j\n";
	registers.j_format_jump((uint32_t)instruction.address);
}

void Computer::step_jal(Instruction instruction) {
	cout << "[debug] jal\n";
	uint32_t pc = registers.get_pc();
	registers.set(RA, pc);
	registers.j_format_jump((uint32_t)instruction.address);
}

void Computer::step_jr(Instruction instruction) {
	cout << "[debug] jr\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	registers.set_pc(rs);
}

void Computer::step_lbu(Instruction instruction) {
	cout << "[debug] lbu\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint8_t value = memory->load_byte_unsigned(address);
	registers.set(instruction.rt, value);
}

void Computer::step_lhu(Instruction instruction) {
	cout << "[debug] lhu\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint16_t value = memory->load_halfword_unsigned(address);
	registers.set(instruction.rt, value);
}

void Computer::step_lui(Instruction instruction) {
	cout << "[debug] lui\n";
	int32_t value = 0;
	value += (uint16_t)instruction.immediate;
	value = value << 16;
	registers.set(instruction.rt, value);
}

void Computer::step_lw(Instruction instruction) {
	cout << "[debug] lw\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t value = memory->load_word(address);
	registers.set(instruction.rt, value);
}

void Computer::step_nor(Instruction instruction) {
	cout << "[debug] nor\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, ~(rs | rt));
}

void Computer::step_or(Instruction instruction) {
	cout << "[debug] or\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs | rt);
}

void Computer::step_ori(Instruction instruction) {
	cout << "[debug] ori\n";
	uint32_t value;
	value = registers.unsigned_get(instruction.rs);
	value |= (uint16_t)instruction.immediate;
	registers.set(instruction.rt, value);
}

void Computer::step_slt(Instruction instruction) {
	cout << "[debug] slt\n";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs < rt);
}

void Computer::step_slti(Instruction instruction) {
	cout << "[debug] slti ";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t compare = rs < (int16_t)instruction.immediate;
	registers.set(instruction.rt, compare);
	cout << compare << '\n';
}

void Computer::step_sltiu(Instruction instruction) {
	cout << "[debug] sltiu\n";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t compare = rs < (uint16_t)instruction.immediate;
	registers.set(instruction.rt, compare);
}

void Computer::step_sltu(Instruction instruction) {
	cout << "[debug] sltu\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs < rt);
}

void Computer::step_sll(Instruction instruction) {
	cout << "[debug] sll\n";
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rt << instruction.shamt);
}

void Computer::step_srl(Instruction instruction) {
	cout << "[debug] srl\n";
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rt >> instruction.shamt);
}

void Computer::step_sb(Instruction instruction) {
	cout << "[debug] sb\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_byte(address, (uint8_t)rt);
}

void Computer::step_sh(Instruction instruction) {
	cout << "[debug] sh\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_halfword(address, (uint16_t)rt);
}

void Computer::step_sw(Instruction instruction) {
	cout << "[debug] sw\n";
	uint32_t address;
	address = registers.unsigned_get(instruction.rs);
	address += (int16_t)instruction.immediate;
	uint32_t rt = registers.unsigned_get(instruction.rt);
	memory->store_word(address, (uint32_t)rt);
}

void Computer::step_sub(Instruction instruction) {
	cout << "[debug] sub\n";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rs - rt);
}

void Computer::step_subu(Instruction instruction) {
	cout << "[debug] subu\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set(instruction.rd, rs - rt);
}

void Computer::step_div(Instruction instruction) {
	cout << "[debug] div\n";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set_lo(rs / rt);
	registers.set_hi(rs % rt);
}

void Computer::step_divu(Instruction instruction) {
	cout << "[debug] divu\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	registers.set_lo(rs / rt);
	registers.set_hi(rs % rt);
}

void Computer::step_mfhi(Instruction instruction) {
	cout << "[debug] mfhi\n";
	uint32_t hi = registers.get_hi();
	registers.set(instruction.rd, hi);
}

void Computer::step_mflo(Instruction instruction) {
	cout << "[debug] mflo\n";
	uint32_t lo = registers.get_lo();
	registers.set(instruction.rd, lo);
}

void Computer::step_mult(Instruction instruction) {
	cout << "[debug] mult ";
	int32_t rs = registers.signed_get(instruction.rs);
	int32_t rt = registers.signed_get(instruction.rt);
	int64_t value = rs * rt;
	registers.set_hi(value >> 32);
	registers.set_lo((uint32_t)value);
	cout << (value >> 32) << ' ' << (uint32_t)value << '\n';
}

void Computer::step_multu(Instruction instruction) {
	cout << "[debug] multu\n";
	uint32_t rs = registers.unsigned_get(instruction.rs);
	uint32_t rt = registers.unsigned_get(instruction.rt);
	uint64_t value = rs * rt;
	registers.set_hi(value >> 32);
	registers.set_lo((uint32_t)value);
}

void Computer::step_sra(Instruction instruction) {
	cout << "[debug] sra\n";
	int32_t rt = registers.signed_get(instruction.rt);
	registers.set(instruction.rd, rt >> instruction.shamt);
}

bool Computer::step_syscall() {
	cout << "[debug] syscall\n";
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

