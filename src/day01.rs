use std::collections::HashSet;

use std::fs::File;
use std::io::{BufRead, BufReader};

fn file_lines(name: &str) -> Vec<String> {
    let reader = BufReader::new(File::open(name).unwrap());
    reader
        .lines()
        .map(|l| l.expect("Could not parse line"))
        .collect()
}

fn silver() -> i32 {
    const GOAL: i32 = 2020;
    let nums: Vec<_> = file_lines("./inputs/day1.txt")
        .into_iter()
        .map(|e| e.parse::<i32>().unwrap())
        .collect();

    let set: HashSet<_> = nums.iter().collect();

    for num in &nums {
        if set.contains(&(GOAL - num)) {
            return num * (GOAL - num);
        }
    }

    unreachable!()
}

fn gold() -> i32 {
    const GOAL: i32 = 2020;
    let nums: Vec<_> = file_lines("./inputs/day1.txt")
        .into_iter()
        .map(|e| e.parse::<i32>().unwrap())
        .collect();

    let set: HashSet<_> = nums.iter().collect();

    for num_curr in &nums {
        let curr = GOAL - num_curr;
        for num in &nums {
            if set.contains(&(curr - num)) {
                return num * num_curr * (curr - num);
            }
        }
    }

    unreachable!()
}

fn main() {
    println!("day 1:\n\tpart 1: {}\n\tpart 2: {}", silver(), gold());
}
