#!/bin/sh

rustc src/day01.rs -o temp.out && ./temp.out && rm temp.out &&
go run src/day02.go &&
julia src/day03.jl &&
deno run --allow-read --quiet src/day04.ts &&
python src/day05.py &&
gcc src/day06.c -Wall -o temp.out && ./temp.out && rm temp.out &&
nim r src/day07.nim 2>/dev/null &&
g++ src/day08.cpp -Wall -std=c++17 -o temp.out && ./temp.out && rm temp.out &&
dart run src/day09.dart &&
zig run src/day10.zig &&
dotnet script src/day11.cs &&
swift src/day12.swift &&
rustc src/day13.rs -o temp.out && ./temp.out && rm temp.out &&
go run src/day14.go &&
julia src/day15.jl &&
deno run --allow-read --quiet src/day16.ts &&
python src/day17.py &&
gcc src/day18.c -Wall -o temp.out && ./temp.out && rm temp.out &&
nim r src/day19.nim 2>/dev/null &&
g++ src/day20.cpp -Wall -std=c++17 -O3 -o temp.out && ./temp.out && rm temp.out &&
dart run src/day21.dart &&
zig run src/day22.zig &&
dotnet script src/day23.cs &&
swift src/day24.swift &&
deno run src/day25.js
