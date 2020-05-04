#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractListModel>

class GameBoard : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(int dimension READ dimension CONSTANT);
  Q_PROPERTY(int scoreA READ scoreA CONSTANT);
  Q_PROPERTY(int scoreB READ scoreB CONSTANT);
  Q_PROPERTY(bool isEndGame READ isEndGame CONSTANT);
public:
  enum BoardDimension {
    Dimension4x4 = 4,
    Dimension5x5 = 5,
    Dimension7x7 = 7,
    Dimension9x9 = 9,
    };
  Q_ENUMS(BoardDimension)

  static constexpr BoardDimension defaultBoardDimension { Dimension4x4 };
  GameBoard(const BoardDimension boardDimension = defaultBoardDimension,
    QObject* parent = nullptr);

  Q_INVOKABLE void boardInit(BoardDimension);

  static void declareQML();

  struct Tile {
    int value {};
    bool active {};
    bool removed {};
    Tile& operator = (const int newValue) {
      value = newValue;
      return *this;
    }
    bool operator == (const int otherValue) {
      return value == otherValue;
    }
  };

  QHash<int, QByteArray> roleNames() const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  bool isPositionValid(const size_t pos) const;
  Q_INVOKABLE bool move(int index);

  size_t dimension() const;
  size_t boardSize() const;
  int scoreA() const;
  int scoreB() const;
  bool isEndGame() const;

  using Position = std::pair<size_t, size_t>;

private:
  Position getRowCol(size_t index) const;
  void setActiveRow(size_t row);
  void setActiveCol(size_t col);
  bool checkTilesInRow(size_t curRow) const;
  bool checkTilesInCol(size_t curCol) const;

  std::vector<Tile> m_rawBoard;
  size_t m_dimension;
  size_t m_boardSize;

  enum BoardRoles {
    ValueRole = Qt::UserRole + 1,
    IsActiveRole,
    IsRemovedRole
  };

  typedef enum PlayerMove {
    FirstPlayerMove,
    SecondPlayerMove
  } PlayerMove_t;

  PlayerMove_t m_playerMove;

  struct GameState {
    int scoreA;
    int scoreB;
    bool endGame;
  };

  GameState gameState;
};

#endif // GAMEBOARD_H
