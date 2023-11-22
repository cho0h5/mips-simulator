mod instruction;
mod parser;

use crate::instruction::Funct::*;
use crate::instruction::RegisterName::*;
use crate::instruction::OpCode::*;
use crate::instruction::Instruction::*;
use crate::instruction::*;
use crate::instruction::ConvertToBinary;

use crate::parser::parse;

fn write_binary_file(instructions: &[Instruction]) -> Result<(), std::io::Error> {
    use std::fs::File;
    use std::io::prelude::*;
    use std::path::Path;

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
    let filename = std::env::args().nth(1).expect("no filename");
    let instructions = parse(&filename);

    println!("write binary file");
    println!("--------");
    if let Ok(_) = write_binary_file(&instructions) {
        println!("--------");
        println!("done");
    } else {
        println!("failed");
    };
}
