#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include "tile.h"

namespace  {

typedef enum PlayerMove {
  FirstPlayerMove,
  SecondPlayerMove
} PlayerMove_t;

}

class GameLogic
{
public:
  GameLogic();
  void init(const int dimension);
  bool move(const int index);
  ~GameLogic();

  using Position = std::pair<size_t, size_t>;

  bool isPositionValid (const size_t pos) const;
  size_t getBoardSize() const;
  size_t getDimension() const;
  const std::vector<Tile>& getBoard() const;
  int getFirstPlayerScore() const;
  int getSecondPlayerScore() const;
  bool isGameEnd() const;
  bool getBoardInited() const;

private:
  Position getRowCol(size_t index) const;
  void setActiveRow(size_t row);
  void setActiveCol(size_t col);
  bool checkTilesInRow(size_t curRow) const;
  bool checkTilesInCol(size_t curCol) const;

  struct GameState {
    int firstPlayerScore;
    int secondPlayerScore;
    bool endGame;
  };

  PlayerMove_t m_playerMove;
  GameState m_gameState;
  std::vector<Tile> m_board;
  size_t m_dimension;
  size_t m_boardSize;
  bool m_boardInited;
};

#endif // GAMELOGIC_H
