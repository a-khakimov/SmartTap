#include "gameboard.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <QDebug>

GameBoard::GameBoard(const GameBoard::BoardDimension_t boardDimension, QObject *parent)
  : QAbstractListModel { parent }, m_playerMove { PlayerMove::FirstPlayerMove }
{
  boardInit(boardDimension);
}

void GameBoard::boardInit(const GameBoard::BoardDimension_t boardDimension)
{
  m_dimension = boardDimension;
  m_boardSize = m_dimension * m_dimension;
  m_rawBoard.clear();
  m_rawBoard.resize(m_boardSize);
  static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine random(seed);
  for (auto& tile : m_rawBoard) {
    tile.value = random() % 19 - 9;
    tile.active = false;
    tile.removed = false;
  }
  setActiveCol(boardDimension / 2);
  gameState.scoreA = 0;
  gameState.scoreB = 0;
  gameState.endGame = false;
}

QHash<int, QByteArray> GameBoard::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[BoardRoles::ValueRole] = "value";
  roles[BoardRoles::IsActiveRole] = "isActive";
  roles[BoardRoles::IsRemovedRole] = "isRemoved";
  return roles;
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
  const int rowIndex { index.row() };
  if (not isPositionValid(rowIndex)) {
    return {};
  }

  if (not index.isValid() or index.row() > rowCount(index)) {
    return {};
  }

  const Tile& tile { m_rawBoard.at(index.row()) };
  switch (role) {
    case BoardRoles::ValueRole: {
      return QVariant::fromValue(tile.value);
    }
    case BoardRoles::IsRemovedRole: {
      return QVariant::fromValue(tile.removed);
    }
    case BoardRoles::IsActiveRole: {
      return QVariant::fromValue(tile.active);
    }
    default:
      return {};
  }
}

bool GameBoard::isPositionValid(const size_t pos) const
{
  return pos < m_boardSize;
}

bool GameBoard::move(int index)
{
  if (not isPositionValid(index)) {
    qDebug() << "Position is not Valid " << index;
    return false;
  }
  const auto [curRow, curCol] = getRowCol(index);

  if (gameState.endGame) {
    qDebug() << "End game";
    return false;
  }
  if (m_rawBoard.at(index).active and not m_rawBoard.at(index).removed) {
    if (m_playerMove == PlayerMove::FirstPlayerMove) {
      qDebug() << "FirstPlayerMove";
      gameState.scoreA += m_rawBoard.at(index).value;
      setActiveRow(curRow);
    } else {
      qDebug() << "SecondPlayerMove";
      gameState.scoreB += m_rawBoard.at(index).value;
      setActiveCol(curCol);
    }

    m_rawBoard.at(index).removed = true;


    m_playerMove = (m_playerMove == PlayerMove::FirstPlayerMove
                      ? PlayerMove::SecondPlayerMove
                      : PlayerMove::FirstPlayerMove);

    if (not checkTilesInRow(curRow) and m_playerMove == PlayerMove::SecondPlayerMove) {
      qDebug() << "SecondPlayerMove End game";
      gameState.endGame = true;
    }

    if (not checkTilesInCol(curCol) and m_playerMove == PlayerMove::FirstPlayerMove) {
      qDebug() << "FirstPlayerMove End game";
      gameState.endGame = true;
    }
    emit dataChanged(createIndex(0, 0), createIndex(m_boardSize, 0));
  }
  return true;
}

size_t GameBoard::dimension() const
{
  return m_dimension;
}

size_t GameBoard::boardSize() const
{
  return m_boardSize;
}

int GameBoard::scoreA() const
{
  return gameState.scoreA;
}

int GameBoard::scoreB() const
{
  return gameState.scoreB;
}

bool GameBoard::isEndGame() const
{
  return gameState.endGame;
}

GameBoard::Position GameBoard::getRowCol(size_t index) const
{
  Q_ASSERT(m_dimension > 0);
  const size_t row = index / m_dimension;
  const size_t column = index % m_dimension;
  return { row, column };
}

void GameBoard::setActiveRow(size_t activeRow)
{
  for (auto tile = m_rawBoard.begin(); tile != m_rawBoard.end(); ++tile) {
    auto distance = std::distance(m_rawBoard.begin(), tile);
    const auto [row, col] = getRowCol(distance);
    tile->active = (activeRow == row);
  }
}

void GameBoard::setActiveCol(size_t activeCol)
{
  for (auto tile = m_rawBoard.begin(); tile != m_rawBoard.end(); ++tile) {
    auto distance = std::distance(m_rawBoard.begin(), tile);
    const auto [row, col] = getRowCol(distance);
    tile->active = (activeCol == col);
  }
}

bool GameBoard::checkTilesInRow(size_t curRow) const
{
  int tileNotRemoved = 0;
  for (auto tile = m_rawBoard.begin(); tile != m_rawBoard.end(); ++tile) {
    auto distance = std::distance(m_rawBoard.begin(), tile);
    const auto [row, _] = getRowCol(distance);
    //std::cout << row << " ";
    if (curRow == row) {
      if (not tile->removed) {
        std::cout << ".";
        tileNotRemoved++;
      }
    }
  }
  std::cout << "row:" << tileNotRemoved << std::endl;
  return tileNotRemoved;
}

bool GameBoard::checkTilesInCol(size_t curCol) const
{
  int tileNotRemoved = 0;
  for (auto tile = m_rawBoard.begin(); tile != m_rawBoard.end(); ++tile) {
    auto distance = std::distance(m_rawBoard.begin(), tile);
    const auto [_, col] = getRowCol(distance);
    if (curCol == col) {
      if (not tile->removed) {
        std::cout << ".";
        tileNotRemoved++;
      }
    }
  }
  std::cout << "col:" << tileNotRemoved << std::endl;
  return tileNotRemoved;
}
