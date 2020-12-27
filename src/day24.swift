import Foundation

struct Point: Hashable {
  let x: Double
  let y: Double

	static func +(lhs: Point, rhs: Point) -> Point {
		return Point(x: lhs.x + rhs.x, y: lhs.y + rhs.y)
	}
}


enum Direction: CaseIterable {
	case e
	case se
	case sw
	case w
	case nw
	case ne

	var value: Point {
		switch self {
		case .e:
			return Point(x: 1, y: 0)
		case .se:
			return Point(x: 0.5, y: -0.5)
		case .sw:
			return Point(x: -0.5, y: -0.5)
		case .w:
			return Point(x: -1, y: 0)
		case .nw:
			return Point(x: -0.5, y: 0.5)
		case .ne:
			return Point(x: 0.5, y: 0.5)
		}
	}

	static func tryParse(_ str: String) -> Direction? {
		switch str {
		case "e":
			return .e
		case "se":
			return .se
		case "sw":
			return .sw
		case "w":
			return .w
		case "nw":
			return .nw
		case "ne":
			return .ne
		default:
			return nil
		}
	}
}

func getInput() -> [[Direction]] {
	var res = [[Direction]]()
	let contents = try! String(contentsOfFile: "./inputs/day24.txt", encoding: .utf8)

	for steps in contents.split(separator: "\n") {
		res.append([Direction]())
		
		var str = ""
		
		for c in steps {
			str += [c]

			if let dir = Direction.tryParse(str) {
				res[res.count-1].append(dir)
				str = ""
			}
		}
	}

	return res
}


func turnTiles(_ directionList: [[Direction]]) -> Set<Point> {
	var black = Set<Point>()

	for directions in directionList {
		let curr = directions.reduce(Point(x: 0, y: 0), { acc, curr in
			acc + curr.value
		})

		if black.contains(curr) {
			black.remove(curr)
		} else {
			black.insert(curr)
		}
	}
	
	return black
}

func part1() -> Int {
	let directionList = getInput()

	return turnTiles(directionList).count
}

func part2() -> Int {
	let directionList = getInput()

	var black = turnTiles(directionList)

	for _ in 1...100 {
		var neighbors = [Point : Int]()

		for pos in black {
			for dir in Direction.allCases {
				neighbors[pos + dir.value, default: 0] += 1
			}
		}

		var new = Set<Point>()

		for (pos, blacks) in neighbors {
			let isBlack = black.contains(pos)

			if isBlack && (blacks == 1 || blacks == 2) {
				new.insert(pos)
			}
			if !isBlack && blacks == 2 {
				new.insert(pos)
			}
		}

		black = new
	}

	return black.count
}

print("""
day 24:
	part 1: \(part1())
	part 2: \(part2())
""")
