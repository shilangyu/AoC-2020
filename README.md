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
| 18  |           ✅            |           ✅            |
| 19  |           ✅            |           ❌            |
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
