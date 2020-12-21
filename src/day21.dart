import 'dart:collection';
import 'dart:io';

class Food {
  List<String> ingredients, allergens;
}

Future<List<Food>> getInput() async {
  final file = File("./inputs/day21.txt");
  var res = <Food>[];

  for (final line in await file.readAsLines()) {
    var sp = line.split(' (contains ');
    sp[1] = sp[1].split(')')[0];

    res.add(Food()
      ..ingredients = sp[0].split(' ')
      ..allergens = sp[1].split(', '));
  }

  return res;
}

HashMap<String, Set<String>> getAssigned(List<Food> foods) {
  var assigned = HashMap<String, Set<String>>();

  for (final food in foods) {
    for (final aller in food.allergens) {
      if (assigned.containsKey(aller)) {
        assigned[aller] = assigned[aller].intersection({...food.ingredients});
      } else {
        assigned[aller] = {...food.ingredients};
      }
    }
  }

  return assigned;
}

Future<int> part1() async {
  final data = await getInput();

  final assigned = getAssigned(data);

  final correct = {...assigned.values.expand((e) => e)};

  var res = 0;
  for (final food in data) {
    for (final ingr in food.ingredients) {
      if (!correct.contains(ingr)) {
        res++;
      }
    }
  }

  return res;
}

Future<String> part2() async {
  final data = await getInput();

  final assigned = getAssigned(data);

  // as in day 16, taking one by one
  // Map<ingredient, allergen>
  Map<String, String> answer = {};
  while (answer.length != assigned.length) {
    for (final ass in assigned.entries) {
      if (ass.value.length == 1) {
        final correct = ass.value.first;

        answer[correct] = ass.key;

        for (final ass in assigned.entries) {
          assigned[ass.key].remove(correct);
        }

        break;
      }
    }
  }

  final res = answer.keys.toList()
    ..sort((a, b) => answer[a].compareTo(answer[b]));

  return res.join(',');
}

main() async {
  print('''day 21:
	part 1: ${await part1()}
	part 2: ${await part2()}''');
}
