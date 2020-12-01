use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn file_lines(name: &str) -> Vec<String> {
    let reader = BufReader::new(File::open(name).unwrap());
    reader
        .lines()
        .map(|l| l.expect("Could not parse line"))
        .collect()
}
