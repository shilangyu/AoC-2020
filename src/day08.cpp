#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

enum class Op
{
	jmp,
	acc,
	nop
};

struct Instruction
{
	Op op;
	int val;
};

vector<Instruction> read_input()
{
	ifstream f;
	f.open("./inputs/day8.txt");
	string line;
	vector<Instruction> res;

	while (getline(f, line))
	{
		string opstr = line.substr(0, line.find(" "));
		int val = stoi(line.substr(line.find(" ") + 1));

		Op op;
		if (opstr == "jmp")
			op = Op::jmp;
		else if (opstr == "acc")
			op = Op::acc;
		else
			op = Op::nop;

		res.push_back({op, val});
	}

	return res;
}

int part1()
{
	auto data = read_input();

	int acc = 0;
	size_t pointer = 0;
	unordered_set<size_t> visited;

	while (true)
	{
		if (visited.find(pointer) != visited.end())
		{
			return acc;
		}

		visited.insert(pointer);

		switch (data[pointer].op)
		{
		case Op::acc:
			acc += data[pointer].val;
			pointer++;
			break;
		case Op::jmp:
			pointer += data[pointer].val;
			break;
		case Op::nop:
		default:
			pointer++;
			break;
		}
	}

	// unreachable
	return 0;
}

int part2()
{
	auto data = read_input();

	// brute force yay!
	for (size_t i = 0; i < data.size(); i++)
	{
		auto was = data[i].op;
		if (was == Op::nop)
			data[i].op = Op::jmp;
		else if (was == Op::jmp)
			data[i].op = Op::nop;
		else
			continue;

		int acc = 0;
		int pointer = 0;
		unordered_set<int> visited;

		while (pointer >= 0)
		{
			if (pointer == static_cast<int>(data.size()))
				return acc;

			if (visited.find(pointer) != visited.end())
				break;

			visited.insert(pointer);

			switch (data[pointer].op)
			{
			case Op::acc:
				acc += data[pointer].val;
				pointer++;
				break;
			case Op::jmp:
				pointer += data[pointer].val;
				break;
			case Op::nop:
			default:
				pointer++;
				break;
			}
		}

		data[i].op = was;
	}

	// unreachable
	return 0;
}

int main(int argc, char *argv[])
{
	cout << "day 8:" << endl
			 << "\tpart 1: " << part1() << endl
			 << "\tpart 2: " << part2() << endl;
	return 0;
}
