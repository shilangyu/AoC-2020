use std::collections::HashSet;

use crate::helpers;

pub fn silver() -> i32 {
    const GOAL: i32 = 2020;
    let nums: Vec<_> = helpers::file_lines("./inputs/day1.txt")
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
pub fn gold() -> i32 {
    const GOAL: i32 = 2020;
    let nums: Vec<_> = helpers::file_lines("./inputs/day1.txt")
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
