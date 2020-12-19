const std = @import("std");

var gpa = std.heap.GeneralPurposeAllocator(.{}){};
var allocator = &gpa.allocator;

fn get_input() !std.ArrayList(i32) {
    const f = try std.fs.cwd().openFile("inputs/day10.txt", .{ .read = true });

    var file_contents = try f.reader().readAllAlloc(
        allocator,
        // file wont be bigger, RIGHT?
        999_999_999,
    );
    defer allocator.free(file_contents);
    var file_contents_trimmed = std.mem.trim(u8, file_contents, "\n");

    var data = std.ArrayList(i32).init(allocator);

    var lines = std.mem.split(file_contents_trimmed, "\n");
    while (lines.next()) |line| {
        try data.append(try std.fmt.parseInt(i32, line, 10));
    }

    return data;
}

fn part1() i32 {
    var data = get_input() catch unreachable;
    defer data.deinit();

    std.sort.sort(i32, data.items, {}, comptime std.sort.asc(i32));
    data.insert(0, 0) catch unreachable;
    data.append(data.items[data.items.len - 1] + 3) catch unreachable;

    var ones: i32 = 0;
    var threes: i32 = 0;

    var i: usize = 1;
    while (i < data.items.len) : (i += 1) {
        const diff = data.items[i] - data.items[i - 1];

        if (diff == 1) {
            ones += 1;
        } else if (diff == 3) {
            threes += 1;
        }
    }

    return ones * threes;
}

fn dp(data: std.ArrayList(i32), memo: *std.AutoHashMap(usize, usize), curr: usize) usize {
    if (memo.contains(curr)) {
        return memo.get(curr).?;
    }

    var res: usize = 0;
    var i: usize = 1;
    while (i <= 3) : (i += 1) {
        if (curr + i >= data.items.len) {
            break;
        }
        if (data.items[curr + i] - data.items[curr] <= 3) {
            res += dp(data, memo, curr + i);
        }
    }
    res = std.math.max(res, 1);
    memo.put(curr, res) catch unreachable;

    return res;
}

fn part2() usize {
    var data = get_input() catch unreachable;
    defer data.deinit();

    std.sort.sort(i32, data.items, {}, comptime std.sort.asc(i32));
    data.insert(0, 0) catch unreachable;
    data.append(data.items[data.items.len - 1] + 3) catch unreachable;

    var memo = std.AutoHashMap(usize, usize).init(allocator);
    defer memo.deinit();

    return dp(data, &memo, 0);
}

pub fn main() void {
    std.debug.print("day 10:\n\tpart 1: {}\n\tpart 2: {}\n", .{ part1(), part2() });
}
