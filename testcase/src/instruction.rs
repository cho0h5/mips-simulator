#[allow(dead_code)]
#[derive(Debug, Copy, Clone)]
pub enum RegisterName {
	ZERO,
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
}

#[allow(dead_code)]
#[derive(Debug, Copy, Clone)]
pub enum OpCode {
    Rformat = 0b000000,
	Addi	= 0b001000,
	Addiu	= 0b001001,
	Andi	= 0b001100,
	Beq		= 0b000100,
	Bne		= 0b000101,
	Jump	= 0b000010,
	Jal		= 0b000011,
	Lbu		= 0b100100,
	Lhu		= 0b100101,
	Lui		= 0b001111,
	Lw		= 0b100011,
	Ori		= 0b001101,
	Slti	= 0b001010,
	Sltiu	= 0b001011,
	Sb		= 0b101000,
	Sh		= 0b101001,
	Sw		= 0b101011,
}

#[allow(dead_code)]
#[derive(Debug, Copy, Clone)]
pub enum Funct {
	Add		= 0b100000,
	Addu	= 0b100001,
	And		= 0b100100,
	Jr		= 0b001000,
	Nor		= 0b100111,
	Or		= 0b100101,
	Slt		= 0b101010,
	Sltu	= 0b101011,
	Sll		= 0b000000,
	Srl		= 0b000010,
	Sub		= 0b100010,
	Subu	= 0b100011,
	Div		= 0b011010,
	Divu	= 0b011011,
	Mfhi	= 0b010000,
	Mflo	= 0b010010,
	Mult	= 0b011000,
	Multu	= 0b011001,
	Sra		= 0b000011,
	Syscall	= 0b001100,
}

#[allow(dead_code)]
#[derive(Debug)]
pub enum Instruction {
    R(RFormat),
    I(IFormat),
    J(JFormat),
}

use crate::Instruction::*;

impl ConvertToBinary for Instruction {
    fn convert(&self) -> u32 {
        match self {
            Instruction::R(f) => f.convert(),
            Instruction::I(f) => f.convert(),
            Instruction::J(f) => f.convert(),
        }
    }
}

#[allow(dead_code)]
#[derive(Debug)]
pub struct RFormat {
    rs: RegisterName,
    rt: RegisterName,
    rd: RegisterName,
    shamt: u8,
    funct: Funct,
}

#[allow(dead_code)]
impl RFormat {
    pub fn new(rs: RegisterName, rt: RegisterName, rd: RegisterName,
        shamt: u8, funct: Funct) -> Instruction {
        R(RFormat {rs, rt, rd, shamt, funct})
    }
}

impl ConvertToBinary for RFormat {
    fn convert(&self) -> u32 {
        let mut instruction: u32;
        instruction = (self.rs as u32 & 0b11111) << 21;
        instruction |= (self.rt as u32 & 0b11111) << 16;
        instruction |= (self.rd as u32 & 0b11111) << 11;
        instruction |= (self.shamt as u32 & 0b11111) << 6;
        instruction |= (self.funct as u32 & 0b111111) << 0;
        instruction
    }
}

#[allow(dead_code)]
#[derive(Debug)]
pub struct IFormat {
    opcode: OpCode,
    rs: RegisterName,
    rt: RegisterName,
    immediate: i16,
}

#[allow(dead_code)]
impl IFormat {
    pub fn new(opcode: OpCode, rs: RegisterName, rt: RegisterName,
        immediate: i16) -> Instruction {
        I(IFormat {opcode, rs, rt, immediate})
    }
}

#[allow(dead_code)]
impl ConvertToBinary for IFormat {
    fn convert(&self) -> u32 {
        let mut instruction: u32;
        instruction = (self.opcode as u32 & 0b111111) << 26;
        instruction |= (self.rs as u32 & 0b11111) << 21;
        instruction |= (self.rt as u32 & 0b11111) << 16;
        instruction |= (self.immediate as u16 as u32) << 0;
        instruction
    }
}

#[allow(dead_code)]
#[derive(Debug)]
pub struct JFormat {
    opcode: OpCode,
    address: u32,
}

#[allow(dead_code)]
impl JFormat {
    pub fn new(opcode: OpCode, address: u32) -> Instruction {
        J(JFormat {opcode, address})
    }
}

impl ConvertToBinary for JFormat {
    fn convert(&self) -> u32 {
        let mut instruction: u32;
        instruction = (self.opcode as u32 & 0b111111) << 26;
        instruction |= (self.address & 0x03FFFFFF) << 0;
        instruction
    }
}

pub trait ConvertToBinary {
    fn convert(&self) -> u32;
}
