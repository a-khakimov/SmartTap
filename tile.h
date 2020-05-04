#ifndef TILE_H
#define TILE_H


struct Tile {
public:
  int value {};
  bool active {};
  bool removed {};

  Tile& operator = (const int newValue)
  {
    value = newValue;
    return *this;
  }

  bool operator == (const int otherValue)
  {
    return value == otherValue;
  }
};


#endif // TILE_H
