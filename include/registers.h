#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>

enum RegisterName {
	ZERO = 0,
	AT,
	V0,
	V1,
	A0,
	A1,
	A2,
	A3,
	T0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	T8,
	T9,
	K0,
	K1,
	GP,
	SP,
	FP,
	RA,
};

class Registers {
	public:
	uint32_t unsigned_get(RegisterName register_name);
	int32_t signed_get(RegisterName register_name);
	void set(RegisterName register_name, uint32_t value);

	uint32_t get_pc();
	void increase_pc();
	void i_format_jump(int16_t branch_addr);
	void j_format_jump(uint32_t branch_addr);

	private:
	uint32_t general_registers[32];
	uint32_t pc;
};

#endif
