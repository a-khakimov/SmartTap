#include "gamelogic.h"

#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

GameLogic::GameLogic() : m_dimension(0), m_boardSize(0)
{
  // static constexpr size_t defaultBoardDimension = 5;
  //init(defaultBoardDimension);
}

void GameLogic::init(const int dimension)
{
  if (dimension > 10) {
    std::cerr << "GameLogic::init() wrong dimension" << std::endl;
  }
  m_boardInited = false;
  //m_board.clear();
  m_board.resize(m_boardSize);
  m_gameState.firstPlayerScore = 0;
  m_gameState.secondPlayerScore = 0;
  m_gameState.endGame = false;
  m_dimension = dimension;
  m_boardSize = m_dimension * m_dimension;
  m_board.clear();
  m_board.resize(m_boardSize);

  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine random(seed);
  for (auto& tile : m_board) {
    tile.value = random() % 19 - 9; /* from -9 to 9 range */
    tile.active = false;
    tile.removed = false;
  }
  setActiveCol(dimension / 2);

  m_playerMove = PlayerMove::FirstPlayerMove;
  m_boardInited = true;
}

bool GameLogic::isPositionValid(const size_t pos) const
{
  return pos < m_boardSize;
}

const std::vector<Tile>& GameLogic::getBoard() const
{
  return m_board;
}

bool GameLogic::isGameEnd() const
{
  return m_gameState.endGame;
}

int GameLogic::getFirstPlayerScore() const
{
  return m_gameState.firstPlayerScore;
}

int GameLogic::getSecondPlayerScore() const
{
  return m_gameState.secondPlayerScore;
}

size_t GameLogic::getDimension() const
{
  return m_dimension;
}

size_t GameLogic::getBoardSize() const
{
  return m_boardSize;
}

bool GameLogic::move(const int index)
{
  std::cout << index << std::endl;
  if (not isPositionValid(index)) {
    //qDebug() << "Position is not Valid " << index;
    return false;
  }
  const auto [curRow, curCol] = getRowCol(index);

  if (m_gameState.endGame) {
    //qDebug() << "End game";
    return false;
  }
  if (m_board.at(index).active and not m_board.at(index).removed) {
    if (m_playerMove == PlayerMove::FirstPlayerMove) {
      m_gameState.firstPlayerScore += m_board.at(index).value;
      setActiveRow(curRow);
    } else {
      m_gameState.secondPlayerScore += m_board.at(index).value;
      setActiveCol(curCol);
    }

    m_board.at(index).removed = true;

    m_playerMove = (m_playerMove == PlayerMove::FirstPlayerMove
                      ? PlayerMove::SecondPlayerMove
                      : PlayerMove::FirstPlayerMove);

    if (not checkTilesInRow(curRow) and m_playerMove == PlayerMove::SecondPlayerMove) {
      m_gameState.endGame = true;
    }

    if (not checkTilesInCol(curCol) and m_playerMove == PlayerMove::FirstPlayerMove) {
      m_gameState.endGame = true;
    }
  }
  return true;
}

GameLogic::Position GameLogic::getRowCol(size_t index) const
{
  //Q_ASSERT(m_dimension > 0);
  const size_t row = index / m_dimension;
  const size_t column = index % m_dimension;
  return { row, column };
}

void GameLogic::setActiveRow(size_t activeRow)
{
  for (auto tile = m_board.begin(); tile != m_board.end(); ++tile) {
    auto distance = std::distance(m_board.begin(), tile);
    const auto [row, col] = getRowCol(distance);
    tile->active = (activeRow == row);
  }
}

void GameLogic::setActiveCol(size_t activeCol)
{
  for (auto tile = m_board.begin(); tile != m_board.end(); ++tile) {
    auto distance = std::distance(m_board.begin(), tile);
    const auto [row, col] = getRowCol(distance);
    tile->active = (activeCol == col);
  }
}

bool GameLogic::checkTilesInRow(size_t curRow) const
{
  int tileNotRemoved = 0;
  for (auto tile = m_board.begin(); tile != m_board.end(); ++tile) {
    auto distance = std::distance(m_board.begin(), tile);
    const auto [row, _] = getRowCol(distance);
    if (curRow == row) {
      if (not tile->removed) {
        tileNotRemoved++;
      }
    }
  }
  return tileNotRemoved;
}

bool GameLogic::checkTilesInCol(size_t curCol) const
{
  int tileNotRemoved = 0;
  for (auto tile = m_board.begin(); tile != m_board.end(); ++tile) {
    auto distance = std::distance(m_board.begin(), tile);
    const auto [_, col] = getRowCol(distance);
    if (curCol == col) {
      if (not tile->removed) {
        tileNotRemoved++;
      }
    }
  }
  return tileNotRemoved;
}

bool GameLogic::getBoardInited() const
{
  return m_boardInited;
}

GameLogic::~GameLogic()
{

}

