#include "ai.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

Ai::Ai()
{

}

int Ai::move(const std::vector<Tile> &board)
{
  std::vector<size_t> indexes;
  for (auto tile = board.begin(); tile != board.end(); ++tile) {
    if (tile->active and not tile->removed) {
      indexes.push_back(std::distance(board.begin(), tile));
    }
  }

  // TODO: заменить рандом на нормальный алгоритм
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 generator(seed);
  std::shuffle(indexes.begin(), indexes.end(), generator);

  return (indexes.empty() ? -1 : indexes.back());
}

Ai::~Ai()
{

}
