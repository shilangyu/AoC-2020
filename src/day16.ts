type Range = [low: number, high: number];

class Property {
  constructor(public r1: Range, public r2: Range) {}

  valid = (num: number) =>
    (this.r1[0] <= num && this.r1[1] >= num) ||
    (this.r2[0] <= num && this.r2[1] >= num);
}

async function getInput(): Promise<
  [
    props: Property[],
    nearby: number[][],
    myTicket: number[],
    departureIndices: number[]
  ]
> {
  const data = await Deno.readFile("./inputs/day16.txt");
  const str = new TextDecoder("utf-8").decode(data);

  const props: Property[] = [];
  const departureIndices = <number[]>[];
  let i = 0;
  for (const match of str.matchAll(/([\w ]+): (\d+)-(\d+) or (\d+)-(\d+)$/gm)) {
    props.push(
      new Property(
        [Number(match[2]), Number(match[3])],
        [Number(match[4]), Number(match[5])]
      )
    );

    if (match[1].startsWith("departure")) {
      departureIndices.push(i);
    }
    i++;
  }

  let found = false;
  let nearby = [];
  for (const line of str.split("\n")) {
    if (line === "nearby tickets:") {
      found = true;
      continue;
    } else if (found) {
      if (line === "") break;

      nearby.push(line.split(",").map(Number));
    }
  }

  found = false;
  let myTicket = <number[]>[];
  for (const line of str.split("\n")) {
    if (line === "your ticket:") {
      found = true;
      continue;
    } else if (found) {
      myTicket = line.split(",").map(Number);
      break;
    }
  }

  return [props, nearby, myTicket, departureIndices];
}

async function part1() {
  const [props, nearby] = await getInput();

  return nearby
    .flat()
    .filter((e) => props.every((p) => !p.valid(e)))
    .reduce((acc, curr) => acc + curr, 0);
}

async function part2() {
  let [props, nearby, myTicket, departureIndices] = await getInput();

  nearby = nearby.filter((e) => e.every((g) => props.some((p) => p.valid(g))));

  let possibilities: { [k: number]: number[] } = {};
  for (let i = 0; i < props.length; i++) {
    for (let j = 0; j < props.length; j++) {
      const prop = props[j];

      let found = true;
      for (const near of nearby) {
        if (!prop.valid(near[i])) {
          found = false;
          break;
        }
      }

      if (found) {
        if (possibilities[i] === undefined) {
          possibilities[i] = [j];
        } else {
          possibilities[i].push(j);
        }
      }
    }
  }

  let assigned: { [k: string]: string } = {};
  // apparently possibilities are arranged in a way where I can pick one column at a time...
  while (Object.keys(possibilities).length !== 0) {
    const [column, [property]] = Object.entries(possibilities).find(
      ([column, poss]) => poss.length === 1
      // ...
    ) as any;

    assigned[property] = column;
    delete possibilities[column];

    for (const key in possibilities) {
      if (Object.prototype.hasOwnProperty.call(possibilities, key)) {
        possibilities[key] = possibilities[key].filter((e) => e !== property);
      }
    }
  }

  let prod = 1;
  for (const i of departureIndices) {
    prod *= myTicket[assigned[i] as any];
  }

  return prod;
}

console.log(`day 16:
	part 1: ${await part1()}
	part 2: ${await part2()}`);
