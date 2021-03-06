#include "gameboardmodel.h"
#include "ai.h"
#include <iostream>
#include <QDebug>
#include <QQmlEngine>

GameBoardModel::GameBoardModel(const GameBoardModel::BoardDimension boardDimension, QObject *parent)
  : QAbstractListModel { parent }
{
  boardInit(boardDimension);
}

void GameBoardModel::boardInit(const GameBoardModel::BoardDimension dimension)
{
  gameLogic.reload(dimension);
  size_t boardSize = gameLogic.getBoardSize();
  std::cout << "boardSize: " << boardSize << std::endl;
  emit resetBoard();
  emit dataChanged(createIndex(0, 0), createIndex(gameLogic.getBoardSize(), 0));
}

void GameBoardModel::declareQML()
{
  qmlRegisterType<GameBoardModel>("GameBoardModel", 1, 0, "GameBoardModel");
}

QHash<int, QByteArray> GameBoardModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[BoardRoles::ValueRole] = "value";
  roles[BoardRoles::IsActiveRole] = "isActive";
  roles[BoardRoles::IsRemovedRole] = "isRemoved";
  return roles;
}

int GameBoardModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return gameLogic.getBoardSize();
}

QVariant GameBoardModel::data(const QModelIndex &index, int role) const
{
  const int rowIndex { index.row() };
  if (not gameLogic.isPositionValid(rowIndex)) {
    return {};
  }

  if (not index.isValid() or index.row() > rowCount(index)) {
    return {};
  }

  const Tile& tile = gameLogic.getBoard().at(index.row());
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
    default: {
      return {};
    }
  }
}

bool GameBoardModel::isTileRemoved(int index)
{
  const auto& tile = gameLogic.getBoard().at(index);
  return tile.removed;
}

int GameBoardModel::moveAI()
{
  smarttap::Ai ai(gameLogic.getBoard(), dimension(), scoreA(), scoreB());
  const int ai_move_index = ai.move();
  std::cout << "ai_move_index:" << ai_move_index << std::endl;
  if (not gameLogic.move(ai_move_index)) {
    return -1;
  }
  emit dataChanged(createIndex(0, 0), createIndex(gameLogic.getBoardSize(), 0));
  emit aiMoveIndex(ai_move_index);
  return ai_move_index;
}

bool GameBoardModel::moveX2(int index)
{
  if (not gameLogic.move(index)) {
    return false;
  }
  emit dataChanged(createIndex(0, 0), createIndex(gameLogic.getBoardSize(), 0));
  return true;
}

size_t GameBoardModel::dimension() const
{
  return gameLogic.getDimension();
}

size_t GameBoardModel::boardSize() const
{
  return gameLogic.getBoardSize();
}

int GameBoardModel::scoreA() const
{
  return gameLogic.getFirstPlayerScore();
}

int GameBoardModel::scoreB() const
{
  return gameLogic.getSecondPlayerScore();
}

bool GameBoardModel::isEndGame() const
{
  return gameLogic.isGameEnd();
}
