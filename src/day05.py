import math


def get_input():
    with open("./inputs/day5.txt") as f:
        return [x[:-1] for x in f.readlines()]


def binar_partition(low, high, seq, left, right):
    for c in seq:
        m = math.floor((high + low)/2)
        if c == left:
            high = m - 1
        if c == right:
            low = m + 1

    return low


def part1():
    data = get_input()
    biggest = 0

    for seq in data:
        row = binar_partition(0, 127, seq[:-3], 'F', 'B')
        column = binar_partition(0, 7, seq[-3:], 'L', 'R')
        biggest = max(biggest, row*8 + column)

    return biggest


def part2():
    data = get_input()

    all_seats = set()
    for i in range(128):
        for j in range(8):
            all_seats.add(i * 8 + j)

    for seq in data:
        row = binar_partition(0, 127, seq[:-3], 'F', 'B')
        column = binar_partition(0, 7, seq[-3:], 'L', 'R')
        all_seats.remove(row * 8 + column)

    for row_id in all_seats:
        if 128 < row_id < 1024-128:
            return row_id

    raise Exception("unreachable")


print(f'''day 5:
	part 1: {part1()}
	part 2: {part2()}''')
