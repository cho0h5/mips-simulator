#include <registers.h>

uint32_t Registers::unsigned_get(RegisterName register_name) {
	if (register_name == ZERO)
		return (uint32_t)0;
	return (uint32_t)general_registers[register_name];
}

int32_t Registers::signed_get(RegisterName register_name) {
	if (register_name == ZERO)
		return (int32_t)0;
	return (int32_t)general_registers[register_name];
}

void Registers::set(RegisterName register_name, uint32_t value) {
	if (register_name == ZERO)
		return;
	general_registers[register_name] = value;
}

uint32_t Registers::get_pc() {
	return pc;
}

void Registers::set_pc(uint32_t address) {
	pc = address;
}

void Registers::increase_pc() {
	pc += 4;
}

void Registers::i_format_jump(int16_t branch_address) {
	pc += branch_address;
}

void Registers::j_format_jump(uint32_t branch_address) {
	branch_address = branch_address << 2;
	pc &= 0xF0000000;
	pc |= branch_address;
}

void Registers::set_lo(uint32_t value) {
	lo = value;
}

void Registers::set_hi(uint32_t value) {
	hi = value;
}

uint32_t Registers::get_lo() {
	return lo;
}

uint32_t Registers::get_hi() {
	return hi;
}
