use std::fs::read_to_string;

use crate::instruction::Funct::*;
use crate::instruction::RegisterName::*;
use crate::instruction::OpCode::*;
use crate::instruction::Instruction::*;
use crate::instruction::*;

pub fn parse(filename: &str) -> Vec<Instruction> {
    for line in read_to_string(filename).unwrap().lines() {
        println!("{:?}", line.to_string().split(":").collect::<Vec<_>>());
    }

    Vec::new()
}
