#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long u64;

char** get_input(size_t* length) {
  static const size_t BUFFER_SIZE = 200;
  char buffer[BUFFER_SIZE];
  // ugh ugh that better be enough, REALLY not feeling like making it dynamic
  char** result = malloc(sizeof(char**) * 400);

  size_t i = 0;

  FILE* fp = fopen("./inputs/day18.txt", "r");
  while (fgets(buffer, BUFFER_SIZE, fp)) {
    result[i] = malloc(sizeof(char*) * BUFFER_SIZE);
    strtok(buffer, "\n");
    strcpy(result[i++], buffer);
  }

  fclose(fp);

  *length = i;

  return result;
}

u64 eval1(const char* str, size_t* start) {
  u64 val = 0;
  bool multiply = false;

  while (*start < strlen(str)) {
    char curr = str[(*start)++];
    if (curr == ')')
      break;

    switch (curr) {
      case ' ':
        break;
      case '*':
      case '+':
        multiply = curr == '*';
        break;
      default: {
        int num;
        if (curr >= '0' && curr <= '9')
          num = curr - '0';
        else
          num = eval1(str, start);

        if (multiply) {
          val *= num;
        } else {
          val += num;
        }
      }
    }
  }

  return val;
}

u64 eval2(const char* str, size_t* start) {
  u64 sum = 0;
  u64 prod = 1;

  while (*start < strlen(str)) {
    char curr = str[(*start)++];
    if (curr == ')')
      break;

    switch (curr) {
      case ' ':
      case '+':
        break;
      case '*':
        prod *= sum;
        sum = 0;
        break;
      default: {
        if (curr >= '0' && curr <= '9')
          sum += curr - '0';
        else
          sum += eval2(str, start);
      }
    }
  }

  return prod * sum;
}

u64 part1() {
  size_t lines;
  char** data = get_input(&lines);

  u64 sum = 0;
  for (size_t i = 0; i < lines; i++) {
    size_t start = 0;
    sum += eval1(data[i], &start);
  }

  return sum;
}

u64 part2() {
  size_t lines;
  char** data = get_input(&lines);

  u64 sum = 0;
  for (size_t i = 0; i < lines; i++) {
    size_t start = 0;
    sum += eval2(data[i], &start);
  }

  return sum;
}

int main(int argc, char* argv[]) {
  printf("day 18:\n\tpart 1: %lld\n\tpart 2: %lld\n", part1(), part2());

  return 0;
}
