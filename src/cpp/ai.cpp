#include "ai.h"
#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <iostream>
#include <algorithm>


#include <iomanip>
#include <limits>

namespace smarttap {


Ai::Ai()
{

}

Ai::Ai(
  const std::vector<Tile> &board,
  const size_t dimension,
  const int enemyScore,
  const int myScore)
  : m_board{board},
    m_dimension(dimension),
    enemyScore{enemyScore},
    myScore{myScore}
{

}

int Ai::move()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::geometric_distribution<> d;
  const int r = d(gen);
  switch (r) {
    case 0 ... 2:
      return algorythmMinValueForEnemy(m_board, m_dimension);
    case 3 ... 4:
      return algorythmMaxValue(m_board);
    default:
      break;
  }
  return algorythmRandom(m_board);
}

Ai::~Ai()
{

}

int Ai::algorythmRandom(const std::vector<Tile> &board)
{
  std::vector<std::size_t> indexes = get_indexes(board);
  const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 generator(seed);
  std::shuffle(indexes.begin(), indexes.end(), generator);
  return (indexes.empty() ? -1 : indexes.back());
}

int Ai::algorythmMaxValue(const std::vector<Tile> &board)
{
  std::map<size_t, int> m;
  for (auto tile = board.begin(); tile != board.end(); ++tile) {
    if (tile->active and not tile->removed) {
      m[std::distance(board.begin(), tile)] = tile->value;
    }
  }
  return std::max_element(
    m.begin(), m.end(),
    [](const auto p1, const auto p2) {
      return p1.second < p2.second;
    })->first;
}

int Ai::algorythmMinValueForEnemy(const std::vector<Tile> &board, const size_t dimension)
{
  std::map<std::size_t, int> indx_coeffs;
  for (auto tile = board.begin(); tile != board.end(); ++tile) {
    if (tile->active and not tile->removed) {
      const int tile_index = std::distance(board.begin(), tile);
      /* Изначально коэффициенты будут равны значениям тайлов */
      indx_coeffs[tile_index] = tile->value;
    }
  }

  auto get_column = [&dimension](const auto index){
    return index % dimension;
  };

  for (const auto& index : indx_coeffs) {
    const size_t column = get_column(index.first);
    std::list<int> enemy_tiles;
    for (auto tile = board.begin(); tile != board.end(); ++tile) {
      const size_t tile_index = std::distance(board.begin(), tile);
      const auto tile_col = get_column(tile_index);
      if (tile_col == column and tile_index != index.first) {
        if (not tile->removed) {
          enemy_tiles.push_back(tile->value);
        }
      }
    }
    // Если после моего хода врагу будет нечего выбирать, то этот вариант откидываем
    if (enemy_tiles.empty()) {
      indx_coeffs[index.first] = std::min_element(indx_coeffs.begin(), indx_coeffs.end(),
        [](auto p1, auto p2) {
          return p1.second < p2.second;
        })->second;
    }
    /* Если после моего хода враг возьмет квадрат
     * со значением больше моего то этот вариант тоже нужно откинуть */
    auto d_max = std::max_element(enemy_tiles.begin(), enemy_tiles.end());
    if (indx_coeffs[index.first] < *d_max) {
      indx_coeffs[index.first] -= *d_max - indx_coeffs[index.first];
    }
    /* Если среднее значение квадратов врага больше или равно значения
     * моего квадрата, то этот варант тоже стараемся откинуть */
    const int mean = std::accumulate(enemy_tiles.begin(), enemy_tiles.end(), 0)
                     / (enemy_tiles.empty() ? 1 : enemy_tiles.size());
    if (indx_coeffs[index.first] <= mean) {
      indx_coeffs[index.first] -= mean - indx_coeffs[index.first];
    }
  }

  return std::max_element(indx_coeffs.begin(), indx_coeffs.end(),
    [](auto p1, auto p2) {
      return p1.second < p2.second;
    })->first;
}

std::vector<std::size_t> Ai::get_indexes(const std::vector<Tile> &board)
{
  std::vector<std::size_t> indexes;
  for (auto tile = board.begin(); tile != board.end(); ++tile) {
    if (tile->active and not tile->removed) {
      indexes.push_back(std::distance(board.begin(), tile));
    }
  }
  return indexes;
}

}
