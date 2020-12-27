get_input() = open("./inputs/day3.txt") do f
	readlines(f) |> l -> split.(l, "")
end

function count_trees(Δx, Δy)
	slope = get_input()
	
	x = 1
	y = 1
	
	trees = 0
	
	while y <= length(slope)
		if slope[y][x] == "#"
			trees += 1
		end
		
		x += Δx
		y += Δy
		
		if x > length(slope[1])
			x %= length(slope[1])
		end
	end
	
	return trees
end

part1() = count_trees(3, 1)
	
part2() = ([(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)] .|> args -> count_trees(args...)) |> prod

println("day 3:
	part 1: ", part1(), "
	part 2: ", part2())
