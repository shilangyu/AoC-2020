import strutils
import sets

type
  InsideBag = object
    name: string
    amount: int
  Bag = object
    name: string
    holds: seq[InsideBag]


proc get_input(): seq[Bag] = 
  let lines = readFile("./inputs/day7.txt").split('\n')[0..^2]

  for l in lines:
    let s = l.split(" bags contain ")
    let name = s[0]
    
    var inner = newSeq[InsideBag]();
    for bag in s[1].split(", "):
      let parts = bag.split(' ')
      if parts[0] == "no":
        break
      inner.add(InsideBag(name : parts[1] & " " & parts[2], amount : parts[0].parseInt()))
    
    result.add(Bag(name: name, holds: inner))

  return result

proc find_holding(data: seq[Bag], goal: string): HashSet[string] = 
  var found = newSeq[string]()

  for d in data:
    for inner in d.holds:
      if inner.name == goal:
        found.add(d.name)
        break

  result = toHashSet(found)
  for b in found:
    result = result + find_holding(data, b)

proc count_bags(data: seq[Bag], inside: string): int =
  for d in data:
    if d.name == inside:
      for inner in d.holds:
        result += inner.amount * (count_bags(data, inner.name) + 1)




proc part1(): int =
  let data = get_input()

  result = find_holding(data, "shiny gold").len()

proc part2(): int =
  let data = get_input()

  result = count_bags(data, "shiny gold")


echo "day 7:\n\tpart 1: ", part1(), "\n\tpart 2: ", part2()
