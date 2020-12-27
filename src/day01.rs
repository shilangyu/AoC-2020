use std::collections::HashSet;

fn get_input() -> Vec<i32> {
    include_str!("../inputs/day1.txt")
        .lines()
        .map(|e| e.parse().unwrap())
        .collect()
}

const GOAL: i32 = 2020;

fn part1() -> i32 {
    let nums = get_input();

    let set: HashSet<_> = nums.iter().collect();

    for num in &nums {
        if set.contains(&(GOAL - num)) {
            return num * (GOAL - num);
        }
    }

    unreachable!()
}

fn part2() -> i32 {
    let nums = get_input();

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
    println!("day 1:
	part 1: {}
	part 2: {}", part1(), part2());
}
