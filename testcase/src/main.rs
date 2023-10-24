#[derive(Debug, Copy, Clone)]
enum RegisterName {
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

#[derive(Debug, Copy, Clone)]
enum OpCode {
    RFORMAT = 0b000000,
	ADDI	= 0b001000,
	ADDIU	= 0b001001,
	ANDI	= 0b001100,
	BEQ		= 0b000100,
	BNE		= 0b000101,
	Jump	= 0b000010,
	JAL		= 0b000011,
	LBU		= 0b100100,
	LHU		= 0b100101,
	LUI		= 0b001111,
	LW		= 0b100011,
	ORI		= 0b001101,
	SLTI	= 0b001010,
	SLTIU	= 0b001011,
	SB		= 0b101000,
	SH		= 0b101001,
	SW		= 0b101011,
}

#[derive(Debug, Copy, Clone)]
enum Funct {
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

#[derive(Debug)]
enum Instruction {
    R(RFormat),
    I(IFormat),
    J(JFormat),
}

impl Convert for Instruction {
    fn convert(&self) -> u32 {
        match self {
            Instruction::R(f) => f.convert(),
            Instruction::I(f) => f.convert(),
            Instruction::J(f) => f.convert(),
        }
    }
}

#[derive(Debug)]
struct RFormat {
    rs: RegisterName,
    rt: RegisterName,
    rd: RegisterName,
    shamt: u8,
    funct: Funct,
}

impl Convert for RFormat {
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

#[derive(Debug)]
struct IFormat {
    opcode: OpCode,
    rs: RegisterName,
    rt: RegisterName,
    immediate: i16,
}

impl Convert for IFormat {
    fn convert(&self) -> u32 {
        let mut instruction: u32;
        instruction = (self.opcode as u32 & 0b111111) << 26;
        instruction |= (self.rs as u32 & 0b11111) << 21;
        instruction |= (self.rt as u32 & 0b11111) << 16;
        instruction |= (self.immediate as u16 as u32) << 0;
        instruction
    }
}

#[derive(Debug)]
struct JFormat {
    opcode: OpCode,
    address: u32,
}

impl Convert for JFormat {
    fn convert(&self) -> u32 {
        let mut instruction: u32;
        instruction = (self.opcode as u32 & 0b111111) << 26;
        instruction |= (self.address & 0x03FFFFFF) << 0;
        instruction
    }
}

trait Convert {
    fn convert(&self) -> u32;
}

fn write_binary_file(instructions: &[Instruction]) -> Result<(), std::io::Error> {
    use std::fs::File;
    use std::io::prelude::*;
    use std::path::Path;

    println!("write binary file");

    let path = Path::new("example.bin");

    let mut file = File::create(&path)?;

    for instruction in instructions {
        let bin = instruction.convert();
        println!("{:08x}", bin);

        let mut buf: [u8; 4] = [
            (bin >> 24) as u8,
            (bin >> 16) as u8,
            (bin >> 8) as u8,
            (bin >> 0) as u8,
        ];

        file.write(&buf);
    }
    Ok(())
}

use Instruction::*;
use RegisterName::*;
use OpCode::*;
use Funct::*;

fn main() {
    let instructions = [
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A2, immediate: 10}),             // A2 = 10
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A1, immediate: 0}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A2, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        R(RFormat {rs: A2, rt: A1, rd: A1, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: A2, rt: A2, immediate: -1}),             // A2 = 10

        R(RFormat {rs: A1, rt: ZERO, rd: A0, shamt: 0, funct: Add}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 1}),              // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
        I(IFormat {opcode: ADDI, rs: ZERO, rt: A0, immediate: '\n' as i16}),    // A0 = '\n'
        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 11}),             // V0 = 1
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall

        I(IFormat {opcode: ADDI, rs: ZERO, rt: V0, immediate: 10}),             // V0 = 10
        R(RFormat {rs: ZERO, rt: ZERO, rd: ZERO, shamt: 0, funct: Syscall}),    // syscall
    ];

    if let Err(_) = write_binary_file(&instructions) {
        println!("failed");
    };
}
