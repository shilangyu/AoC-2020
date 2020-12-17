# AoC-2020

[![](https://github.com/shilangyu/AoC-2020/workflows/ci/badge.svg)](https://github.com/shilangyu/AoC-2020/actions)

Advent of Code 2020 in Rust, Golang, Julia, Typescript, Python, C, Nim, C++, Dart, Zig, C#, and Swift

```ts
function writtenIn(day: number): string {
  const choices = [
    "Rust",
    "Golang",
    "Julia",
    "Typescript",
    "Python",
    "C",
    "Nim",
    "C++",
    "Dart",
    "Zig",
    "C#",
    "Swift",
  ];
  return choices[(day - 1) % choices.length];
}
```

| day |         part 1          |         part 2          |
| :-: | :---------------------: | :---------------------: |
|  1  |           ✅            |           ✅            |
|  2  |           ✅            |           ✅            |
|  3  |           ✅            |           ✅            |
|  4  |           ✅            |           ✅            |
|  5  |           ✅            |           ✅            |
|  6  |           ✅            |           ✅            |
|  7  |           ✅            |           ✅            |
|  8  |           ✅            |           ✅            |
|  9  |           ✅            |           ✅            |
| 10  | ❌ (Still studying Zig) | ❌ (Still studying Zig) |
| 11  |           ✅            |           ✅            |
| 12  |           ✅            |           ✅            |
| 13  |           ✅            |           ✅            |
| 14  |           ✅            |           ✅            |
| 15  |           ✅            |           ✅            |
| 16  |           ✅            |           ✅            |
| 17  |           ✅            |           ✅            |
| 18  |           ❌            |           ❌            |
| 19  |           ❌            |           ❌            |
| 20  |           ❌            |           ❌            |
| 21  |           ❌            |           ❌            |
| 22  |           ❌            |           ❌            |
| 23  |           ❌            |           ❌            |
| 24  |           ❌            |           ❌            |
| 25  |           ❌            |           ❌            |

Run all with `./run.sh`. Requires:

- `cargo`
- `go`
- `julia`
- `deno`
- `python`
- `gcc`
- `nim`
- `dart`
- `zig`
- `dotnet`, [`dotnet-script`](https://github.com/filipw/dotnet-script)
- `swift`

<details>
	<summary>WARNING: contains answers</summary>
 
  ```sh
day 1:
	part 1: 858496
	part 2: 263819430
day 2:
	part 1: 396
	part 2: 428
day 3:
	part 1: 205
	part 2: 3952146825
day 4:
	part 1: 202
	part 2: 137
day 5:
	part 1: 938
	part 2: 696
day 6:
	part 1: 6680
	part 2: 3117
day 7:
	part 1: 335
	part 2: 2431
day 8:
	part 1: 1217
	part 2: 501
day 9:
	part 1: 373803594
	part 2: 51152360
day 11:
	part 1: 2277
	part 2: 2066
day 12:
	part 1: 757
	part 2: 51249
day 13:
	part 1: 2545
	part 2: 266204454441577
day 14:
	part 1: 15403588588538
	part 2: 3260587250457
day 15:
	part 1: 421
	part 2: 436
day 16:
	part 1: 27911
	part 2: 737176602479
day 17:
	part 1: 401
	part 2: 2224
  ```
</details>
