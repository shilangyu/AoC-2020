package main

import (
	"bufio"
	"fmt"
	"os"
)

const maskSize = 36

type bitState byte

const (
	bitStateZero bitState = iota
	bitStateOne
	bitStateNothing
)

func (b bitState) apply(to uint64, at int) uint64 {
	switch b {
	case bitStateZero:
		to &^= (1 << (maskSize - 1 - at))
	case bitStateOne:
		to |= 1 << (maskSize - 1 - at)
	}

	return to
}

type overwrite struct {
	at   uint64
	with uint64
}

type block struct {
	mask       [maskSize]bitState
	overwrites []overwrite
}

func getInput() []block {
	file, _ := os.Open("./inputs/day14.txt")
	defer file.Close()

	res := []block{}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		if scanner.Text()[:2] == "ma" {
			b := block{}

			curr := 0
			str := ""
			fmt.Sscanf(scanner.Text(), "mask = %s", &str)
			for _, c := range str {
				switch c {
				case 'X':
					b.mask[curr] = bitStateNothing
				case '0':
					b.mask[curr] = bitStateZero
				case '1':
					b.mask[curr] = bitStateOne
				}
				curr++
			}

			res = append(res, b)
		} else {
			o := overwrite{}
			fmt.Sscanf(scanner.Text(), "mem[%d] = %d", &o.at, &o.with)
			res[len(res)-1].overwrites = append(res[len(res)-1].overwrites, o)
		}
	}

	return res
}

func part1() uint64 {
	memory := map[uint64]uint64{}

	data := getInput()

	for _, b := range data {
		for _, over := range b.overwrites {
			memory[over.at] = over.with

			for i, bit := range b.mask {
				memory[over.at] = bit.apply(memory[over.at], i)
			}
		}

	}

	sum := uint64(0)
	for _, m := range memory {
		sum += m
	}

	return sum
}

func part2() uint64 {
	memory := map[uint64]uint64{}

	data := getInput()

	for _, b := range data {
		for _, over := range b.overwrites {
			floating := [maskSize]bitState{}
			amount := 0

			for i, bit := range b.mask {
				switch bit {
				case bitStateZero:
					floating[i] = bitState((over.at >> (maskSize - i - 1)) & 1)
				case bitStateOne:
					floating[i] = bit
				case bitStateNothing:
					floating[i] = bit
					amount++
				}
			}

			for i := 0; i < (1 << amount); i++ {
				addr := uint64(0)
				curr := 0
				for pos, state := range floating {
					bit := uint64(0)
					switch state {
					case bitStateOne:
						bit = 1
					case bitStateNothing:
						bit = uint64(i>>(amount-curr-1)) & 1
						curr++
					}
					addr |= bit << (maskSize - 1 - pos)
				}
				memory[addr] = over.with
			}
		}

	}

	sum := uint64(0)
	for _, m := range memory {
		sum += m
	}

	return sum
}

func main() {
	fmt.Printf(`day 14:
	part 1: %d
	part 2: %d
`, part1(), part2())
}
