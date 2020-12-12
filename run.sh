#!/bin/sh

cargo eval src/day01.rs
go run src/day02.go
julia src/day03.jl
deno run --allow-read --quiet src/day04.ts
python src/day05.py
gcc src/day06.c -Wall -o temp.out && ./temp.out && rm temp.out
nim r src/day07.nim 2>/dev/null
g++ src/day08.cpp -Wall -o temp.out && ./temp.out && rm temp.out
dart run src/day09.dart
dotnet script src/day11.cs
swift src/day12.swift
