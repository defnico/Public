#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <vector>

#include "Dictionary.h"
#include "Tile.h"

class Board {
public:
  Board() {}
  ~Board();
  bool readFile(std::string boardFileName);
  bool readInitFile(std::string initFileName);

  int width() const { return width_; }
  int height() const { return height_; }
  int startCol() const { return startCol_; }
  int startRow() const { return startRow_; }

  bool isEmpty() const;

  const std::vector<std::vector<char>>& squares() const { return squares_; }
  std::vector<std::vector<Tile*>>& tiles() { return tiles_; }

private:
  int width_, height_;

  // First word must be use this square.
  int startCol_, startRow_;

  // The letters when the board is created.
  std::vector<std::vector<char>> squares_;

  // The tiles placed on the board (nullptr when square is empty).
  std::vector<std::vector<Tile*>> tiles_;
};

#endif // BOARD_H_
