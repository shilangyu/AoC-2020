#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
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

Tile rotate(const Tile& tile) {
  auto& pixels = tile.pixels;
  Tile res = tile;

  for (size_t i = 0; i < pixels.size(); i++) {
    for (size_t j = 0; j < pixels[i].size(); j++) {
      res.pixels[j][pixels.size() - i - 1] = pixels[i][j];
    }
  }

  return res;
}

Tile flip_y(const Tile& tile) {
  auto& pixels = tile.pixels;
  Tile res = tile;

  for (size_t i = 0; i < pixels.size(); i++) {
    for (size_t j = 0; j < pixels[i].size(); j++) {
      res.pixels[i][pixels.size() - j - 1] = pixels[i][j];
    }
  }

  return res;
}

/// Augment a list of tiles with all of the rotations and flips
vector<Tile> augment_actions(vector<Tile> tiles) {
  vector<Tile> augmented;

  for (auto tile : tiles) {
    augmented.push_back(tile);
    augmented.push_back(rotate(tile));
    augmented.push_back(rotate(rotate(tile)));
    augmented.push_back(rotate(rotate(rotate(tile))));
    augmented.push_back(flip_y(tile));
    augmented.push_back(rotate(flip_y(tile)));
    augmented.push_back(rotate(rotate(flip_y(tile))));
    augmented.push_back(rotate(rotate(rotate(flip_y(tile)))));
  }

  return augmented;
}

optional<vector<vector<Tile>>> tile_image(vector<Tile>& tiles,
                                          vector<vector<Tile>>& tiling,
                                          size_t d,
                                          unordered_set<uint64_t>& used_tiles) {
  auto n = tiling.size();
  auto m = tiling[n - 1].size();

  if (n == d && m == d) {
    // full tiling
    return tiling;
  }

  for (auto& tile : tiles) {
    if (used_tiles.find(tile.id) != used_tiles.end()) {
      // already used in the tiling, skip
      continue;
    }

    if (n != 1) {
      // if not first row, the tile has to match with the one above
      if (m != d) {
        if (tiling[n - 2][m].pixels.back() != tile.pixels.front()) {
          continue;
        }
      } else {
        if (tiling[n - 1][0].pixels.back() != tile.pixels.front()) {
          continue;
        }
      }
    }

    if (m != d && m != 0) {
      // if not first column, the tile has to match with the one on the left
      for (size_t i = 0; i < tile.pixels.size(); i++) {
        if (tiling[n - 1][m - 1].pixels[i].back() != tile.pixels[i][0]) {
          goto skip_tile;
        }
      }
    }

    {
      used_tiles.insert(tile.id);
      if (m == d) {
        tiling.emplace_back();
      }
      tiling.back().push_back(tile);

      if (auto out = tile_image(tiles, tiling, d, used_tiles);
          out.has_value()) {
        return out;
      }

      tiling.back().pop_back();
      if (m == d) {
        tiling.pop_back();
      }

      used_tiles.erase(tile.id);
    }

  skip_tile:;
  }

  return std::nullopt;
}

vector<vector<Tile>> tile_image(vector<Tile>& tiles) {
  unordered_set<uint64_t> used_tiles;
  vector<vector<Tile>> temp;
  temp.emplace_back();

  size_t d = lround(sqrt((tiles.size() / 8)));

  auto tiling = tile_image(tiles, temp, d, used_tiles);

  return tiling.value();
}

string part1() {
  auto data = augment_actions(get_input());
  auto tiling = tile_image(data);

  // c++ does not support 128bit numbers
  string python_cmd = "python3 -c 'print(";

  python_cmd.append(to_string(tiling.front().front().id));
  python_cmd.append("*");
  python_cmd.append(to_string(tiling.back().back().id));
  python_cmd.append("*");
  python_cmd.append(to_string(tiling.front().back().id));
  python_cmd.append("*");
  python_cmd.append(to_string(tiling.back().front().id));
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
