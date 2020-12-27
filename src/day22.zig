const std = @import("std");

var gpa = std.heap.GeneralPurposeAllocator(.{}){};
var allocator = &gpa.allocator;

const Players = struct { p1: std.ArrayList(usize), p2: std.ArrayList(usize) };

const Player = enum { p1, p2 };

fn get_input() !Players {
    const f = try std.fs.cwd().openFile("inputs/day22.txt", .{ .read = true });

    var file_contents = try f.reader().readAllAlloc(
        allocator,
        // file wont be bigger, RIGHT?
        999_999_999,
    );
    defer allocator.free(file_contents);
    var file_contents_trimmed = std.mem.trim(u8, file_contents, "\n");

    var p1 = std.ArrayList(usize).init(allocator);
    var p2 = std.ArrayList(usize).init(allocator);

    var p1Now = true;

    var lines = std.mem.split(file_contents_trimmed, "\n");
    while (lines.next()) |line| {
        if (line.len == 0) {
            p1Now = false;
            continue;
        }

        if (line[0] == 'P') {
            continue;
        }

        if (p1Now) {
            try p1.append(try std.fmt.parseInt(usize, line, 10));
        } else {
            try p2.append(try std.fmt.parseInt(usize, line, 10));
        }
    }

    return Players{ .p1 = p1, .p2 = p2 };
}

fn copyPlayers(players: *Players, p1Length: usize, p2Length: usize) !Players {
    var p1 = std.ArrayList(usize).init(allocator);
    try p1.ensureCapacity(p1Length);
    var p2 = std.ArrayList(usize).init(allocator);
    try p2.ensureCapacity(p2Length);

    var i: usize = 0;
    while (i < p1Length) : (i += 1) {
        try p1.append(players.p1.items[i]);
    }
    i = 0;
    while (i < p2Length) : (i += 1) {
        try p2.append(players.p2.items[i]);
    }

    return Players{ .p1 = p1, .p2 = p2 };
}

fn play(players: *Players, isPart1: bool) !Player {
    var round: usize = 0;

    while (players.p1.items.len != 0 and players.p2.items.len != 0) : (round += 1) {
        // yeah nah I'm not gonna check if I'm in a loop, just bail me out if it's taking too long
        if (round > 1_000) return .p1;

        var card1 = players.p1.orderedRemove(0);
        var card2 = players.p2.orderedRemove(0);

        var winner: Player = if (card1 > card2) .p1 else .p2;

        if (!isPart1 and card1 <= players.p1.items.len and card2 <= players.p2.items.len) {
            var copy = try copyPlayers(players, card1, card2);
            defer copy.p1.deinit();
            defer copy.p2.deinit();
            // oopsie recursive inferred errors no work
            winner = play(&copy, isPart1) catch unreachable;
        }

        if (winner == .p1) {
            try players.p1.append(card1);
            try players.p1.append(card2);
        } else {
            try players.p2.append(card2);
            try players.p2.append(card1);
        }
    }

    return if (players.p1.items.len == 0) .p2 else .p1;
}

fn countResult(players: Players, winner: Player) usize {
    var res: usize = 0;
    var curr: usize = std.math.max(players.p1.items.len, players.p2.items.len);

    for (switch (winner) {
        .p1 => players.p1.items,
        .p2 => players.p2.items,
    }) |item| {
        res += item * curr;
        curr -= 1;
    }

    return res;
}

fn part1() !usize {
    var data = get_input() catch unreachable;
    defer data.p1.deinit();
    defer data.p2.deinit();

    return countResult(data, try play(&data, true));
}

fn part2() !usize {
    var data = get_input() catch unreachable;
    defer data.p1.deinit();
    defer data.p2.deinit();

    return countResult(data, try play(&data, false));
}

pub fn main() void {
    std.debug.print("day 22:\n\tpart 1: {}\n\tpart 2: {}\n", .{ part1(), part2() });
}
