mod instruction;

use crate::instruction::Funct::*;
use crate::instruction::RegisterName::*;
use crate::instruction::OpCode::*;
use crate::instruction::Instruction::*;
use crate::instruction::*;
use crate::instruction::ConvertToBinary;

fn write_binary_file(instructions: &[Instruction]) -> Result<(), std::io::Error> {
    use std::fs::File;
    use std::io::prelude::*;
    use std::path::Path;

    println!("write binary file");
    println!("--------");

    let path = Path::new("example.bin");

    let mut file = File::create(&path)?;

    for instruction in instructions {
        let bin = instruction.convert();
        println!("{:08x}", bin);

        let buf: [u8; 4] = [
            (bin >> 24) as u8,
            (bin >> 16) as u8,
            (bin >> 8) as u8,
            (bin >> 0) as u8,
        ];

        file.write(&buf)?;
    }
    Ok(())
}

fn main() {
    // RFormat::new(ZERO, A2, T0,  0, Slt)
    let instructions = [
        IFormat::new(Addi, ZERO, A0, 5),
        JFormat::new(Jal, 10),
        RFormat::new(V0, ZERO, A0, 0, Add),
        IFormat::new(Addi, ZERO, V0, 1),
        RFormat::new(ZERO, ZERO, ZERO, 0, Syscall),
        IFormat::new(Addi, ZERO, A0, '\n' as i16),
        IFormat::new(Addi, ZERO, V0, 11),
        RFormat::new(ZERO, ZERO, ZERO, 0, Syscall),
        IFormat::new(Addi, ZERO, V0, 10),
        RFormat::new(ZERO, ZERO, ZERO, 0, Syscall),

        IFormat::new(Addi, SP, SP, -8), // fact
        IFormat::new(Sw, SP, RA, 4),
        IFormat::new(Sw, SP, A0, 0),
        IFormat::new(Slti, A0, T0, 1),
        IFormat::new(Beq, ZERO, T0, 3),
        IFormat::new(Addi, ZERO, V0, 1),
        IFormat::new(Addi, SP, SP, 8),
        RFormat::new(RA, ZERO, ZERO, 0, Jr),
        IFormat::new(Addi, A0, A0, -1), // L1
        JFormat::new(Jal, 10),
        IFormat::new(Lw, SP, A0, 0),
        IFormat::new(Lw, SP, RA, 4),
        IFormat::new(Addi, SP, SP, 8),
        RFormat::new(A0, V0, ZERO, 0, Mult),
        RFormat::new(ZERO, ZERO, V0, 0, Mflo),
        RFormat::new(RA, ZERO, ZERO, 0, Jr),
    ];

    if let Ok(_) = write_binary_file(&instructions) {
        println!("--------");
        println!("done");
    } else {
        println!("failed");
    };
}
