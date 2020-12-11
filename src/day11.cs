using System;
using System.IO;

using Board = System.Collections.Generic.List<System.Collections.Generic.List<State>>;

Board getInput()
{
	Board data = new();

	using (var file = new StreamReader("./inputs/day11.txt"))
	{
		string line;
		while ((line = file.ReadLine()) != null)
		{
			data.Add(new());
			foreach (var c in line)
			{
				data[^1].Add(c switch
				{
					'L' => State.empty,
					'.' => State.floor,
					'#' => State.occupied,
					_ => throw new Exception("unreachable")
				});
			}
		}

	}

	return data;
}

Board nextGen(Board data, Func<Board, int, int, State, State> counter)
{
	var copy = data.ConvertAll(e => e.ConvertAll(r => r));

	for (int i = 0; i < data.Count; i++)
	{
		for (int j = 0; j < data[i].Count; j++)
		{
			copy[i][j] = data[i][j] switch
			{
				State.floor => State.floor,
				State.empty or State.occupied => counter(data, i, j, data[i][j]),
				_ => throw new Exception("unreachable")
			};
		}
	}

	return copy;
}


bool areSame(Board d1, Board d2)
{
	for (int i = 0; i < d1.Count; i++)
	{
		for (int j = 0; j < d1[0].Count; j++)
		{
			if (d1[i][j] != d2[i][j]) return false;
		}
	}
	return true;
}



int part1()
{
	var data = getInput();

	while (true)
	{
		var next = nextGen(data, (Board data, int i, int j, State s) =>
		{
			var occ = 0;

			for (int k = -1; k < 2; k++)
			{
				for (int l = -1; l < 2; l++)
				{
					if (k == 0 && l == 0 || i + k < 0 || i + k >= data.Count || j + l < 0 || j + l >= data[0].Count)
					{
						continue;
					}
					if (data[i + k][j + l] == State.occupied)
					{
						occ++;
					}
				}
			}

			return s switch
			{
				State.empty when occ == 0 => State.occupied,
				State.occupied when occ >= 4 => State.empty,
				_ => s
			};
		});

		if (areSame(next, data))
		{
			int counter = 0;
			foreach (var row in data)
			{
				foreach (var s in row)
				{
					counter += s switch
					{
						State.occupied => 1,
						_ => 0
					};
				}
			}
			return counter;
		}

		data = next;
	}
}

int part2()
{
	var data = getInput();

	while (true)
	{
		var next = nextGen(data, (Board data, int i, int j, State s) =>
		{
			var occ = 0;

			for (int k = -1; k < 2; k++)
			{
				for (int l = -1; l < 2; l++)
				{
					int y = i;
					int x = j;
					if (k == 0 && l == 0) continue;
					while (true)
					{
						y += k;
						x += l;
						if (y < 0 || y >= data.Count || x < 0 || x >= data[0].Count)
						{
							break;
						}

						if (data[y][x] == State.occupied)
						{
							occ++;
							break;
						}
						else if (data[y][x] == State.empty)
						{
							break;
						}
					}
				}
			}

			return s switch
			{
				State.empty when occ == 0 => State.occupied,
				State.occupied when occ >= 5 => State.empty,
				_ => s
			};
		});

		if (areSame(next, data))
		{
			int counter = 0;
			foreach (var row in data)
			{
				foreach (var s in row)
				{
					counter += s switch
					{
						State.occupied => 1,
						_ => 0
					};
				}
			}
			return counter;
		}

		data = next;
	}
}

Console.WriteLine($@"day 11:
	part 1: {part1()}
	part 2: {part2()}");
enum State { occupied, floor, empty };
