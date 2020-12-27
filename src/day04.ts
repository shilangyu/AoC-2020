const passportFields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"];

async function getInput(): Promise<string[]> {
  const data = await Deno.readFile("./inputs/day4.txt");
  return new TextDecoder("utf-8").decode(data).split("\n\n");
}

type ParsedPassport = [key: string, value: any][];

function getFields(passport: string): ParsedPassport {
  return [...passport.matchAll(/(\w+):(.+?)(?: |$)/gm)].map((e) => {
    let parsed: any = e[2];

    switch (e[1]) {
      case "byr":
      case "iyr":
      case "eyr":
        parsed = Number(e[2]);
        break;
      case "hgt":
        parsed = [Number(e[2].slice(0, -2)), e[2].slice(-2)];
        break;
    }

    return [e[1], parsed];
  });
}

function validKeys(passport: ParsedPassport): boolean {
  const keys = passport.map((e) => e[0]);
  return passportFields.every((f) => f === "cid" || keys.includes(f));
}

async function part1() {
  const data = await getInput();
  let valid = 0;

  for (const passport of data) {
    const fields = getFields(passport);
    if (validKeys(fields)) {
      valid++;
    }
  }

  return valid;
}

async function part2() {
  const data = await getInput();
  let valid = 0;

  for (const passport of data) {
    const fields = getFields(passport);
    if (validKeys(fields)) {
      const validValues = fields.every((e) => {
        switch (e[0]) {
          case "byr":
            return e[1] <= 2002 && e[1] >= 1920;
          case "iyr":
            return e[1] <= 2020 && e[1] >= 2010;
          case "eyr":
            return e[1] <= 2030 && e[1] >= 2020;
          case "hgt":
            if ("in" === e[1][1]) {
              return e[1][0] <= 76 && e[1][0] >= 59;
            } else if ("cm" === e[1][1]) {
              return e[1][0] <= 193 && e[1][0] >= 150;
            }
            return false;
          case "hcl":
            return /^#[0-9a-f]{6}$/.test(e[1]);
          case "ecl":
            return ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"].includes(
              e[1]
            );
          case "pid":
            return /^\d{9}$/.test(e[1]);
          default:
            return true;
        }
      });

      if (validValues) {
        valid++;
      }
    }
  }

  return valid;
}

console.log(`day 4:
	part 1: ${await part1()}
	part 2: ${await part2()}`);
