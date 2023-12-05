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

vector<vector<bool>> rotate(const vector<vector<bool>>& pixels) {
  auto res = pixels;

  for (size_t i = 0; i < pixels.size(); i++) {
    for (size_t j = 0; j < pixels[i].size(); j++) {
      res[j][pixels.size() - i - 1] = pixels[i][j];
    }
  }

  return res;
}

Tile rotate(const Tile& tile) {
  auto res = tile;
  res.pixels = rotate(tile.pixels);
  return res;
}

vector<vector<bool>> flip_y(const vector<vector<bool>>& pixels) {
  auto res = pixels;

  for (size_t i = 0; i < pixels.size(); i++) {
    for (size_t j = 0; j < pixels[i].size(); j++) {
      res[i][pixels.size() - j - 1] = pixels[i][j];
    }
  }

  return res;
}

Tile flip_y(const Tile& tile) {
  auto res = tile;
  res.pixels = flip_y(tile.pixels);
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

    if (n != 1 || (n == 1 && m == d)) {
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

vector<vector<bool>> drop_borders(Tile& tile) {
  auto copy = tile.pixels;

  copy.pop_back();
  copy.erase(copy.begin());

  for (size_t i = 0; i < copy.size(); i++) {
    copy[i].pop_back();
    copy[i].erase(copy[i].begin());
  }

  return copy;
}

void print_image(vector<vector<bool>> pixels) {
  for (size_t i = 0; i < pixels.size(); i++) {
    for (size_t j = 0; j < pixels[i].size(); j++) {
      cout << (pixels[i][j] ? '#' : '.');
    }
    cout << endl;
  }
}

size_t count_set(const vector<vector<bool>>& pixels) {
  size_t count = 0;
  for (const auto& row : pixels) {
    for (const auto& cell : row) {
      if (cell) {
        count += 1;
      }
    }
  }
  return count;
}

int part2() {
  auto data = augment_actions(get_input());
  auto tiling = tile_image(data);

  vector<vector<bool>> monster = {
      {false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, true,  false},
      {true,  false, false, false, false, true,  true,  false, false, false,
       false, true,  true,  false, false, false, false, true,  true,  true},
      {false, true,  false, false, true,  false, false, true,  false, false,
       true,  false, false, true,  false, false, true,  false, false, false},
  };

  // construct tiled image
  vector<vector<bool>> image;
  for (size_t i = 0; i < tiling.size(); i++) {
    for (size_t j = 0; j < tiling[i].size(); j++) {
      auto pixels = drop_borders(tiling[i][j]);
      for (size_t k = 0; k < pixels.size(); k++) {
        if (j == 0) {
          image.emplace_back();
        }
        for (size_t l = 0; l < pixels[k].size(); l++) {
          image[k + i * pixels.size()].push_back(pixels[k][l]);
        }
      }
    }
  }
  auto images = {
      image,
      rotate(image),
      rotate(rotate(image)),
      rotate(rotate(rotate(image))),
      flip_y(image),
      rotate(flip_y(image)),
      rotate(rotate(flip_y(image))),
      rotate(rotate(rotate(flip_y(image)))),
  };

  // count number of monsters
  for (auto img : images) {
    int monster_count = 0;
    for (size_t i = 0; i < img.size() - monster.size() + 1; i++) {
      for (size_t j = 0; j < img[i].size() - monster[0].size() + 1; j++) {
        bool found = true;
        for (size_t k = 0; k < monster.size(); k++) {
          for (size_t l = 0; l < monster[k].size(); l++) {
            if (monster[k][l] && !img[i + k][j + l]) {
              found = false;
              break;
            }
          }
          if (!found) {
            break;
          }
        }
        if (found) {
          monster_count += 1;
        }
      }
    }

    if (monster_count > 0) {
      // there is only one orientation where there are multiple monsters
      return count_set(img) - monster_count * count_set(monster);
    }
  }

  return 0;
}

int main() {
  cout << "day 20:" << endl
       << "\tpart 1: " << part1() << endl
       << "\tpart 2: " << part2() << endl;
  return 0;
}
