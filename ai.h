#ifndef AI_H
#define AI_H

#include "gamelogic.h"

class Ai
{
public:
  Ai();
  int move(const std::vector<Tile>& board);
  ~Ai();
};

#endif // AI_H
