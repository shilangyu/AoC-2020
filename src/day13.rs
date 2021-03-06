fn get_input() -> (i32, Vec<Option<i32>>) {
    let mut lines = include_str!("../inputs/day13.txt").lines();

    (
        lines.next().unwrap().parse().unwrap(),
        lines.next().unwrap().split(',').map(|e| e.parse().ok()).collect(),
    )
}

fn part1() -> i32 {
    let (goal, buses) = get_input();

    let mut best = i32::MAX;
    let mut res = 0;

    for num in buses.into_iter().filter_map(|e| e) {
        let curr = goal - (goal % num) + num;
        if curr < best {
            best = curr;
            res = num * (best - goal);
        }
    }

    return res;
}

fn part2() -> usize {
    let (_, buses) = get_input();
    // !!assumes inputs are coprimes which they happen to be!!
    assert_coprimes(&buses);

    let buses: Vec<_> = buses.into_iter().map(|e| e.map(|d| d as usize)).collect();

    let mut res = 0;
    let mut prod = 1;
    for (i, bus) in buses.into_iter().enumerate() {
        if let Some(num) = bus {
            while (res + i) % num != 0 {
                res += prod;
            }
            prod *= num;
        }
    }

    return res;
}

fn main() {
    println!(
        "day 13:
	part 1: {}
	part 2: {}",
        part1(),
        part2()
    );
}

fn assert_coprimes(nums: &Vec<Option<i32>>) {
    // taken from `num` crate
    fn gcd(mut n1: i32, mut n2: i32) -> i32 {
        while n2 != 0 {
            let temp = n2;
            n2 = n1 % temp;
            n1 = temp;
        }
        n1.abs()
    }

    for n1 in nums.iter().filter_map(|&e| e) {
        for n2 in nums.iter().filter_map(|&e| e) {
            if n1 == n2 {
                continue;
            }
            if gcd(n1, n2) != 1 {
                unreachable!()
            }
        }
    }
}
