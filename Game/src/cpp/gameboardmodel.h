#ifndef GameBoardModel_H
#define GameBoardModel_H

#include <QAbstractListModel>
#include "gamelogic.h"

class GameBoardModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(int dimension READ dimension CONSTANT);
  Q_PROPERTY(int scoreA READ scoreA CONSTANT);
  Q_PROPERTY(int scoreB READ scoreB CONSTANT);
  Q_PROPERTY(bool isEndGame READ isEndGame CONSTANT);

public:

  enum BoardDimension {
    Dimension2x2 = 2,
    Dimension3x3 = 3,
    Dimension4x4 = 4,
    Dimension5x5 = 5,
    Dimension6x6 = 6,
    Dimension7x7 = 7,
    Dimension9x9 = 9,
    };
  Q_ENUMS(BoardDimension)

  enum GameMode {
    None = 0,
    Ai,
    X2,
    Multiplayer
  };
  Q_ENUMS(GameMode)

  static constexpr BoardDimension defaultBoardDimension { Dimension6x6 };
  GameBoardModel(const BoardDimension boardDimension = defaultBoardDimension,
    QObject* parent = nullptr);

  QHash<int, QByteArray> roleNames     () const override;
  int                    rowCount      (const QModelIndex &parent = QModelIndex()) const override;
  QVariant               data          (const QModelIndex& index, int role = Qt::DisplayRole) const override;

  Q_INVOKABLE bool       isTileRemoved (int index);
  Q_INVOKABLE void       boardInit     (BoardDimension);
  Q_INVOKABLE bool       moveX2        (int index);
  Q_INVOKABLE int        moveAI        ();
  size_t                 dimension     () const;
  size_t                 boardSize     () const;
  int                    scoreA        () const;
  int                    scoreB        () const;
  bool                   isEndGame     () const;
  static void            declareQML    ();

private:

  enum BoardRoles {
    ValueRole = Qt::UserRole + 1,
    IsActiveRole,
    IsRemovedRole
  };

  GameLogic gameLogic;

signals:
  void aiMoveIndex(qint32 aiindex) const;
  void resetBoard() const;
};

#endif // GameBoardModel_H
