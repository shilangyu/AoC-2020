using System;
using System.IO;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;


(Cups, int firstCup, int lastCup) getInput()
{
	using (var file = new StreamReader("./input.txt"))
	{
		var line = file.ReadLine();
		return (new(line), line[0] - '0', line[^1] - '0');
	}
}


string part1()
{
	var (cups, currentCup, _) = getInput();

	for (int round = 0; round < 100; round++)
	{
		cups.makeMove(currentCup);
		currentCup = cups[currentCup];
	}

	return cups.ToString()[1..];
}

BigInteger part2()
{
	var (cups, currentCup, lastCup) = getInput();

	cups[lastCup] = 10;
	for (int i = 10; i <= 1_000_000; i++)
		cups.cupVecMap.Add(i + 1);
	cups[1_000_000] = currentCup;

	for (int round = 0; round < 10_000_000; round++)
	{
		cups.makeMove(currentCup);
		currentCup = cups[currentCup];
	}

	var a = cups[1];
	var b = cups[a];

	return new BigInteger(a) * b;
}

Console.WriteLine($@"day 23:
    part 1: {part1()}
    part 2: {part2()}");


class Cups
{
	// Map<cup, cup_after_that>
	public List<int> cupVecMap;

	public int this[int index]
	{
		get => cupVecMap[index];
		set => cupVecMap[index] = value;
	}

	public Cups(string initialCups)
	{
		var temp = initialCups.ToCharArray().Select(e => e - '0').ToList();

		cupVecMap = new List<int>(temp);
		cupVecMap.Add(-1);

		for (int i = 0; i < temp.Count - 1; i++)
			cupVecMap[temp[i]] = temp[i + 1];

		cupVecMap[temp[temp.Count - 1]] = temp[0];
		cupVecMap[0] = -1;
	}

	public (int, int, int) pickUp(int at)
	{
		var c1 = this[at];
		var c2 = this[c1];
		var c3 = this[c2];

		return (c1, c2, c3);
	}

	public int destination(int of)
	{
		int goal = of - 1;
		var (c1, c2, c3) = pickUp(of);

		while (true)
		{
			if (goal == 0) goal = cupVecMap.Count - 1;

			if (goal != c1 && goal != c2 && goal != c3)
				return goal;

			goal -= 1;
		}

		throw new Exception("unreachable");
	}
	public void makeMove(int from)
	{
		var (c1, c2, c3) = pickUp(from);
		var dest = destination(from);

		this[from] = this[c3];
		this[c3] = this[dest];
		this[dest] = c1;
	}


	public override string ToString()
	{
		var curr = 1;
		var res = "";

		do
		{
			res += curr.ToString();
			curr = this[curr];
		} while (curr != 1);

		return res;
	}
}
