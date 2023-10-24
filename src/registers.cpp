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

void Registers::increase_pc() {
	pc += 4;
}
