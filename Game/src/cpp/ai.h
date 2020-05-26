#ifndef AI_H
#define AI_H

#include "gamelogic.h"

namespace smarttap {

class Ai
{
public:
  Ai();
  explicit Ai(
    const std::vector<Tile>& board,
    const size_t dimension,
    const int enemyScore,
    const int myScore);
  int move();
  ~Ai();
private:
  int algorythmMinValueForEnemy(const std::vector<Tile>& board, const size_t dimension);
  int algorythmMaxValue(const std::vector<Tile>& board);
  int algorythmRandom(const std::vector<Tile>& board);
  std::vector<std::size_t> get_indexes(const std::vector<Tile>& board);

  std::vector<Tile> m_board;
  size_t m_dimension;
  int enemyScore;
  int myScore;
};

}

#endif // AI_H
