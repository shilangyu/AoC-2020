import Foundation


struct Instruction {
	var cmd: Character
	var value: Int
}

func getInputs() -> [Instruction] {
	var res = [Instruction]()
	let contents = try! String(contentsOfFile: "./inputs/day12.txt", encoding: .utf8)

	for cmd in contents.split(separator:"\n") {
		res.append(Instruction(
			cmd: cmd[cmd.startIndex], 
			value: Int(cmd[cmd.index(after: cmd.startIndex)...])!
		))	
	}

	return res
}

func intRotate(vec: (Int, Int), deg: Int) -> (Int, Int) {
	let toDeg = Double.pi / 180
	let x = Double(vec.0) * cos(toDeg*Double(deg)) - Double(vec.1) * sin(toDeg*Double(deg))
	let y = Double(vec.0) * sin(toDeg*Double(deg)) + Double(vec.1) * cos(toDeg*Double(deg))
	
	return (Int(x.rounded()), Int(y.rounded()))
}


func part1() -> Int {
	var dir = (1, 0)
	var pos = (0, 0)

	for instr in getInputs() {
		switch instr.cmd {
			case "F":
				pos.0 += dir.0 * instr.value
				pos.1 += dir.1 * instr.value
			case "L":
				dir = intRotate(vec: dir, deg: instr.value)
			case "R":
				dir = intRotate(vec: dir, deg: 360 - instr.value)
			case "N":
				pos.1 += instr.value
			case "E":
				pos.0 += instr.value
			case "S":
				pos.1 -= instr.value
			case "W":
				pos.0 -= instr.value
			default:
				break;
		} 
	}

	return abs(pos.0) + abs(pos.1)
}

func part2() -> Int {
	var pos = (0, 0)
	var waypoint = (10, 1)

	for instr in getInputs() {
		switch instr.cmd {
			case "F":
				pos.0 += waypoint.0 * instr.value
				pos.1 += waypoint.1 * instr.value
			case "L":
				waypoint = intRotate(vec: waypoint, deg: instr.value)
			case "R":
				waypoint = intRotate(vec: waypoint, deg: 360 - instr.value)
			case "N":
				waypoint.1 += instr.value
			case "E":
				waypoint.0 += instr.value
			case "S":
				waypoint.1 -= instr.value
			case "W":
				waypoint.0 -= instr.value
			default:
				break;
		}
	}

	return abs(pos.0) + abs(pos.1)
}

print("""
day 12:
	part 1: \(part1())
	part 2: \(part2())
""")
