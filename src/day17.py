from collections import defaultdict


def get_input():
    res = set()
    with open("./inputs/day17.txt") as f:
        for i, row in enumerate(f.readlines()):
            for j, e in enumerate(row[:-1]):
                if e == '#':
                    res.add((i, j))
    return res


def next_gen(old_gen, active_map):
    new = set()
    for pos, amt in active_map.items():
        was_active = pos in old_gen
        if not was_active and amt == 3 or was_active and (amt == 2 or amt == 3):
            new.add(pos)
    return new


def part1():
    data = set(((i, j, 0) for i, j in get_input()))

    for _ in range(6):
        active = defaultdict(lambda: 0)

        for i, j, k in data:
            for di in range(-1, 2):
                for dj in range(-1, 2):
                    for dk in range(-1, 2):
                        if di == dj == dk == 0:
                            continue
                        active[(i + di, j + dj, k + dk)] += 1
        data = next_gen(data, active)

    return len(data)


def part2():
    data = set(((i, j, 0, 0) for i, j in get_input()))

    for _ in range(6):
        active = defaultdict(lambda: 0)

        for i, j, k, w in data:
            for di in range(-1, 2):
                for dj in range(-1, 2):
                    for dk in range(-1, 2):
                        for dw in range(-1, 2):
                            if di == dj == dk == dw == 0:
                                continue
                            active[(i + di, j + dj, k + dk, w + dw)] += 1
        data = next_gen(data, active)

    return len(data)


print(f'''day 17:
	part 1: {part1()}
	part 2: {part2()}''')
