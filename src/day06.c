#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** get_input(size_t* length) {
  static const size_t BUFFER_SIZE = 30;
  char buffer[BUFFER_SIZE];
  // ugh ugh that better be enough
  char** result = malloc(sizeof(char**) * 2200);

  size_t i = 0;

  FILE* fp = fopen("./inputs/day6.txt", "r");
  while (fgets(buffer, BUFFER_SIZE, fp)) {
    result[i] = malloc(sizeof(char*) * BUFFER_SIZE);
    strtok(buffer, "\n");
    strcpy(result[i++], buffer);
  }

  fclose(fp);

  result[i++] = "\n";
  *(length) = i;

  return result;
}

int part1() {
  size_t lines;
  char** data = get_input(&lines);

  int sum = 0;
  const size_t alphabet_size = 'z' - 'a' + 1;
  int qs[alphabet_size];
  for (size_t i = 0; i < alphabet_size; i++) {
    qs[i] = 0;
  }

  for (size_t n = 0; n < lines; n++) {
    if (data[n][0] == '\n') {
      for (size_t i = 0; i < alphabet_size; i++) {
        sum += qs[i];
        qs[i] = 0;
      }
      continue;
    }

    for (size_t i = 0; i < strlen(data[n]); i++) {
      qs[data[n][i] - 'a'] = 1;
    }
  }

  return sum;
}

int part2() {
  size_t lines;
  char** data = get_input(&lines);

  int sum = 0;
  int people = 0;
  const size_t alphabet_size = 'z' - 'a' + 1;
  int qs[alphabet_size];
  for (size_t i = 0; i < alphabet_size; i++) {
    qs[i] = 0;
  }

  for (size_t n = 0; n < lines; n++) {
    if (data[n][0] == '\n') {
      for (size_t i = 0; i < alphabet_size; i++) {
        if (qs[i] == people)
          sum++;
        qs[i] = 0;
      }
      people = 0;
      continue;
    }

    people++;

    for (size_t i = 0; i < strlen(data[n]); i++) {
      qs[data[n][i] - 'a']++;
    }
  }

  return sum;
}

int main(int argc, char* argv[]) {
  printf("day 6:\n\tpart 1: %d\n\tpart 2: %d\n", part1(), part2());

  return 0;
}
