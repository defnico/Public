#ifndef SQUARE_BUTTON_H
#define SQUARE_BUTTON_H

#include <QPushButton>

// This widget is the QPushButton for each square on the board.
class SquareButton : public QPushButton {
  Q_OBJECT
public:
  SquareButton(int r, int c, QPixmap& pixmap)
      : icon_(pixmap), row_(r), col_(c) {
    setIcon(icon_);
    setIconSize(QSize(40, 40));
    setFixedSize(40, 40);
  }

  void RestoreBoardIcon() { setIcon(icon_); }

public slots:
  void Select() { emit Selected(row_, col_); }

signals:
  void Selected(int, int);

private:
  // The original icon to show at the square at row,col.
  // Stored here in case it needs to be resoted when a tile is taken off
  // the board.
  QIcon icon_;
  int row_;
  int col_;
};

#endif // SQUARE_BUTTON_H
