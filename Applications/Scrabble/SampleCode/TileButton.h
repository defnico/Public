#ifndef TILE_BUTTON_H
#define TILE_BUTTON_H

#include "Game.h"
#include <QPushButton>

// Button class used to show and select the current player's tiles.
class TileButton : public QPushButton {
  Q_OBJECT
public:
  TileButton(int index) : index_(index) {}
  bool selected() const { return selected_; }
  void setSelected(bool selected) { selected_ = selected; }

  Tile* tile() { return tile_; }
  void setTile(Tile* tile) { tile_ = tile; }

  // Store where the Tile is placed on the board.
  void placeTileOnBoard(int r, int c) {
    tilePlacedOnBoard_ = true;
    row_ = r;
    col_ = c;
  }

  // Remove tile from the board if it was placed there.
  void removeTileFromBoard() { tilePlacedOnBoard_ = false; }

  bool tilePlacedOnBoard() const { return tilePlacedOnBoard_; }

  // Row and column where tile was placed on the board.
  int row() const { return row_; }
  int col() const { return col_; }

  void clear() {
    setIcon(QIcon());
    setDisabled(false);
    selected_ = false;
    tilePlacedOnBoard_ = false;
  }

public slots:
  void Select() { emit Selected(index_); }

signals:
  void Selected(int);

private:
  int index_; // Current player's tiles index 0 <= index_ < handSize_

  bool selected_; // true if the Tile is selected.
  Tile* tile_;    // Tile for this button.

  bool tilePlacedOnBoard_; // True if tile was placed on the board.
  int row_; // Row on board where tile is place if tilePlaced_ is true.
  int col_; // Column on board where tile is place if tilePlaced_ is true.
};

#endif // TILE_BUTTON_H
