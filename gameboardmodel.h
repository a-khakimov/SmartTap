#ifndef GAMEBOARDMODEL_H
#define GAMEBOARDMODEL_H

#include <QAbstractListModel>

class GameBoardModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(int dimension READ dimension CONSTANT);
  Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT);
public:
  static constexpr size_t defaultBoardDimension {5};
  GameBoardModel(const size_t boardDimension = defaultBoardDimension,
    QObject* parent = nullptr);

  struct Tile {
    int value {};
    Tile& operator = (const int newValue) {
      value = newValue;
      return *this;
    }
    bool operator == (const int otherValue) {
      return value == otherValue;
    }
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  bool isPositionValid(const size_t pos) const;
  Q_INVOKABLE bool remove(int index);
  Q_INVOKABLE int scoreA();
  Q_INVOKABLE int scoreB();

  size_t dimension() const;
  size_t boardSize() const;

  using Position = std::pair<size_t, size_t>;

private:
  Position getRowCol(size_t index) const;

  std::vector<Tile> m_rawBoard;
  const size_t m_dimension;
  const size_t m_boardSize;
  int m_scoreA;
  int m_scoreB;
};

#endif // GAMEBOARDMODEL_H
