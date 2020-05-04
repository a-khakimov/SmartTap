#include "gameboardmodel.h"

#include <algorithm>
#include <random>
#include <QDebug>

GameBoardModel::GameBoardModel(const size_t boardDimension, QObject *parent)
  : QAbstractListModel { parent },
    m_dimension { boardDimension },
    m_boardSize { m_dimension * m_dimension },
    m_scoreA { 0 }, m_scoreB { 0 }
{
  m_rawBoard.resize(m_boardSize);
  std::iota(m_rawBoard.begin(), m_rawBoard.end(), 0);
  static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 generator(seed);
  std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
}

int GameBoardModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_rawBoard.size();
}

QVariant GameBoardModel::data(const QModelIndex &index, int role) const
{
  if (not index.isValid() or role != Qt::DisplayRole) {
    return {};
  }
  const int rowIndex { index.row() };
  if (not isPositionValid(rowIndex)) {
    return {};
  }
  return QVariant::fromValue(m_rawBoard.at(rowIndex).value);
}

bool GameBoardModel::isPositionValid(const size_t pos) const
{
  return pos < m_boardSize;
}

bool GameBoardModel::remove(int index)
{
  if (not isPositionValid(index)) {
    qDebug() << "Position is not Valid " << index;
    return false;
  }


  m_scoreA += m_rawBoard.at(index).value;

  const auto [row, col] = getRowCol(index);
  qDebug() << "remove - index:" << index << " row:" << row << " col:" << col;

  emit dataChanged(createIndex(0, 0), createIndex(m_boardSize, 0));
  return true;
}

size_t GameBoardModel::dimension() const
{
  return m_dimension;
}

size_t GameBoardModel::boardSize() const
{
  return m_boardSize;
}

GameBoardModel::Position GameBoardModel::getRowCol(size_t index) const
{
  Q_ASSERT(m_dimension > 0);
  const size_t row = index / m_dimension;
  const size_t column = index % m_dimension;
  return { row, column };
}

int GameBoardModel::scoreA()
{
  return m_scoreA;
}

int GameBoardModel::scoreB()
{
  return m_scoreB;
}

