import tables
import strutils
import options

type
  Rule = object
    character: Option[char]
    subrules: seq[seq[int]]


proc get_input(): (Table[int, Rule], seq[string]) = 
  var rules = initTable[int, Rule]()
  let lines = readFile("./inputs/day19.txt").split('\n')[0..^2]

  var strings_started = false
  var strings = newSeq[string]()

  for l in lines:
    if strings_started:
      strings.add(l)
      continue
    
    let s = l.split(": ")
    if s.len() == 1:
      strings_started = true
      continue
    let rule_num = s[0].parseInt()

    if s[1][0] == '"':
      rules[rule_num] = Rule(character: some(s[1][1]), subrules: @[])
    else:
      var subrules = newSeq[seq[int]]()
      for options in s[1].split(" | "):
        subrules.add(newSeq[int]())
        for num in options.split(' '):
          subrules[^1].add(num.parseInt())
      
      rules[rule_num] = Rule(character: none(char), subrules: subrules)
          
  return (rules, strings)


const not_found = -1
func matches(rules: Table[int, Rule], rule: int, str: string, index: int): int =
  let curr = rules[rule]
  if curr.character.isSome():
    if curr.character.get() == str[index]:
      return index + 1
    else:
      return not_found
  
  for subrule in curr.subrules:
    var matched = true
    var currIndex = index
    for subsubrule in subrule:
      let temp = matches(rules, subsubrule, str, currIndex)
      if temp == not_found:
        matched = false
        break
      currIndex = temp

    if matched:
      return currIndex

  return not_found

proc part1(): int =
  let (rules, data) = get_input()
  
  for l in data:
    if matches(rules, 0, l, 0) == l.len():
      result += 1


proc part2(): int =
  var (rules, data) = get_input()

  rules[8] = Rule(character: none(char), subrules: @[@[42], @[42, 8]])
  rules[11] = Rule(character: none(char), subrules: @[@[42, 31], @[42, 11, 31]])
  
  # for l in data:
  #   if matches(rules, 0, l, 0) == l.len():
  #     result += 1


echo "day 19:\n\tpart 1: ", part1(), "\n\tpart 2: ", part2()
