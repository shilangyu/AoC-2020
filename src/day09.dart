import 'dart:collection';
import 'dart:io';
import 'dart:math';

const preambleSize = 25;

Future<List<int>> getInput() async {
  var file = File("./inputs/day9.txt");
  return (await file.readAsLines()).map(int.parse).toList();
}

Future<int> part1() async {
  final preamble = HashSet<int>();
  final data = await getInput();

  var i = 0;
  for (final num in data) {
    if (preamble.length == preambleSize) {
      var found = false;
      for (final n1 in preamble) {
        if (num - n1 != n1 && preamble.contains(num - n1)) {
          found = true;
          break;
        }
      }

      if (!found) return num;

      preamble.remove(data[i - preambleSize]);
    }
    preamble.add(num);
    i++;
  }

  throw Exception("unreachable");
}

Future<int> part2() async {
  final data = await getInput();
  final goal = await part1();

  var sum = 0;
  for (final l in range(0, data.length)) {
    sum = data[l];

    for (final r in range(l + 1, data.length)) {
      sum += data[r];

      if (sum == goal) {
        return data.getRange(l, r + 1).reduce(min) +
            data.getRange(l, r + 1).reduce(max);
      }
    }
  }

  throw Exception("unreachable");
}

main() async {
  print('''day 9:
	part 1: ${await part1()}
	part 2: ${await part2()}''');
}

Iterable<int> range(int low, int high) sync* {
  for (int i = low; i < high; ++i) yield i;
}
