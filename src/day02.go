package main

import (
	"bufio"
	"fmt"
	"os"
)

type pass struct {
	low, high int
	char      rune
	password  string
}

func getInput() []pass {
	res := []pass{}

	file, _ := os.Open("./inputs/day2.txt")
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		curr := pass{}
		fmt.Sscanf(scanner.Text(), "%d-%d %c: %s", &curr.low, &curr.high, &curr.char, &curr.password)
		res = append(res, curr)
	}

	return res
}

func part1() (amount int) {
	passes := getInput()

	for _, pass := range passes {
		curr := 0
		for _, c := range pass.password {
			if c == pass.char {
				curr++
			}
		}
		if curr <= pass.high && curr >= pass.low {
			amount++
		}
	}

	return
}

func part2() (amount int) {
	passes := getInput()

	for _, pass := range passes {
		// poor-mans logical xor
		if (rune(pass.password[pass.low-1]) == pass.char) != (rune(pass.password[pass.high-1]) == pass.char) {
			amount++
		}
	}

	return
}

func main() {
	fmt.Printf(`day 2:
	part 1: %d
	part 2: %d
`, part1(), part2())
}
