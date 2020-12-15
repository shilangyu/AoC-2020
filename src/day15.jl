get_inputs() = open("./inputs/day15.txt") do f
	readlines(f)[1] |> l -> split(l, ",") .|> string .|> String |> l -> parse.(Int, l)
end


function run_game(upto)
	nums = get_inputs()
	
	prev = pop!(nums)
	
	memo = Dict((num, i) for (i, num) in enumerate(nums))
	
	turn = length(nums) + 1
	
	while turn != upto
		if haskey(memo, prev)
			memo[prev], prev = turn, turn - memo[prev]
		else
			memo[prev] = turn
			prev = 0
		end
		
		turn += 1
	end
	
	return prev
end



part1() = run_game(2020)
part2() = run_game(30000000)

println("day 15:\n\tpart 1: ", part1(), "\n\tpart 2: ", part2())
