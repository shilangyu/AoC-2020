#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// execute command and get output (needed to call python)
// https://stackoverflow.com/a/478960/7907549
string exec(const char* cmd) {
  array<char, 128> buffer;
  string result;
  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

struct Tile {
  uint64_t id;
  vector<vector<bool>> pixels;
};

vector<Tile> get_input() {
  ifstream f;
  f.open("./inputs/day20.txt");
  string line;
  vector<Tile> res;

  while (getline(f, line)) {
    Tile curr;
    curr.id = stoi(line.substr(line.find(" ") + 1, line.size()));

    vector<vector<bool>> pixels;
    while (getline(f, line)) {
      if (line == "") {
        break;
      }

      pixels.push_back({});
      for (auto& c : line) {
        pixels.back().push_back(c == '#');
      }
    }
    curr.pixels = pixels;
    res.push_back(curr);
  }

  return res;
}

string part1() {
  auto data = get_input();

  struct TileBorders {
    uint64_t id;
    // borders encoded as a 10-bit number
    array<uint16_t, 4> borders;
  };

  vector<TileBorders> tiles;

  for (auto& tile : data) {
    tiles.push_back({});
    tiles.back().id = tile.id;

    uint16_t b1 = 0;
    for (size_t i = 0; i < tile.pixels.size(); i++) {
      b1 |= tile.pixels[0][i] << i;
    }
    uint16_t b2 = 0;
    for (size_t i = 0; i < tile.pixels.size(); i++) {
      b2 |= tile.pixels.back()[tile.pixels.back().size() - 1 - i] << i;
    }
    uint16_t b3 = 0;
    for (size_t i = 0; i < tile.pixels.size(); i++) {
      b3 |= tile.pixels[tile.pixels.back().size() - 1 - i][0] << i;
    }
    uint16_t b4 = 0;
    for (size_t i = 0; i < tile.pixels.size(); i++) {
      b4 |= tile.pixels[i].back() << i;
    }

    tiles.back().borders = {b1, b2, b3, b4};
  }

  // c++ does not support 128bit numbers
  string python_cmd = "python3 -c 'print(1";

  // THANK GOD each tile has only one matching neighbor, gonna exploit it and
  // just assume those with 2 matching borders are corners
  for (auto& tile : tiles) {
    int found = 0;
    for (auto& border : tile.borders) {
      // reversed is needed to check for rotations
      uint16_t reversed = 0;
      for (size_t i = 0; i < data[0].pixels.size(); i++) {
        reversed |= ((border >> (data[0].pixels.size() - 1 - i)) & 1) << i;
      }

      for (auto& other_tile : tiles) {
        if (other_tile.id == tile.id)
          continue;

        for (auto& other_border : other_tile.borders) {
          // rotation || flip
          if (reversed == other_border || border == other_border) {
            found++;
          }
        }
      }
    }
    if (found == 2) {
      python_cmd.append("*");
      python_cmd.append(to_string(tile.id));
    }
  }
  python_cmd.append(", end=\"\")'");
  string res = exec(python_cmd.c_str());

  return res;
}

int part2() {
  auto data = get_input();

  return 0;
}

int main() {
  cout << "day 20:" << endl
       << "\tpart 1: " << part1() << endl
       << "\tpart 2: " << part2() << endl;
  return 0;
}
